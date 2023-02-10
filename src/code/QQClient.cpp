/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-10 15:52
 * @FilePath: \Flee\src\code\QQClient.cpp
 * @Description:
 */

#include "QQClient.h"
#include "ByteArray.h"
#include "QQConfig.h"
#include "tea.h"
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <spdlog/common.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <string>
#include <vector>

namespace Flee {
// bool isInit = true;

QQClient::QQClient(uint64_t uin)
    : config(uin), packet(uin, config.platform, config.getDeviceDir()) {

    std::string uin_str = std::to_string(uin);
    std::string dir     = config.getLogDir() + uin_str + ".log";

    std::vector<spdlog::sink_ptr> sinks = {
        std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
        std::make_shared<spdlog::sinks::rotating_file_sink_mt>(dir, 1024 * 1024 * 10,
                                                               10)
    };
    //<2.创建使用多个sink的单个logger，logger会把内容输出到不同位置，此处是控制台以及RotatingFileLog.txt
    std::string loggerName =
        std::to_string(config.platform) + ":" + std::to_string(uin);
    logger = std::make_shared<spdlog::logger>(loggerName, sinks.begin(), sinks.end());
}

bool QQClient::login() {
    uint32_t          id       = packet.getUin();
    ByteArray         password = packet.getPassword();
    std::stringstream ss;
    ss << config.getDir() << "/" << id << "/token";
    std::string dir = ss.str();
    if(password.empty()) {
        if(std::filesystem::exists(dir)) {
            ByteArray    token;
            std::fstream token_file{ dir };
            token_file >> token;
            // token 登录
            return tokenLogin(token);
        } else {
            // 扫码登录 或者 扫码后操作
            return packet.sig.qrsig.size() ? qrcodeLogin() : fetchQrcode();
        }
    } else {
        // 密码登录
        return passwordLogin(password);
    }
    return false;
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
/**
 * @brief
 *
 * @return true
 * @return false
 */
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
    body = buildCode2dPacket(0x31, 0x11100, body);
    /**
        this[FN_SEND](pkt).then(payload => {
            payload = tea.decrypt(payload.slice(16, -1), this[ECDH].share_key)
            const stream = Readable.from(payload, { objectMode: false })
            stream.read(54)
            const retcode = stream.read(1)[0]
            const qrsig = stream.read(stream.read(2).readUInt16BE())
            stream.read(2)
            const t = readTlv(stream)
            if (!retcode && t[0x17]) {
                this.sig.qrsig = qrsig
                this.emit("internal.qrcode", t[0x17])
            } else {
                this.emit("internal.error.qrcode", retcode, "获取二维码失败，请重试")
            }
        }).catch(() => this.emit("internal.error.network", -2, "server is busy"))
     */

    return false;
}

void QQClient::queryQrcodeResult() {
    if(!packet.sig.qrsig.size()) {
    } else {
        ByteArray body;
        body << uint16_t(5) << uint8_t(1) << uint32_t(16)
             << DataPacket(packet.sig.qrsig) << uint64_t(0) << uint8_t(8) << uint32_t(0)
             << uint16_t(0);
    }
}

ByteArray QQClient::buildLoginPacket(std::string cmd, const ByteArray& body,
                                     uint8_t type) {
    auto seq      = packet.sig.seq_pp();
    auto uin      = packet.getUin();
    auto cmdid    = 0x810;
    auto subappid = packet.apk.subid;
    logger->debug("send:{} seq:{}", cmd, seq);

    if(cmd == "") {
        uin      = 0;
        cmdid    = 0x812;
        subappid = APK::getApk(Platform::Watch).subid;
    }
    //  if (type === 2)
    ByteArray sso, temp, _temp_;
    if(type == 2) {
        /**
            body = new Writer()
                .writeU8(0x02)
                .writeU8(0x01)
                .writeBytes(this.sig.randkey)
                .writeU16(0x131)
                .writeU16(0x01)
                .writeTlv(this[ECDH].public_key)
                .writeBytes(tea.encrypt(body, this[ECDH].share_key))
        */
        temp << uint16_t((0x02 << 16) & 0x01) << packet.sig.randkey
             << uint32_t((0x131 << 16) & 0x01) << DataPacket(ecdh.getPublicKey())
             << Tea::encrypt(ecdh.getShareKey(), body);
        /**
            body = new Writer()
                .writeU8(0x02)
                .writeU16(29 + body.length) // 1 + 27 + body.length + 1
                .writeU16(8001)             // protocol ver
                .writeU16(cmdid)            // command id
                .writeU16(1)                // const
                .writeU32(uin)
                .writeU8(3)                 // const
                .writeU8(0x87)              // encrypt type 7:0 69:emp 0x87:4
                .writeU8(0)                 // const
                .writeU32(2)                // const
                .writeU32(0)                // app client ver
                .writeU32(0)                // const
                .writeBytes(body)
                .writeU8(0x03)
        */
        _temp_ << uint8_t(0x02) << uint16_t(29 + temp.size()) << uint16_t(8001)
               << uint16_t(cmdid) << uint16_t(1) << uint32_t(uin)
               << uint16_t((2 << 8) & 0x87) << uint8_t(0) << uint32_t(2) << uint64_t(0)
               << temp << uint8_t(0);
        temp.clear();
    }
    /**
        let sso = new Writer()
            .writeWithLength(
                new Writer()
                    .writeU32(this.sig.seq)
                    .writeU32(subappid)
                    .writeU32(subappid)
                    .writeBytes(Buffer.from(
                        [0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
                        0x00, 0x00, 0x00, 0x01, 0x00])
                    )
                    .writeWithLength(this.sig.tgt)
                    .writeWithLength(cmd)
                    .writeWithLength(this.sig.session)
                    .writeWithLength(this.device.imei)
                    .writeU32(4)
                    .writeU16(2)
                    .writeU32(4)
            )
            .writeWithLength(body)
            .read()
    */
    temp << uint32_t(packet.sig.seq) << uint32_t(subappid) << uint32_t(subappid)
         << ByteArray{ Byte{ 0x01 }, Byte{ 0x00 }, Byte{ 0x00 }, Byte{ 0x00 },
                       Byte{ 0x00 }, Byte{ 0x00 }, Byte{ 0x00 }, Byte{ 0x00 },
                       Byte{ 0x00 }, Byte{ 0x00 }, Byte{ 0x01 }, Byte{ 0x00 } }
         << DataPacketWithLength(packet.sig.tgt) << DataPacketWithLength(cmd)
         << DataPacketWithLength(packet.sig.session)
         << DataPacketWithLength(packet.device.imei) << uint32_t(4) << uint16_t(2)
         << uint32_t(4);
    sso << DataPacketWithLength(temp) << DataPacketWithLength(_temp_);
    temp.clear();
    _temp_.clear();
    /**
        if (type === 1)
            sso = tea.encrypt(sso, this.sig.d2key)
        else if (type === 2)
            sso = tea.encrypt(sso, BUF16)
    */
    if(type == 1) {
        sso = Tea::encrypt(packet.sig.d2key, sso);
    } else if(type == 2) {
        sso = Tea::encrypt(ByteArray(0), sso);
    }
    /**
        return new Writer()
        .writeWithLength(new Writer()
            .writeU32(0x0A)
            .writeU8(type)
            .writeWithLength(this.sig.d2)
            .writeU8(0)
            .writeWithLength(String(uin))
            .writeBytes(sso)
            .read()
        ).read()
     */
    _temp_ << uint32_t(0x0A) << uint8_t(type) << DataPacketWithLength(packet.sig.d2)
           << uint8_t(0) << DataPacketWithLength(std::to_string(uin)) << sso;
    sso.clear();
    temp << DataPacketWithLength(_temp_);
    _temp_.clear();
    return std::move(temp);
}

ByteArray QQClient::buildCode2dPacket(uint16_t cmdid, uint32_t head,
                                      const ByteArray& body) {
    ByteArray temp;
    /**
        body = new Writer()
            .writeU32(head)
            .writeU32(0x1000)
            .writeU16(0)
            .writeU32(0x72000000)
            .writeU32(timestamp())
            .writeU8(2)
            .writeU16(44 + body.length)
            .writeU16(cmdid)
            .writeBytes(Buffer.alloc(21))
            .writeU8(3)
            .writeU16(0)
            .writeU16(50)
            .writeU32(this.sig.seq + 1)
            .writeU64(0)
            .writeBytes(body)
            .writeU8(3)
            .read()
        return buildLoginPacket.call(this, "wtlogin.trans_emp", body)
     */
    temp << head << uint32_t(0x1000) << uint16_t(0) << uint32_t(0x72000000)
         << uint8_t(2) << uint16_t(44 + body.size()) << cmdid << ByteArray(21)
         << uint8_t(3) << uint16_t(0) << uint16_t(50) << uint32_t(packet.sig.seq + 1)
         << uint64_t(0) << body << uint8_t(3);
    return std::move(buildLoginPacket("wtlogin.trans_emp", temp));
}

QQClient::~QQClient() {}

}; // namespace Flee