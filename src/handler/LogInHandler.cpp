/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-03-04 20:57
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-03-31 16:14
 * @FilePath: \Flee\src\handler\LogInHandler.cpp
 * @Description:
 */
#include "LogInHandler.h"
#include "ByteArray.h"
#include "QQPackTlv.h"
#include <QRCode.h>
#include <cstdint>
#include <spdlog/spdlog.h>
#include <tea.h>

namespace Flee {

bool LogInHandler::parseQRCode(ByteArray& buffer, const std::string& filename) const {
    /**
        payload = tea.decrypt(payload.slice(16, -1), this[ECDH].share_key);
        const stream = stream_1.Readable.from(payload, { objectMode: false });
        stream.read(54);
     */
    buffer.discardExact(16);
    buffer.discardExact(-1);
    buffer = Tea::decrypt(packet.ecdh.getMaskedSharedKey(), buffer);
    buffer.discardExact(54);
    /**
    const retcode = stream.read(1)[0];
    const qrsig = stream.read(stream.read(2).readUInt16BE());
    stream.read(2);
     */
    uint8_t   retcode = buffer.read<uint8_t>();
    ByteArray qrsig   = buffer.readByteArray(buffer.read<uint16_t>());
    buffer.discardExact(2);
    /**
        const t = readTlv(stream);
        if (!retcode && t[0x17]) {
            this.sig.qrsig = qrsig;
            this.emit("internal.qrcode", t[0x17]);
        }
        else {
            this.emit("internal.error.qrcode", retcode, "获取二维码失败，请重试");
        }
     */
    auto t = QQPackTlv::readTlv(buffer);
    if((!retcode) && t.count(0x17)) {
        packet.sig.qrsig = qrsig;
        qrcode(filename, t[0x17]);
        spdlog::info("The QR code picture has been saved to: {}", filename);
        return true;
    } else {
        spdlog::error("Failed to obtain the QR code. Please try again.");
        return false;
    }
}

void LogInHandler::qrcode(const std::string& filename, const ByteArray& data) const {
    std::ofstream ofs;
    ofs.open(filename, std::ios::binary);
    if(ofs.is_open()) {
        ofs << data;
    }
    ofs.close();
    QRCode qrcode;
    qrcode.encode(data);
    spdlog::info("\n{}", qrcode.toString());
}

QRCodeResult LogInHandler::parseQRCodeResult(ByteArray& buffer) const {
    /**
    payload = tea.decrypt(payload.slice(16, -1), this[ECDH].share_key);
    const stream = stream_1.Readable.from(payload, { objectMode: false });
    stream.read(48);
    let len = stream.read(2).readUInt16BE();
    */
    buffer.discardExact(16);
    buffer.discardExact(-1);
    buffer = Tea::decrypt(packet.ecdh.getMaskedSharedKey(), buffer);
    buffer.discardExact(48);
    uint16_t len = buffer.read<uint16_t>();
    /**
    if (len > 0) {
        len--;
        if (stream.read(1)[0] === 2) {
            stream.read(8);
            len -= 8;
        }
        if (len > 0)
            stream.read(len);
    }
     */
    if(len > 0) {
        len--;
        if(buffer.read<uint8_t>() == 2) {
            buffer.discardExact(8);
            len -= 8;
        }
        if(len > 0) {
            buffer.discardExact(len);
        }
    }
    /**
    stream.read(4);
    retcode = stream.read(1)[0];
     */
    buffer.discardExact(4);
    uint8_t retcode = buffer.read<uint8_t>();
    /**
    if (retcode === 0) {
        stream.read(4);
        uin = stream.read(4).readUInt32BE();
        stream.read(6);
        const t = readTlv(stream);
        t106 = t[0x18];
        t16a = t[0x19];
        t318 = t[0x65];
        tgtgt = t[0x1e];
    }
     */
    if(retcode == 0) {
        buffer.discardExact(4);
        uint32_t uin = buffer.read<uint32_t>();
        buffer.discardExact(6);
        auto t = QQPackTlv::readTlv(buffer);
        buffer.clear();
        return { retcode, uin, t[0x18], t[0x19], t[0x65], t[0x1e] };
    }
    return {};
}
uint8_t LogInHandler::decodeLoginResponse(ByteArray& buffer) const {
    /**
    payload = tea.decrypt(payload.slice(16, payload.length - 1), this[ECDH].share_key);
    const r = stream_1.Readable.from(payload, { objectMode: false });
    r.read(2);
    const type = r.read(1).readUInt8();
    r.read(2);
    const t = readTlv(r);
     */
    buffer.discardExact(16);
    buffer.discardExact(-1);
    buffer = Tea::decrypt(packet.ecdh.getMaskedSharedKey(), buffer);
    buffer.discardExact(2);
    uint8_t type = buffer.read<uint8_t>();
    buffer.discardExact(2);
    auto t = QQPackTlv::readTlv(buffer);

    switch(type) {
        case 204:
            packet.sig.t104 = t[0x104];
            spdlog::info("internal.verbose: unlocking...");
            return type;
        case 0:
            packet.sig.t104.clear();
            packet.sig.t174.clear();
            // TODO：is online
            return type;
        case 15:
        case 16:
            spdlog::error("internal.error.token");
            return type;
        case 2:
            packet.sig.t104 = t[0x104];
            if(t.count(0x192)) {
                spdlog::info("{}", t[0x192].toString());
            } else {
                spdlog::error(
                    "internal.error.login type= {};[登陆失败]未知格式的验证码", type);
            }
            return type;
        case 160:
            if((t.count(0x204 == 0)) && (t.count(0x174) == 0)) {
                spdlog::info("internal.verbose, 已向密保手机发送短信验证码");
                return {};
            }
            std::string phone;
            if((t.count(0x174) != 0) && (t.count(0x178) != 0)) {
                packet.sig.t104 = t[0x104];
                packet.sig.t174 = t[0x174];

                phone = t[0x178].toString().substr(t[0x178].find(Byte('\x0b')) + 1, 11);
            }
            spdlog::info("internal.verify {} {}",
                         t.count(0x204) == 0 ? "" : t[0x204].toString(), phone);
            return type;
    }
    if(t.count(0x149) != 0) {
        auto stream = t[0x149];
        stream.discardExact(2);
        auto title   = stream.readString(stream.read<uint16_t>());
        auto content = stream.readString(stream.read<uint16_t>());
        spdlog::error("internal.error.login type={} [{}]:{}", type, title, content);
    }
    if(t.count(0x146) != 0) {
        auto stream = t[0x146];
        stream.discardExact(4);
        auto title   = stream.readString(stream.read<uint16_t>());
        auto content = stream.readString(stream.read<uint16_t>());
        spdlog::error("internal.error.login type={} [{}]:{}", type, title, content);
    }
    spdlog::error("internal.error.login: [登陆失败]未知错误");
    return type;
}

} // namespace Flee