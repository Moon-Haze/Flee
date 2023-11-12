/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-03-31 17:03
 * @FilePath: \Flee\src\core\QBaseClient.cpp
 * @Description:
 */

#include "QBaseClient.h"
#include "BuildPackage.h"
#include "ByteArray.h"
#include "QQConfig.h"
#include "QQPackTlv.h"
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iostream>
#include <map>
#include <spdlog/common.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

namespace Flee {
// bool isInit = true;

QBaseClient::QBaseClient(uint64_t uin)
    : config(uin),
      packet(uin, config.platform, config.getDeviceDir()),
      netService(io_service) {

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

void QBaseClient::login() {
    ByteArray password = packet.getPassword();

    /**
    std::string src[] = { "msfwifi.3g.qq.com:8080", "114.221.148.179:14000",
                          "113.96.13.125:8080",     "14.22.3.51:8080",
                          "42.81.172.207:443",      "114.221.144.89:80",
                          "125.94.60.148:14000",    "42.81.192.226:443",
                          "114.221.148.233:8080",   "42.81.172.22:80" };
    */
    netService.connect("msfwifi.3g.qq.com", "8080");
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
            fetchQrcode();
        }
    } else {
        // 密码登录
        passwordLogin(password);
    }
    // 读取数据包
    netService.async_read(
        std::bind(&QQPackTlv::parseFlagPacket, &(this->packet), std::placeholders::_1));
    io_service.run();
}

void QBaseClient::FN_SEND_LOGIN(const std::string& cmd, const ByteArray& body) {

    if(netService.write(packet.buildLoginPacket(cmd, body))) {
        this->listener.add(this->packet.sig.seq, [this](ByteArray& buffer) {
            auto type = this->loginHandler.decodeLoginResponse(buffer);
            if(type == 204) {
                ByteArray body;
                body << uint32_t((20 << 16) | 4) << packet.t08() << packet.t104()
                     << packet.t116() << packet.t401();
                this->FN_SEND_LOGIN("wtlogin.login", body);
            }
        });
    }
}

void QBaseClient::tokenLogin(const ByteArray& data) {}

void QBaseClient::passwordLogin(const ByteArray& data) {}

void QBaseClient::qrcodeLogin(const QRCodeResult& result) {
    if(result.retcode != 0 || result.t106.empty() || result.t16a.empty()
       || result.t318.empty() || result.tgtgt.empty()) {
        std::string message;
        switch(result.retcode) {
            case 48:
                message = "二维码尚未扫描";
                break;
            case 53:
                message = "二维码尚未确认";
                this->timer1.wait();
                this->queryQrcodeResult();
                break;
            case 17:
                message = "二维码超时，请重新获取";
            case 54:
                message = "二维码被取消，请重新获取";
                fetchQrcode();
            default:
                message = "扫码遇到未知错误，请重新获取";
        }
        packet.sig.qrsig.clear();
        // this.emit("internal.error.qrcode", retcode, message);
        // TODO: 二维码相关操作
        spdlog::info("internal.error.qrcode: retcode={}, message={}", result.retcode,
                     message);
    } else { // else if (retcode === 0 && t106 && t16a && t318 && tgtgt)
        /**
                this.sig.qrsig = constants_1.BUF0;
                if (uin !== this.uin) {
                    this.emit("internal.error.qrcode", retcode,
            `扫码账号(${uin})与登录账号(${this.uin})不符`); return;
                }
         */
        packet.sig.qrsig.clear();
        if(result.uin != packet.getUin()) {
            logger->error("扫码账号({})与登录账号({})不符", result.uin,
                          packet.getUin());
        } else {
            // this.sig.tgtgt = tgtgt;
            packet.sig.tgtgt = result.tgtgt;
            ByteArray body;
            /**
                .writeU16(9)
                .writeU16(24)
                .writeBytes(t(0x18))
                .writeBytes(t(0x1))
                .writeU16(0x106)
                .writeTlv(t106)
                .writeBytes(t(0x116))
                .writeBytes(t(0x100))
                .writeBytes(t(0x107))
                .writeBytes(t(0x142))
                .writeBytes(t(0x144))
                .writeBytes(t(0x145))
                .writeBytes(t(0x147))
                .writeU16(0x16a)
                .writeTlv(t16a)
                .writeBytes(t(0x154))
                .writeBytes(t(0x141))
                .writeBytes(t(0x8))
                .writeBytes(t(0x511))
                .writeBytes(t(0x187))
                .writeBytes(t(0x188))
                .writeBytes(t(0x194))
                .writeBytes(t(0x191))
                .writeBytes(t(0x202))
                .writeBytes(t(0x177))
                .writeBytes(t(0x516))
                .writeBytes(t(0x521))
                .writeU16(0x318)
                .writeTlv(t318)
                this[FN_SEND_LOGIN]("wtlogin.login", body);
            */
            body << uint32_t((9 << 16) | 24) << packet.t18() << packet.t01()
                 << uint16_t(0x106) << BuildPackage<>(result.t106) << packet.t116()
                 << packet.t100() << packet.t107() << packet.t142() << packet.t144()
                 << packet.t145() << packet.t147() << uint16_t(0x16a)
                 << BuildPackage<>(result.t16a) << packet.t154() << packet.t141()
                 << packet.t08() << packet.t511() << packet.t187() << packet.t188()
                 << packet.t194() << packet.t191() << packet.t202() << packet.t177()
                 << packet.t516() << packet.t521() << uint16_t(0x318) << result.t318;
            FN_SEND_LOGIN("wtlogin.login", body);
        }
    }
}
void QBaseClient::fetchQrcode() {
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

    // spdlog::info("send data: size={}", body.size());
    if(netService.write(body)) {
        this->listener.add(this->packet.sig.seq, [this](ByteArray& buffer) {
            bool retbool =
                this->loginHandler.parseQRCode(buffer, this->config.getQRCodeDir());
            if(retbool) {
                this->timer1.wait();
                this->queryQrcodeResult();
            }
        });
    }
}

void QBaseClient::queryQrcodeResult() {
    if(packet.sig.qrsig.size()) {
        /**
            const body = new writer_1.default()
                .writeU16(5)
                .writeU8(1)
                .writeU32(8)
                .writeU32(16)
                .writeTlv(this.sig.qrsig)
                .writeU64(0)
                .writeU8(8)
                .writeTlv(constants_1.BUF0)
                .writeU16(0)
                .read();
         */
        ByteArray body;
        body << uint16_t(5) << uint8_t(1) << uint32_t(8) << uint32_t(16)
             << BuildPackage(packet.sig.qrsig) << uint64_t(0) << uint8_t(8)
             << uint32_t(0) << uint16_t(0);
        // const pkt = buildCode2dPacket.call(this, 0x12, 0x6200, body);
        body = packet.buildCode2dPacket(0x12, 0x6200, body);
        // spdlog::info("send data: size={}", body.size());
        if(netService.write(body)) {
            this->listener.add(this->packet.sig.seq, [this](ByteArray& buffer) {
                auto result = this->loginHandler.parseQRCodeResult(buffer);
                this->qrcodeLogin(result);
            });
        }
    } else {
        spdlog::info("packet.sig.qrsig.size =0");
    }
}

}; // namespace Flee