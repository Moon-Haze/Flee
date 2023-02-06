#include "PackTlv.h"

#include "ByteArray.h"
#include "DevInfo.pb.h"
#include "QQConfig.h"
#include "QQProtocol.h"
#include "constants.h"
#include "tea.h"
#include <algorithm>
#include <cstdint>
#include <string>
#include <utility>

namespace Flee {

template class DataPacket<uint16_t>;

template <typename T>
DataPacket<T>::DataPacket(const ByteArray& data, T offset)
    : data(data), offset(offset) {
    static_assert(std::is_arithmetic<T>::value | std::is_same<T, char>::value
                      | std::is_same<T, std::byte>::value,
                  "T must be a numeric,char,byte type");
}

template <typename T>
DataPacket<T>::DataPacket(const std::string& data, T offset)
    : data(std::move(toByteArray(data))), offset(offset) {}

// template <typename T, typename Z>
// DataPacket<T>::DataPacket<Z>(Z data, T offset = 0) {}

template <typename T>
T DataPacket<T>::getOffset() const {
    return offset;
}

template <typename T>
const ByteArray& DataPacket<T>::getData() const {
    return data;
}

template <typename T = uint16_t>
ByteArray& operator<<(ByteArray& array, const DataPacket<T>& packet) {
    array << static_cast<T>(packet.getData().size() + packet.getOffset())
          << packet.getData();
    return array;
}

template ByteArray& operator<< <uint16_t>(ByteArray&                  array,
                                          const DataPacket<uint16_t>& packet);

PackTlv::PackTlv(const QQInfo& info) : info(info) {}

ByteArray PackTlv::t01() const {
    /**
        return new Writer()
            .writeU16(1) // ip ver
            .writeBytes(crypto.randomBytes(4))
            .writeU32(this.uin)
            .write32(Date.now() & 0xffffffff)
            .writeBytes(Buffer.alloc(4)) //ip
            .writeU16(0)
    */
    ByteArray temp;
    temp << int32_t(0x01 << 16) << uint16_t(1) << getRandomByteArray(4)
         << uint32_t(info.getUin()) << int32_t(currentTimeMillis() & 0xffffffff)
         << uint32_t(0) << UINT64_C(0);
    int16_t size = temp.size() - 4;
    temp[2]      = Byte((size >> 8) & 0xff);
    temp[3]      = Byte(size & 0xff);
    return std::move(temp);
}
ByteArray PackTlv::t08() const {
    /**
        return new Writer()
            .writeU16(0)
            .writeU32(2052)
            .writeU16(0)
    */
    ByteArray temp;
    temp << uint32_t(0x08 << 16) << uint16_t(0) << uint32_t(2052)
         << uint16_t(0);
    int16_t size = temp.size() - 4;
    temp[2]      = Byte((size >> 8) & 0xff);
    temp[3]      = Byte(size & 0xff);
    return std::move(temp);
}

ByteArray PackTlv::t16() const {
    /*
    const apk = (0, device_1.getApkInfo)(device_1.Platform.Watch);
    return new writer_1.default()
        .writeU32(7)
        .writeU32(apk.appid)
        .writeU32(apk.subid)
        .writeBytes(this.device.guid)
        .writeTlv(apk.id)
        .writeTlv(apk.ver)
        .writeTlv(apk.sign);
    */

    APK       apk = APK::getApk(Platform::Watch);
    ByteArray temp;
    temp << uint32_t(0x16 << 16) << uint32_t(7) << uint32_t(apk.appid)
         << uint32_t(apk.subid) << info.device.guid << apk.id << apk.ver
         << apk.sign;
    int16_t size = temp.size() - 4;
    temp[2]      = Byte((size >> 8) & 0xff);
    temp[3]      = Byte(size & 0xff);
    return std::move(temp);
}
ByteArray PackTlv::t18() const {
    /**
    return new Writer()
        .writeU16(1) // ping ver
        .writeU32(1536)
        .writeU32(this.apk.appid)
        .writeU32(0) // app client ver
        .writeU32(this.uin)
        .writeU16(0)
        .writeU16(0)
    */
    ByteArray temp;
    temp << uint32_t(0x18 << 16) << uint32_t(1) << uint32_t(1536)
         << uint32_t(info.apk.appid) << uint32_t(0) << uint32_t(info.getUin())
         << uint32_t(0);
    int16_t size = temp.size() - 4;
    temp[2]      = Byte((size >> 8) & 0xff);
    temp[3]      = Byte(size & 0xff);
    return std::move(temp);
}

ByteArray PackTlv::t1B() const {
    /*
    return new writer_1.default()
        .writeU16(1) // ping ver
        .writeU32(1536)
        .writeU32(this.apk.appid)
        .writeU32(0) // app client ver
        .writeU32(this.uin)
        .writeU16(0)
        .writeU16(0);
    */
    ByteArray temp;
    temp << uint32_t(0x1B << 16) << uint16_t(1) << uint32_t(1536)
         << uint32_t(info.apk.appid) << uint32_t(0) << uint32_t(info.getUin())
         << uint32_t(0);
    int16_t size = temp.size() - 4;
    temp[2]      = Byte((size >> 8) & 0xff);
    temp[3]      = Byte(size & 0xff);
    return std::move(temp);
}

ByteArray PackTlv::t1D() const {
    /**
        return new Writer()
            .writeU8(1)
            .writeU32(184024956)
            .writeU32(0)
            .writeU8(0)
            .writeU32(0)
    */
    ByteArray temp;
    temp << uint32_t(0x1D << 16) << uint8_t(1) << uint32_t(184024956)
         << uint32_t(0) << uint8_t(0) << uint32_t(0);
    int16_t size = temp.size() - 4;
    temp[2]      = Byte((size >> 8) & 0xff);
    temp[3]      = Byte(size & 0xff);
    return std::move(temp);
}
ByteArray PackTlv::t1F() const {
    /**
        return new Writer()
            .writeU8(0)
            .writeTlv("android")
            .writeTlv("7.1.2")
            .writeU16(2)
            .writeTlv("China Mobile GSM")
            .writeTlv(BUF0)
            .writeTlv("wifi")
    */
    ByteArray temp;
    temp << uint32_t(0x1F << 16) << uint8_t(0) << DataPacket("android")
         << DataPacket("7.1.2") << uint16_t(2) << DataPacket("China Mobile GSM")
         << DataPacket(ByteArray_0) << DataPacket("wifi");
    int16_t size = temp.size() - 4;
    temp[2]      = Byte((size >> 8) & 0xff);
    temp[3]      = Byte(size & 0xff);
    return std::move(temp);
}
ByteArray PackTlv::t33() const {
    /**
        return new Writer().writeBytes(this.device.guid)
    */
    ByteArray temp;
    temp << uint32_t((0x33 << 16) & info.device.guid.size())
         << info.device.guid;
    return std::move(temp);
}
ByteArray PackTlv::t35() const {
    /**
    return new Writer().writeU32(8)
    */
    ByteArray temp;
    temp << uint32_t((0x35 << 16) & 4) << uint32_t(8);
    return std::move(temp);
}
ByteArray PackTlv::t100(uint8_t emp) const {
    /**
        return new Writer()
            .writeU16(1) // db buf ver
            .writeU32(7) // sso ver, dont over 7
            .writeU32(this.apk.appid)
            .writeU32(emp ? 2 : this.apk.subid)
            .writeU32(0) // app client ver
            .writeU32(this.apk.sigmap)
    */
    ByteArray temp;
    temp << uint32_t(0x100 << 16) << uint16_t(1) << uint32_t(7)
         << uint32_t(info.apk.appid) << uint16_t(emp ? 2 : info.apk.subid)
         << uint32_t(0) << info.apk.sigmap;
    int16_t size = temp.size() - 4;
    temp[2]      = Byte((size >> 8) & 0xff);
    temp[3]      = Byte(size & 0xff);
    return std::move(temp);
}
ByteArray PackTlv::t104() const {
    /**
        return new Writer().writeBytes(this.sig.t104)
    */
    ByteArray temp;
    temp << uint32_t((0x35 << 16) & info.secrets.t104.size())
         << info.secrets.t104;
    return std::move(temp);
}
ByteArray PackTlv::t106() const {
    /**
        const body = new Writer()
            .writeU16(4) // tgtgt ver
            .writeBytes(crypto.randomBytes(4))
            .writeU32(7) // sso ver
            .writeU32(this.apk.appid)
            .writeU32(0) // app client ver
            .writeU64(this.uin)
            .write32(Date.now() & 0xffffffff)
            .writeBytes(Buffer.alloc(4)) // dummy ip
            .writeU8(1) // save password
            .writeBytes(md5pass)
            .writeBytes(this.sig.tgtgt)
            .writeU32(0)
            .writeU8(1) // guid available
            .writeBytes(this.device.guid)
            .writeU32(this.apk.subid)
            .writeU32(1) // login type password
            .writeTlv(String(this.uin))
            .writeU16(0)
            .read()
    */
    ByteArray temp, _temp_;
    temp << uint16_t(4) << getRandomByteArray(4) << uint32_t(7)
         << info.apk.appid << info.getUin()
         << int32_t(currentTimeMillis() & 0xffffffff)
         << ByteArray(4, Byte(0x00)) << uint8_t(1) << info.getPassword()
         << info.secrets.tgtgt << uint32_t(0) << uint8_t(1) << info.device.guid
         << info.apk.subid << uint32_t(1)
         << DataPacket(std::to_string(info.getUin())) << uint16_t(0);
    /**
        const buf = Buffer.alloc(4)
        buf.writeUInt32BE(this.uin)
        const key = md5(Buffer.concat([
            md5pass, Buffer.alloc(4), buf
        ]))
        return new Writer().writeBytes(tea.encrypt(body, key))
    */
    ByteArray key = info.getPassword();
    key << uint32_t(0) << info.getUin();
    _temp_ = Tea::encrypt(key, temp);
    temp.clear();
    temp << uint16_t(0x106) << uint16_t(_temp_.size()) << _temp_;
    return std::move(temp);
}
ByteArray PackTlv::t107() const {
    /**
        return new Writer()
            .writeU16(0)    // pic type
            .writeU8(0)     // captcha type
            .writeU16(0)    // pic size
            .writeU8(1)     // ret type
    */
    ByteArray temp;
    temp << uint32_t(0x107 << 16) << uint16_t(0) << uint8_t(0) << uint16_t(0)
         << uint8_t(1);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray PackTlv::t109() const {
    /**
        return new Writer().writeBytes(md5(this.device.imei))
    */
    ByteArray temp;
    temp << uint32_t(0x109 << 16) << md5(info.device.imei);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray PackTlv::t10a() const {
    /**
        return new Writer().writeBytes(this.sig.tgt)
    */
    ByteArray temp;
    temp << uint32_t((0x10a << 16) & info.secrets.tgt.size())
         << info.secrets.tgt;
    return std::move(temp);
}
ByteArray PackTlv::t116() const {
    /**
        return new Writer()
            .writeU8(0)
            .writeU32(this.apk.bitmap)
            .writeU32(0x10400) // sub sigmap
            .writeU8(1) // size of app id list
            .writeU32(1600000226) // app id list[0]
    */
    ByteArray temp;
    temp << uint32_t(0x116 << 16) << uint8_t(0) << info.apk.bitmap
         << uint32_t(0x10400) << uint8_t(1) << uint32_t(1600000226);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray PackTlv::t124() const {
    /**
        return new Writer()
            .writeTlv(this.device.os_type.slice(0, 16))
            .writeTlv(this.device.version.release.slice(0, 16))
            .writeU16(2) // network type
            .writeTlv(this.device.sim.slice(0, 16))
            .writeU16(0)
            .writeTlv(this.device.apn.slice(0, 16))
    */
    ByteArray temp;
    temp << uint32_t(0x124 << 16) << DataPacket(info.device.osType)
         << DataPacket(info.device.version.release) << uint16_t(2)
         << DataPacket(info.device.simInfo) << uint16_t(0)
         << DataPacket(info.device.apn);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray PackTlv::t128() const {
    /**
        return new Writer()
            .writeU16(0)
            .writeU8(0) // guid new
            .writeU8(1) // guid available
            .writeU8(0) // guid changed
            .writeU32(16777216) // guid flag
            .writeTlv(this.device.model.slice(0, 32))
            .writeTlv(this.device.guid.slice(0, 16))
            .writeTlv(this.device.brand.slice(0, 16))
    */
    ByteArray temp;
    temp << uint32_t(0x128 << 16) << uint16_t(0) << uint8_t(0) << uint8_t(1)
         << uint8_t(0) << uint32_t(16777216) << DataPacket(info.device.model)
         << DataPacket(info.device.guid) << DataPacket(info.device.brand);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray PackTlv::t141() const {
    /**
        return new Writer()
            .writeU16(1) // ver
            .writeTlv(this.device.sim)
            .writeU16(2) // network type
            .writeTlv(this.device.apn)
    */
    ByteArray temp;
    temp << uint32_t(0x141 << 16) << uint16_t(1)
         << DataPacket(info.device.simInfo) << uint16_t(2)
         << DataPacket(info.device.apn);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray PackTlv::t142() const {
    /**
        return new Writer()
            .writeU16(0)
            .writeTlv(this.apk.id.slice(0, 32))
    */
    ByteArray temp;
    temp << uint32_t((0x142 << 16) & (info.apk.id.size() + 2))
         << DataPacket(info.apk.id);
    return std::move(temp);
}
ByteArray PackTlv::t143() const {
    /**
        return new Writer().writeBytes(this.sig.d2)
    */
    ByteArray temp;
    temp << uint32_t((0x143 << 16) & info.secrets.d2.size()) << info.secrets.d2;
    return std::move(temp);
}
ByteArray PackTlv::t144() const {
    /**
        const body = new Writer()
            .writeU16(5) // tlv cnt
            .writeBytes(packTlv.call(this, 0x109))
            .writeBytes(packTlv.call(this, 0x52d))
            .writeBytes(packTlv.call(this, 0x124))
            .writeBytes(packTlv.call(this, 0x128))
            .writeBytes(packTlv.call(this, 0x16e))
        return new Writer().writeBytes(tea.encrypt(body.read(), this.sig.tgtgt))
    */
    ByteArray temp;
    temp << uint16_t(0) << t109() << t52d() << t124() << t128() << t16e();

    temp = toByteArray(uint32_t((0x142 << 16)))
           + Tea::encrypt(info.secrets.tgtgt, temp);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray PackTlv::t145() const {
    /**
        return new Writer().writeBytes(this.device.guid)
    */
    ByteArray temp;
    temp << uint32_t((0x145 << 16) & info.device.guid.size())
         << info.device.guid;
    return std::move(temp);
}
ByteArray PackTlv::t147() const {
    /**
        return new Writer()
            .writeU32(this.apk.appid)
            .writeTlv(this.apk.ver.slice(0, 5))
            .writeTlv(this.apk.sign)
    */
    ByteArray temp;
    temp << uint32_t((0x147 << 16)) << uint32_t(info.apk.appid)
         << DataPacket(info.apk.ver) << DataPacket(info.apk.sign);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray PackTlv::t154() const {
    /**
        return new Writer().writeU32(this.sig.seq + 1)
    */
    ByteArray temp;
    temp << uint32_t((0x154 << 16) & 4) << uint32_t(info.secrets.seq + 1);
    return std::move(temp);
}
ByteArray PackTlv::t16e() const {
    /**
        return new Writer().writeBytes(this.device.model)
    */
    ByteArray temp;
    temp << uint32_t((0x16e << 16) & info.device.model.size())
         << info.device.model;
    return std::move(temp);
}
ByteArray PackTlv::t174() const {
    /**
        return new Writer().writeBytes(this.sig.t174)
    */
    ByteArray temp;
    temp << uint32_t((0x174 << 16) & info.secrets.t174.size())
         << info.secrets.t174;
    return std::move(temp);
}
ByteArray PackTlv::t177() const {
    /**
        return new Writer()
            .writeU8(0x01)
            .writeU32(this.apk.buildtime)
            .writeTlv(this.apk.sdkver)
    */
    ByteArray temp;
    temp << uint32_t(0x177 << 16) << uint8_t(0x01) << info.apk.buildTime
         << DataPacket(info.apk.sdkver);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray PackTlv::t17a() const {
    /**
        return new Writer().writeU32(9)
    */
    ByteArray temp;
    temp << uint32_t((0x17a << 16) & 4) << uint32_t(9);
    return std::move(temp);
}
ByteArray PackTlv::t17c(const ByteArray& code) const {
    /**
        return new Writer().writeTlv(code)
    */
    ByteArray temp;
    temp << uint32_t((0x17c << 16) & code.size() + 2) << DataPacket(code);
    return {};
}
ByteArray PackTlv::t187() const {
    /**
        return new Writer().writeBytes(md5(this.device.mac_address))
    */
    ByteArray temp;
    temp << uint32_t(0x187 << 16) << md5(info.device.mac_address);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray PackTlv::t188() const {
    /**
        return new Writer().writeBytes(md5(this.device.android_id))
    */
    ByteArray temp;
    temp << uint32_t(0x188 << 16) << md5(info.device.android_id);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray PackTlv::t191() const {
    /**
        return new Writer().writeU8(0x82)
    */
    ByteArray temp;
    temp << uint32_t((0x191 << 16) & 1) << uint8_t(0x82);
    return std::move(temp);
}
ByteArray PackTlv::t193(const ByteArray& ticket) const {
    /**
        return new Writer().writeBytes(ticket)
    */
    ByteArray temp;
    temp << uint32_t((0x193 << 16) & ticket.size()) << ticket;
    return std::move(temp);
}
ByteArray PackTlv::t194() const {
    /**
        return new Writer().writeBytes(this.)
    */
    ByteArray temp;
    temp << uint32_t((0x194 << 16) & info.device.imei.size())
         << info.device.imei;
    return std::move(temp);
}
ByteArray PackTlv::t197() const {
    /**
        return new Writer().writeTlv(Buffer.alloc(1))
    */
    ByteArray temp;
    temp << uint32_t((0x197 << 16) & 3) << uint16_t(1) << uint8_t(0);
    return std::move(temp);
}
ByteArray PackTlv::t198() const {
    /**
        return new Writer().writeTlv(Buffer.alloc(1))
    */
    ByteArray temp;
    temp << uint32_t((0x198 << 16) & 3) << uint16_t(1) << uint8_t(0);
    return std::move(temp);
}
ByteArray PackTlv::t202() const {
    /**
        return new Writer()
            .writeTlv(this.device.wifi_bssid.slice(0, 16))
            .writeTlv(this.device.wifi_ssid.slice(0, 32))
    */
    ByteArray temp;
    temp << uint32_t(0x202 << 16) << DataPacket(info.device.wifi_bssid)
         << DataPacket(info.device.wifi_ssid);
    return std::move(temp);
}
ByteArray PackTlv::t400() const {
    /**
        return new Writer()
            .writeU16(1)
            .writeU64(this.uin)
            .writeBytes(this.device.guid)
            .writeBytes(crypto.randomBytes(16))
            .write32(1)
            .write32(16)
            .write32(Date.now() & 0xffffffff)
            .writeBytes(Buffer.alloc(0))
    */
    ByteArray temp;
    temp << uint32_t(0x400 << 16) << uint16_t(1) << info.getUin()
         << info.device.guid << getRandomByteArray(16) << int32_t(1)
         << int32_t(16) << int32_t(currentTimeMillis() & 0xffffffff);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray PackTlv::t401() const {
    /**
        return new Writer().writeBytes(crypto.randomBytes(16))
    */
    ByteArray temp;
    temp << uint32_t(0x401 << 16) << uint16_t(1) << info.getUin()
         << info.device.guid << getRandomByteArray(16);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray PackTlv::t511() const {
    /**
        const domains = new Set<Domain>([
            "aq.qq.com",
            "buluo.qq.com",
            "connect.qq.com",
            "docs.qq.com",
            "game.qq.com",
            "gamecenter.qq.com",
            // "graph.qq.com",
            "haoma.qq.com",
            "id.qq.com",
            // "imgcache.qq.com",
            "kg.qq.com",
            "mail.qq.com",
            "mma.qq.com",
            "office.qq.com",
            // "om.qq.com",
            "openmobile.qq.com",
            "qqweb.qq.com",
            "qun.qq.com",
            "qzone.qq.com",
            "ti.qq.com",
            "v.qq.com",
            "vip.qq.com",
            "y.qq.com",
        ])
    */
    std::vector<std::string> domains = {
        "aq.qq.com",
        "buluo.qq.com",
        "connect.qq.com",
        "docs.qq.com",
        "game.qq.com",
        "gamecenter.qq.com",
        // "graph.qq.com",
        "haoma.qq.com",
        "id.qq.com",
        // "imgcache.qq.com",
        "kg.qq.com",
        "mail.qq.com",
        "mma.qq.com",
        "office.qq.com",
        // "om.qq.com",
        "openmobile.qq.com",
        "qqweb.qq.com",
        "qun.qq.com",
        "qzone.qq.com",
        "ti.qq.com",
        "v.qq.com",
        "vip.qq.com",
        "y.qq.com",
    };
    /**
        const stream = new Writer().writeU16(domains.size)
        for (let v of domains)
            stream.writeU8(0x01).writeTlv(v)
        return stream
    */
    ByteArray temp;
    temp << uint32_t(0x511 << 16) << uint16_t(domains.size());
    for(std::string& item : domains) {
        temp << uint8_t(0x01) << DataPacket(item);
    }
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray PackTlv::t516() const {
    /**
        return new Writer().writeU32(0)
    */
    ByteArray temp;
    temp << uint32_t((0x516 << 16) & 4) << uint32_t(0);
    return std::move(temp);
}
ByteArray PackTlv::t521() const {
    /**
        return new Writer()
            .writeU32(0) // product type
            .writeU16(0) // const
    */
    ByteArray temp;
    temp << uint32_t((0x521 << 16) & 6) << uint32_t(0) << uint16_t(0);
    return std::move(temp);
}
ByteArray PackTlv::t525() const {
    /**
        return new Writer()
            .writeU16(1) // tlv cnt
            .writeU16(0x536) // tag
            .writeTlv(Buffer.from([0x1, 0x0])) // zero
    */
    ByteArray temp;
    temp << uint32_t((0x525 << 16) & 8) << uint16_t(1) << uint16_t(0x536)
         << uint16_t(2) << uint32_t(0x1 << 16);
    return std::move(temp);
}
ByteArray PackTlv::t52d() const {
    /**
        const d = this.device
        const buf = pb.encode({
            1: d.bootloader,
            2: d.proc_version,
            3: d.version.codename,
            4: d.version.incremental,
            5: d.fingerprint,
            6: d.boot_id,
            7: d.android_id,
            8: d.baseband,
            9: d.version.incremental,
        })
        return new Writer().writeBytes(buf)
    */
    DevInfo devInfo;
    devInfo.set_bootloader(ByteArrayTo<std::string>(info.device.bootloader));
    devInfo.set_procversion(ByteArrayTo<std::string>(info.device.proc_version));
    devInfo.set_codename(
        ByteArrayTo<std::string>(info.device.version.codename));
    devInfo.set_incremental(
        ByteArrayTo<std::string>(info.device.version.incremental));
    devInfo.set_fingerprint(ByteArrayTo<std::string>(info.device.fingerprint));
    devInfo.set_bootid(ByteArrayTo<std::string>(info.device.boot_id));
    devInfo.set_androidid(ByteArrayTo<std::string>(info.device.display));
    devInfo.set_baseband(ByteArrayTo<std::string>(info.device.baseBand));
    devInfo.set_innerversion(
        ByteArrayTo<std::string>(info.device.version.incremental));

    ByteArray temp;
    temp << uint32_t(0x52d << 16) << devInfo.SerializeAsString();
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}

}; // namespace Flee
