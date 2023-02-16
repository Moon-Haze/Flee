/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-02-11 15:15
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-16 13:23
 * @FilePath: \Flee\src\code\QQPackTlv.cpp
 * @Description:
 */
#include "QQPackTlv.h"
#include "ByteArray.h"
#include "DataPacket.h"
#include "ParsingException.h"
#include "QQConfig.h"
#include "tea.h"
#include <boost/iostreams/copy.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/filter/zlib.hpp>
#include <boost/iostreams/filtering_stream.hpp>
#include <boost/iostreams/stream.hpp>
#include <cstdint>
#include <spdlog/spdlog.h>
#include <string>

namespace Flee {

void QQPackTlv::setLogger(std::shared_ptr<spdlog::logger> logger) {
    QQPackTlv::logger = logger;
}

PacketListener& QQPackTlv::getPacketListener() {
    return listener;
}
ByteArray QQPackTlv::buildLoginPacket(std::string cmd, const ByteArray& body,
                                      uint8_t type) {
    int16_t  seq      = this->sig.seq_pp();
    uint32_t uin      = this->getUin();
    uint16_t cmdid    = 0x810;
    uint32_t subappid = this->apk.subid;
    spdlog::info("send:{} seq:{}", cmd, seq);
    /**
        if (cmd === "wtlogin.trans_emp") {
            uin = 0;
            cmdid = 0x812;
            subappid = (0, device_1.getApkInfo)(device_1.Platform.Watch).subid;
        }
     */
    if(cmd == "wtlogin.trans_emp") {
        uin      = 0;
        cmdid    = 0x812;
        subappid = APK::getApk(Platform::Watch).subid;
    }
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
        temp << uint16_t((0x02 << 8) | 0x01) << this->sig.randkey
             << uint32_t((0x131 << 16) | 0x01) << BuildPackage(ecdh.getPublicKey())
             << Tea::encrypt(ecdh.getShareKey(), body);
        // spdlog::info("encrypt {}", temp.toHex());
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
        _temp_ << uint8_t(0x02) << uint16_t(29 + temp.size()) << uint16_t(8001) << cmdid
               << uint16_t(1) << uint32_t(uin) << uint16_t((3 << 8) | 0x87)
               << uint8_t(0) << uint32_t(2) << uint64_t(0) << temp << uint8_t(0x03);
        // spdlog::info("size {}", _temp_.toHex());
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
    temp << uint32_t(this->sig.seq) << uint32_t(subappid) << uint32_t(subappid)
         << ByteArray{ Byte{ 0x01 }, Byte{ 0x00 }, Byte{ 0x00 }, Byte{ 0x00 },
                       Byte{ 0x00 }, Byte{ 0x00 }, Byte{ 0x00 }, Byte{ 0x00 },
                       Byte{ 0x00 }, Byte{ 0x00 }, Byte{ 0x01 }, Byte{ 0x00 } }
         << BuildPackageWithLength(this->sig.tgt) << BuildPackageWithLength(cmd)
         << BuildPackageWithLength(this->sig.session)
         << BuildPackageWithLength(this->device.imei) << uint32_t(4) << uint16_t(2)
         << uint32_t(4);
    sso << BuildPackageWithLength(temp) << BuildPackageWithLength(_temp_);
    temp.clear();
    _temp_.clear();
    /**
        if (type === 1)
            sso = tea.encrypt(sso, this.sig.d2key)
        else if (type === 2)
            sso = tea.encrypt(sso, BUF16)
    */
    if(type == 1) {
        sso = Tea::encrypt(this->sig.d2key, sso);
    } else if(type == 2) {
        sso = Tea::encrypt(ByteArray(16), sso);
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
    _temp_ << uint32_t(0x0A) << type << BuildPackageWithLength(this->sig.d2)
           << uint8_t(0) << BuildPackageWithLength(std::to_string(uin)) << sso;
    sso.clear();
    temp << BuildPackageWithLength(_temp_);
    _temp_.clear();
    return std::move(temp);
}

ByteArray QQPackTlv::buildCode2dPacket(uint16_t cmdid, uint32_t head,
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
     */
    temp << head << uint32_t(0x1000) << uint16_t(0) << uint32_t(0x72000000)
         << uint32_t(currentTimeSeconds()) << uint8_t(2) << uint16_t(44 + body.size())
         << cmdid << ByteArray(21) << uint8_t(3) << uint16_t(0) << uint16_t(50)
         << uint32_t(this->sig.seq + 1) << uint64_t(0) << body << uint8_t(3);
    spdlog::info("{} {}", __FUNCTION__, temp.toHex());
    // return buildLoginPacket.call(this, "wtlogin.trans_emp", body)
    return std::move(buildLoginPacket("wtlogin.trans_emp", temp));
}

void QQPackTlv::parseFlagPacket(ByteArray& packet) {

    // spdlog::info("{} packet: {}", __FUNCTION__, packet.toHex());
    // const flag = pkt.readUInt8(4);
    packet.discardExact(4);
    auto flag = packet.read<uint8_t>();

    packet.discardExact(1);
    // spdlog::info("flag = {}", flag);

    // const encrypted = pkt.slice(pkt.readUInt32BE(6) + 6);
    packet.discardExact(packet.read<int32_t>() - 4);
    /**
        let decrypted;
        switch (flag) {
            case 0:
                decrypted = encrypted;
                break;
            case 1:
                decrypted = tea.decrypt(encrypted, this.sig.d2key);
                break;
            case 2:
                decrypted = tea.decrypt(encrypted, constants_1.BUF16);
                break;
            default:
                this.emit("internal.error.token");
                throw new Error("unknown flag:" + flag);
        }
     */
    ByteArray decrypted;
    switch(flag) {
        case 0: {
            decrypted = packet;
            break;
        }
        case 1: {
            decrypted = Tea::decrypt(this->sig.d2key, packet);
            break;
        }
        case 2: {
            decrypted = Tea::decrypt(ByteArray(16), packet);
            break;
        }
        default: {
            logger->error("{} unknown flag: {}", __FUNCTION__, flag);
            throw ParsingException("unknown flag:" + std::to_string(flag),
                                   ParsingException::FlagError);
        }
    }
    packet.clear();
    // const sso = await parseSso.call(this, decrypted);
    auto sso = parseSsoPacket(decrypted);
    logger->info("recv: {} seq: {}", sso.cmd, sso.seq);
    /**
        if (this[HANDLERS].has(sso.seq))
            this[HANDLERS].get(sso.seq)?.(sso.payload);
        else
            this.emit("internal.sso", sso.cmd, sso.payload, sso.seq);
     */
    if(listener.contain(sso.seq)) {
        listener.get(sso.seq)(sso.data);
    } else {
        ByteArray temp(sso.data);
        parseFlagPacket(temp);
    }
}
DataPacket QQPackTlv::parseSsoPacket(ByteArray& packet) {

    spdlog::info("{} packet: {}", __FUNCTION__, packet.toHex());
    /**
00 00 00 36 //54=9*4+18=36+18
00 00 08 BF
00 00 00 00
00 00 00 04
00 00 00 16
43 6C 69 65 6E74 2E 43 6F 72 72 65 63 74 54 69 6D 65 //18
00 00 00 08
2E 99 74 20
00 00 00 00
00 00 00 04
00 00 00 08 //10*4+18=58

63 EB 82 F3

flag=0
payload = 63 EB 82 F3
     */
    /**
00 00 00 36 //54=36+18
00 00 08 BF
00 00 00 00
*/

    ByteArray bytes   = packet.readByteArray(packet.read<uint32_t>() - 4);
    int32_t   seq     = bytes.read<int32_t>();
    int32_t   retcode = bytes.read<int32_t>();
    spdlog::info("req: {} retcode: {}", seq, retcode);
    if(retcode != 0) {
        logger->error("unsuccessful retcode: {}", retcode);
        throw ParsingException("unsuccessful retcode: " + std::to_string(retcode),
                               ParsingException::ReturnCodeError);
    }
    /**
    00 00 00 04
    00 00 00 16 //22-4=18
    43 6C 69 65 6E 74 2E 43 6F 72 72 65 63 74 54 69 6D 65
    00 00 00 08
    2E 99 74 20
    00 00 00 00 flag

    00 00 00 04
    00 00 00 08

    63 EB 82 F3
     */
    uint32_t    offset = bytes.read<uint32_t>();
    uint32_t    len    = bytes.read<uint32_t>();
    std::string cmd    = bytes.readString(len - offset);
    bytes.discardExact(bytes.read<uint32_t>() - 4);
    int32_t flag = bytes.read<int32_t>();
    logger->info("{} flag:{}", __FUNCTION__, flag);
    switch(flag) {
        case 0: {
            // 已完成，不做任何处理即可
            // payload = buf.slice(headlen + 4);
            break;
        }
        case 1: {
            // payload = await(0, constants_1.unzip)(buf.slice(headlen + 4));
            boost::iostreams::filtering_streambuf<boost::iostreams::input> inbuf;
            inbuf.push(boost::iostreams::zlib_decompressor());
            inbuf.push(boost::iostreams::basic_array_source<char>(
                reinterpret_cast<char*>(packet.data()), packet.size()));
            packet.clear();
            std::stringstream ss_decomp;
            boost::iostreams::copy(inbuf, ss_decomp);
            packet << ss_decomp.str();
            break;
        }
        case 8: {
            /**
             * TODO:
             * 这一部分未完成，还在测试，将来会补全，主要是这一部分的数据分割还不确定
             *
             */
            // payload = buf.slice(headlen);
            bytes.discardExact(4);
            if(bytes.size() == 4) {
                packet = bytes + packet;
            }
            logger->info("compressed flag: {}", flag);
            break;
        }
        default: {
            logger->error("unknown compressed flag: {}", flag);
            throw ParsingException("unknown compressed flag: " + std::to_string(flag),
                                   ParsingException::FlagError);
        }
    }
    return { seq, packet, cmd };
}
}; // namespace Flee