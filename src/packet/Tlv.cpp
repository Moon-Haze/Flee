#include "Tlv.h"

#include "BuildPackage.h"
#include "ByteArray.h"
#include "DevInfo.pb.h"
#include "QQProtocol.h"
#include "constants.h"
#include "tea.h"
#include <algorithm>
#include <boost/json/parse.hpp>
#include <boost/json/serialize.hpp>
#include <boost/json/value.hpp>
#include <cstdint>
#include <string>
#include <utility>
namespace Flee {

Tlv::Tlv(uint64_t uin, const Platform& platform, const std::string& device_file)
    : sig(uin),
      apk(APK::getApk(platform)),
      device(std::move(Device::getDevice(uin, device_file))) {}

Tlv::Tlv(const Tlv& other) : sig(other.sig), apk(other.apk), device(other.device) {}

uint64_t Tlv::getUin() const {
    return uin;
}

void Tlv::setPassword(const ByteArray& value) {
    password = value;
}

void Tlv::setPassword(const std::string& value) {
    password = md5(value);
}

const ByteArray& Tlv::getPassword() const {
    return password;
}

AccountSecrets& Tlv::getSig() {
    return sig;
}

std::string Tlv::genRandomPayloadByDevice() const {
    boost::json::value reserved = {
        { "harmony", "0" },
        { "clone", "0" },
        { "containe", "" },
        { "oz", "UhYmelwouA+V2nPWbOvLTgN2/m8jwGB+yUB5v9tysQg=" },
        { "oo", "Xecjt+9S1+f8Pz2VLSxgpw==" },
        { "kelong", "0" },
        { "uptimes", Flee::getFormatDateTime("%Y-%m-%d %H:%M:%S") },
        { "multiUser", "0" },
        { "bod", this->device.board.toString() },
        { "brd", this->device.brand.toString() },
        { "dv", this->device.device.toString() },
        { "firstLevel", "" },
        { "manufact", this->device.brand.toString() },
        { "name", this->device.model.toString() },
        { "host", "se.infra" },
        { "kernel", this->device.fingerprint.toString() }
    };

    std::string       timeMonth = getFormatDateTime("%Y-%m-") + "01";
    uint64_t          rand1     = getRandomNumber(0, 899999) + 100000u;
    uint64_t          rand2     = getRandomNumber(0, 899999999) + 100000000u;
    std::stringstream beaconId;
    for(int i = 1; i <= 40; i++) {
        switch(i) {
            case 1:
            case 2:
            case 13:
            case 14:
            case 17:
            case 18:
            case 21:
            case 22:
            case 25:
            case 26:
            case 29:
            case 30:
            case 33:
            case 34:
            case 37:
            case 38:
                beaconId << 'k' << i << ':' << timeMonth << rand1 << '.' << rand2;
                break;
            case 3:
                beaconId << "k3:0000000000000000";

            default:
                beaconId << 'k' << i << ':' << getRandomNumber(0, 10000);
        }
        beaconId << ";";
    }
    return boost::json::serialize(boost::json::value{
        { "androidId", this->device.android_id.toString() },
        { "platformId", 1 },
        { "appKey", this->apk.app_key },
        { "appVersion", this->apk.version },
        { "beaconIdSrc", beaconId.str() },
        { "brand", this->device.brand.toString() },
        { "channelId", "2017" },
        { "cid", "" },
        { "imei", this->device.imei },
        { "imsi", "" },
        { "mac", "" },
        { "model", this->device.model.toString() },
        { "networkType", "unknown" },
        { "oaid", "" },
        { "osVersion",
          (std::stringstream() << "Android " << this->device.version.release.toString()
                               << ",level " << this->device.version.sdk)
              .str() },
        { "qimei", "" },
        { "qimei36", "" },
        { "sdkVersion", "1.2.13.6" },
        { "audit", "" },
        { "userId", "{}" },
        { "packageId", this->apk.id },
        { "deviceType", this->apk.display == "aPad" ? "Pad" : "Phone" },
        { "sdkName", "" },
        { "reserved", boost::json::serialize(reserved) } });
}
ByteArray Tlv::t01() const {
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
    temp << uint32_t(0x01 << 16) << uint16_t(1) << getRandomInt32_t()
         << uint32_t(this->uin) << int32_t(currentTimeMillis() & 0xffffffff)
         << uint32_t(0) << uint16_t(0);
    int16_t size = temp.size() - 4;
    temp[2]      = Byte((size >> 8) & 0xff);
    temp[3]      = Byte(size & 0xff);
    return std::move(temp);
}
ByteArray Tlv::t08() const {
    /**
        return new Writer()
            .writeU16(0)
            .writeU32(2052)
            .writeU16(0)
    */
    ByteArray temp;
    temp << uint32_t(0x08 << 16) << uint16_t(0) << uint32_t(2052) << uint16_t(0);
    int16_t size = temp.size() - 4;
    temp[2]      = Byte((size >> 8) & 0xff);
    temp[3]      = Byte(size & 0xff);
    return std::move(temp);
}

ByteArray Tlv::t16() const {
    /**
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
         << uint32_t(apk.subid) << this->device.guid << BuildPackage(apk.id)
         << BuildPackage(apk.ver) << BuildPackage(apk.sign);
    int16_t size = temp.size() - 4;
    temp[2]      = Byte((size >> 8) & 0xff);
    temp[3]      = Byte(size & 0xff);
    return std::move(temp);
}
ByteArray Tlv::t18() const {
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
    temp << uint32_t(0x18 << 16) << uint16_t(1) << uint32_t(1536)
         << uint32_t(this->apk.appid) << uint32_t(0) << uint32_t(this->uin)
         << uint32_t(0);
    int16_t size = temp.size() - 4;
    temp[2]      = Byte((size >> 8) & 0xff);
    temp[3]      = Byte(size & 0xff);
    return std::move(temp);
}

ByteArray Tlv::t1B() const {
    /**
        return new writer_1.default()
            .writeU32(0)
            .writeU32(0)
            .writeU32(3)
            .writeU32(4)
            .writeU32(72)
            .writeU32(2)
            .writeU32(2)
            .writeU16(0);
    */
    ByteArray temp;
    temp << uint32_t(0x1B << 16) << uint64_t(0) << uint32_t(3) << uint32_t(4)
         << uint32_t(72) << uint32_t(2) << uint32_t(2) << uint16_t(0);
    int16_t size = temp.size() - 4;
    temp[2]      = Byte((size >> 8) & 0xff);
    temp[3]      = Byte(size & 0xff);
    return std::move(temp);
}

ByteArray Tlv::t1D() const {
    /**
        return new Writer()
            .writeU8(1)
            .writeU32(184024956)
            .writeU32(0)
            .writeU8(0)
            .writeU32(0)
    */
    ByteArray temp;
    temp << uint32_t(0x1D << 16) << uint8_t(1) << uint32_t(184024956) << uint32_t(0)
         << uint8_t(0) << uint32_t(0);
    int16_t size = temp.size() - 4;
    temp[2]      = Byte((size >> 8) & 0xff);
    temp[3]      = Byte(size & 0xff);
    return std::move(temp);
}
ByteArray Tlv::t1F() const {
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
    temp << uint32_t(0x1F << 16) << uint8_t(0) << BuildPackage("android")
         << BuildPackage("7.1.2") << uint16_t(2) << BuildPackage("China Mobile GSM")
         << uint16_t(0) /* BuildPackage(ByteArray_0)*/ << BuildPackage("wifi");
    int16_t size = temp.size() - 4;
    temp[2]      = Byte((size >> 8) & 0xff);
    temp[3]      = Byte(size & 0xff);
    return std::move(temp);
}
ByteArray Tlv::t33() const {
    /**
        return new Writer().writeBytes(this.device.guid)
    */
    ByteArray temp;
    temp << uint32_t((0x33 << 16) | this->device.guid.size()) << this->device.guid;
    return std::move(temp);
}
ByteArray Tlv::t35() const {
    /**
    return new Writer().writeU32(8)
    */
    ByteArray temp;
    temp << uint32_t((0x35 << 16) | 4) << uint32_t(8);
    return std::move(temp);
}
ByteArray Tlv::t100(uint8_t emp) const {
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
         << uint32_t(this->apk.appid) << uint16_t(emp ? 2 : this->apk.subid)
         << uint32_t(0) << this->apk.main_sig_map;
    int16_t size = temp.size() - 4;
    temp[2]      = Byte((size >> 8) & 0xff);
    temp[3]      = Byte(size & 0xff);
    return std::move(temp);
}
ByteArray Tlv::t104() const {
    /**
        return new Writer().writeBytes(this.sig.t104)
    */
    ByteArray temp;
    temp << uint32_t((0x35 << 16) | this->sig.t104.size()) << this->sig.t104;
    return std::move(temp);
}
ByteArray Tlv::t106() const {
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
    */
    ByteArray temp, _temp_;
    temp << uint16_t(4) << getRandomByteArray(4) << uint32_t(7) << this->apk.appid
         << this->uin << int32_t(currentTimeMillis() & 0xffffffff) << ByteArray(4)
         << uint8_t(1) << this->getPassword() << this->sig.tgtgt << uint32_t(0)
         << uint8_t(1) << this->device.guid << this->apk.subid << uint32_t(1)
         << BuildPackage(std::to_string(this->uin)) << uint16_t(0);
    /**
        const buf = Buffer.alloc(4)
        buf.writeUInt32BE(this.uin)
        const key = md5(Buffer.concat([
            md5pass, Buffer.alloc(4), buf
        ]))
        return new Writer().writeBytes(tea.encrypt(body, key))
    */
    ByteArray key = this->getPassword();
    key << uint32_t(0) << this->uin;
    _temp_ = Tea::encrypt(key, temp);
    temp.clear();
    temp << uint32_t((0x106 << 16) | _temp_.size()) << _temp_;
    return std::move(temp);
}
ByteArray Tlv::t107() const {
    /**
        return new Writer()
            .writeU16(0)    // pic type
            .writeU8(0)     // captcha type
            .writeU16(0)    // pic size
            .writeU8(1)     // ret type
    */
    ByteArray temp;
    temp << uint32_t((0x107 << 16) | 6)
         << uint16_t(0)
         // << uint8_t(0) << uint16_t(0)
         << uint32_t(1);
    return std::move(temp);
}
ByteArray Tlv::t109() const {
    /**
        return new Writer().writeBytes(md5(this.device.imei))
    */
    ByteArray temp;
    temp << uint32_t(0x109 << 16) << md5(this->device.imei);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray Tlv::t10a() const {
    /**
        return new Writer().writeBytes(this.sig.tgt)
    */
    ByteArray temp;
    temp << uint32_t((0x10a << 16) | this->sig.tgt.size()) << this->sig.tgt;
    return std::move(temp);
}
ByteArray Tlv::t116() const {
    /**
        return new Writer()
            .writeU8(0)
            .writeU32(this.apk.bitmap)
            .writeU32(0x10400) // sub sigmap
            .writeU8(1) // size of app id list
            .writeU32(1600000226) // app id list[0]
    */
    ByteArray temp;
    temp << uint32_t(0x116 << 16) << uint8_t(0) << this->apk.bitmap << uint32_t(0x10400)
         << uint8_t(1) << uint32_t(1600000226);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray Tlv::t124() const {
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
    temp << uint32_t(0x124 << 16) << BuildPackage(this->device.osType)
         << BuildPackage(this->device.version.release) << uint16_t(2)
         << BuildPackage(this->device.simInfo) << uint16_t(0)
         << BuildPackage(this->device.apn);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray Tlv::t128() const {
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
         << uint8_t(0) << uint32_t(16777216) << BuildPackage(this->device.model)
         << BuildPackage(this->device.guid) << BuildPackage(this->device.brand);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray Tlv::t141() const {
    /**
        return new Writer()
            .writeU16(1) // ver
            .writeTlv(this.device.sim)
            .writeU16(2) // network type
            .writeTlv(this.device.apn)
    */
    ByteArray temp;
    temp << uint32_t(0x141 << 16) << uint16_t(1) << BuildPackage(this->device.simInfo)
         << uint16_t(2) << BuildPackage(this->device.apn);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray Tlv::t142() const {
    /**
        return new Writer()
            .writeU16(0)
            .writeTlv(this.apk.id.slice(0, 32))
    */
    ByteArray temp;
    temp << uint32_t((0x142 << 16) | (this->apk.id.size() + 2))
         << BuildPackage(this->apk.id);
    return std::move(temp);
}
ByteArray Tlv::t143() const {
    /**
        return new Writer().writeBytes(this.sig.d2)
    */
    ByteArray temp;
    temp << uint32_t((0x143 << 16) | this->sig.d2.size()) << this->sig.d2;
    return std::move(temp);
}
ByteArray Tlv::t144() const {
    /**
        const body = new Writer()
            .writeU16(5) // tlv cnt
            .writeBytes(Tlv.call(this, 0x109))
            .writeBytes(Tlv.call(this, 0x52d))
            .writeBytes(Tlv.call(this, 0x124))
            .writeBytes(Tlv.call(this, 0x128))
            .writeBytes(Tlv.call(this, 0x16e))
        return new Writer().writeBytes(tea.encrypt(body.read(), this.sig.tgtgt))
    */
    ByteArray temp;
    temp << uint16_t(0) << t109() << t52d() << t124() << t128() << t16e();

    temp =
        ByteArray::from(uint32_t((0x142 << 16))) + Tea::encrypt(this->sig.tgtgt, temp);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray Tlv::t145() const {
    /**
        return new Writer().writeBytes(this.device.guid)
    */
    ByteArray temp;
    temp << uint32_t((0x145 << 16) | this->device.guid.size()) << this->device.guid;
    return std::move(temp);
}
ByteArray Tlv::t147() const {
    /**
        return new Writer()
            .writeU32(this.apk.appid)
            .writeTlv(this.apk.ver.slice(0, 5))
            .writeTlv(this.apk.sign)
    */
    ByteArray temp;
    temp << uint32_t((0x147 << 16)) << uint32_t(this->apk.appid)
         << BuildPackage(this->apk.ver) << BuildPackage(this->apk.sign);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray Tlv::t154() const {
    /**
        return new Writer().writeU32(this.sig.seq + 1)
    */
    ByteArray temp;
    temp << uint32_t((0x154 << 16) | 4) << uint32_t(this->sig.seq + 1);
    return std::move(temp);
}
ByteArray Tlv::t16e() const {
    /**
        return new Writer().writeBytes(this.device.model)
    */
    ByteArray temp;
    temp << uint32_t((0x16e << 16) | this->device.model.size()) << this->device.model;
    return std::move(temp);
}
ByteArray Tlv::t174() const {
    /**
        return new Writer().writeBytes(this.sig.t174)
    */
    ByteArray temp;
    temp << uint32_t((0x174 << 16) | this->sig.t174.size()) << this->sig.t174;
    return std::move(temp);
}
ByteArray Tlv::t177() const {
    /**
        return new Writer()
            .writeU8(0x01)
            .writeU32(this.apk.buildtime)
            .writeTlv(this.apk.sdkver)
    */
    ByteArray temp;
    temp << uint32_t(0x177 << 16) << uint8_t(0x01) << this->apk.buildTime
         << BuildPackage(this->apk.sdkver);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray Tlv::t17a() const {
    /**
        return new Writer().writeU32(9)
    */
    ByteArray temp;
    temp << uint32_t((0x17a << 16) | 4) << uint32_t(9);
    return std::move(temp);
}
ByteArray Tlv::t17c(const ByteArray& code) const {
    /**
        return new Writer().writeTlv(code)
    */
    ByteArray temp;
    temp << uint32_t((0x17c << 16) | code.size() + 2) << BuildPackage(code);
    return {};
}
ByteArray Tlv::t187() const {
    /**
        return new Writer().writeBytes(md5(this.device.mac_address))
    */
    ByteArray temp;
    temp << uint32_t(0x187 << 16) << md5(this->device.mac_address);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray Tlv::t188() const {
    /**
        return new Writer().writeBytes(md5(this.device.android_id))
    */
    ByteArray temp;
    temp << uint32_t(0x188 << 16) << md5(this->device.android_id);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray Tlv::t191() const {
    /**
        return new Writer().writeU8(0x82)
    */
    ByteArray temp;
    temp << uint32_t((0x191 << 16) | 1) << uint8_t(0x82);
    return std::move(temp);
}
ByteArray Tlv::t193(const ByteArray& ticket) const {
    /**
        return new Writer().writeBytes(ticket)
    */
    ByteArray temp;
    temp << uint32_t((0x193 << 16) | ticket.size()) << ticket;
    return std::move(temp);
}
ByteArray Tlv::t194() const {
    /**
        return new Writer().writeBytes(this.)
    */
    ByteArray temp;
    temp << uint32_t((0x194 << 16) | this->device.imei.size()) << this->device.imei;
    return std::move(temp);
}
ByteArray Tlv::t197() const {
    /**
        return new Writer().writeTlv(Buffer.alloc(1))
    */
    ByteArray temp;
    temp << uint32_t((0x197 << 16) | 3) << uint16_t(1) << uint8_t(0);
    return std::move(temp);
}
ByteArray Tlv::t198() const {
    /**
        return new Writer().writeTlv(Buffer.alloc(1))
    */
    ByteArray temp;
    temp << uint32_t((0x198 << 16) | 3) << uint16_t(1) << uint8_t(0);
    return std::move(temp);
}
ByteArray Tlv::t202() const {
    /**
        return new Writer()
            .writeTlv(this.device.wifi_bssid.slice(0, 16))
            .writeTlv(this.device.wifi_ssid.slice(0, 32))
    */
    ByteArray temp;
    temp << uint32_t(0x202 << 16) << BuildPackage(this->device.wifi_bssid)
         << BuildPackage(this->device.wifi_ssid);
    return std::move(temp);
}
ByteArray Tlv::t400() const {
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
    temp << uint32_t(0x400 << 16) << uint16_t(1) << this->uin << this->device.guid
         << getRandomByteArray(16) << int32_t(1) << int32_t(16)
         << int32_t(currentTimeMillis() & 0xffffffff);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray Tlv::t401() const {
    /**
        return new Writer().writeBytes(crypto.randomBytes(16))
    */
    ByteArray temp;
    temp << uint32_t(0x401 << 16) << uint16_t(1) << this->uin << this->device.guid
         << getRandomByteArray(16);
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray Tlv::t511() const {
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
        temp << uint8_t(0x01) << BuildPackage(item);
    }
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}
ByteArray Tlv::t516() const {
    /**
        return new Writer().writeU32(0)
    */
    ByteArray temp;
    temp << uint32_t((0x516 << 16) | 4) << uint32_t(0);
    return std::move(temp);
}
ByteArray Tlv::t521() const {
    /**
        return new Writer()
            .writeU32(0) // product type
            .writeU16(0) // const
    */
    ByteArray temp;
    temp << uint32_t((0x521 << 16) | 6) << uint32_t(0) << uint16_t(0);
    return std::move(temp);
}
ByteArray Tlv::t525() const {
    /**
        return new Writer()
            .writeU16(1) // tlv cnt
            .writeU16(0x536) // tag
            .writeTlv(Buffer.from([0x1, 0x0])) // zero
    */
    ByteArray temp;
    temp << uint32_t((0x525 << 16) | 8) << uint16_t(1) << uint16_t(0x536) << uint16_t(2)
         << uint32_t(0x1 << 16);
    return std::move(temp);
}
ByteArray Tlv::t52d() const {
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
    devInfo.set_bootloader(this->device.bootloader.toString());
    devInfo.set_procversion(this->device.proc_version.toString());
    devInfo.set_codename(this->device.version.codename.toString());
    devInfo.set_incremental(this->device.version.incremental.toString());
    devInfo.set_fingerprint(this->device.fingerprint.toString());
    devInfo.set_bootid(this->device.boot_id.toString());
    devInfo.set_androidid(this->device.android_id.toString());
    devInfo.set_baseband(this->device.baseBand.toString());
    devInfo.set_innerversion(this->device.version.incremental.toString());

    ByteArray temp;
    temp << uint32_t(0x52d << 16) << devInfo.SerializeAsString();
    uint16_t size = temp.size() - 4;
    temp[2]       = Byte((size & 0xff) >> 4);
    temp[3]       = Byte((size >> 4) & 0xff);
    return std::move(temp);
}

}; // namespace Flee
