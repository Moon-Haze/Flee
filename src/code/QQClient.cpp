/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-16 11:05
 * @FilePath: \Flee\src\code\QQClient.cpp
 * @Description:
 */

#include "QQClient.h"
#include "ByteArray.h"
#include "NetworkHandler.h"
#include "QQConfig.h"
#include <corecrt.h>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <spdlog/common.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

namespace Flee {
// bool isInit = true;

QQClient::QQClient(uint64_t uin)
    : config(uin),
      packet(uin, config.platform, config.getDeviceDir()),
      handler(io_service) {

    std::vector<spdlog::sink_ptr> sinks = {
        std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
        std::make_shared<spdlog::sinks::rotating_file_sink_mt>(config.getLogDir(),
                                                               1024 * 1024 * 10, 10)
    };
    try {
        logger = std::make_shared<spdlog::logger>(std::to_string(uin), sinks.begin(),
                                                  sinks.end());
        packet.setLogger(logger);
        spdlog::info("create logger, this name is {}, out file is {} ", uin,
                     config.getLogDir());
    } catch(std::exception& e) {
        spdlog::error("Error in creating logger message: {}", e.what());
    }
}

void QQClient::login() {
    ByteArray password = packet.getPassword();

    /**
    std::string src[] = { "msfwifi.3g.qq.com:8080", "114.221.148.179:14000",
                          "113.96.13.125:8080",     "14.22.3.51:8080",
                          "42.81.172.207:443",      "114.221.144.89:80",
                          "125.94.60.148:14000",    "42.81.192.226:443",
                          "114.221.148.233:8080",   "42.81.172.22:80" };
    */
    handler.connect("msfwifi.3g.qq.com", "8080");
    const std::string& token_dir(config.getTokenDir());

    if(password.empty()) {
        if(std::filesystem::exists(token_dir)) {
            spdlog::info("token file({}) exists. use token to log in.", token_dir);
            ByteArray    token;
            std::fstream token_file{ token_dir };
            token_file >> token;
            // token 登录
            tokenLogin(token);
        } else {
            spdlog::info("token file({}) doesn't exists.", token_dir);
            // 扫码登录 或者 扫码后操作
            packet.sig.qrsig.size() ? qrcodeLogin() : fetchQrcode();
        }
    } else {
        // 密码登录
        passwordLogin(password);
    }
    // 读取数据包
    handler.async_read(
        [this](ByteArray& bytes) { this->packet.parseFlagPacket(bytes); });
    io_service.run();
}

bool QQClient::tokenLogin(const ByteArray& data) {
    return false;
}

bool QQClient::passwordLogin(const ByteArray& data) {
    return false;
}

bool QQClient::qrcodeLogin() {
    return false;
}

bool QQClient::fetchQrcode() {
    ByteArray body;
    /**
        const body = new writer_1.default()
            .writeU16(0)
            .writeU32(16)
            .writeU64(0)
            .writeU8(8)
            .writeTlv(constants_1.BUF0)
            .writeU16(6)
            .writeBytes(t(0x16))
            .writeBytes(t(0x1B))
            .writeBytes(t(0x1D))
            .writeBytes(t(0x1F))
            .writeBytes(t(0x33))
            .writeBytes(t(0x35))
     */
    body << uint16_t(0) << uint32_t(16) << uint64_t(0) << uint8_t(8) << uint16_t(0)
         << uint16_t(6) << packet.t16() << packet.t1B() << packet.t1D() << packet.t1F()
         << packet.t33() << packet.t35();
    // const pkt = buildCode2dPacket.call(this, 0x31, 0x11100, body)
    body = packet.buildCode2dPacket(0x31, 0x11100, body);
    /**
     */
    // spdlog::info("send data: {}", body.toHex());
    // spdlog::info("send data: size={}", body.size());
    handler.write(body, [this](std::size_t size) {
        this->listener.add(this->packet.sig.seq, [](const ByteArray& buffer) {
            /**
                payload = tea.decrypt(payload.slice(16, -1), this[ECDH].share_key);
                const stream = stream_1.Readable.from(payload, { objectMode: false });
                stream.read(54);
                const retcode = stream.read(1)[0];
                const qrsig = stream.read(stream.read(2).readUInt16BE());
                stream.read(2);
                const t = readTlv(stream);
                if (!retcode && t[0x17]) {
                    this.sig.qrsig = qrsig;
                    this.emit("internal.qrcode", t[0x17]);
                }
                else {
                    this.emit("internal.error.qrcode",
               retcode,"获取二维码失败，请重试");
                }
             */
        });
    });
    return false;
}

void QQClient::queryQrcodeResult() {
    if(!packet.sig.qrsig.size()) {
    } else {
        ByteArray body;
        body << uint16_t(5) << uint8_t(1) << uint32_t(16)
             << BuildPackage(packet.sig.qrsig) << uint64_t(0) << uint8_t(8)
             << uint32_t(0) << uint16_t(0);
    }
}

}; // namespace Flee