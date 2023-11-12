/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-03-04 20:51
 * @FilePath: \Flee\include\packet\Tlv.h
 * @Description:
 */
#ifndef FLEE_TLV_H
#define FLEE_TLV_H

#include "AccountSecrets.h"
#include "ByteArray.h"
#include "QQProtocol.h"
#include "device.h"
#include <map>

namespace Flee {

class Tlv {
private:
    uint64_t  uin;
    ByteArray password;

public:
    AccountSecrets sig;
    APK            apk;
    Device         device;

public:
    explicit Tlv(uint64_t uin, const Platform& platform,
                 const std::string& device_file);

    explicit Tlv(const Tlv& other);

    uint64_t getUin() const;

    void setPassword(const ByteArray& value);

    void setPassword(const std::string& value);

    const ByteArray& getPassword() const;

    std::string genRandomPayloadByDevice() const;

    AccountSecrets& getSig();

    ByteArray t01() const;
    ByteArray t08() const;
    ByteArray t16() const;
    ByteArray t18() const;
    ByteArray t1B() const;
    ByteArray t1D() const;
    ByteArray t1F() const;
    ByteArray t33() const;
    ByteArray t35() const;
    ByteArray t100(uint8_t emp = 0) const;
    ByteArray t104() const;
    ByteArray t106() const;
    ByteArray t107() const;
    ByteArray t109() const;
    ByteArray t10a() const;
    ByteArray t116() const;
    ByteArray t124() const;
    ByteArray t128() const;
    ByteArray t141() const;
    ByteArray t142() const;
    ByteArray t143() const;
    ByteArray t144() const;
    ByteArray t145() const;
    ByteArray t147() const;
    ByteArray t154() const;
    ByteArray t16e() const;
    ByteArray t174() const;
    ByteArray t177() const;
    ByteArray t17a() const;
    ByteArray t17c(const ByteArray& code) const;
    ByteArray t187() const;
    ByteArray t188() const;
    ByteArray t191() const;
    ByteArray t193(const ByteArray& ticket) const;
    ByteArray t194() const;
    ByteArray t197() const;
    ByteArray t198() const;
    ByteArray t202() const;
    ByteArray t400() const;
    ByteArray t401() const;
    ByteArray t511() const;
    ByteArray t516() const;
    ByteArray t521() const;
    ByteArray t525() const;
    ByteArray t52d() const;
};
};     // namespace Flee
#endif // FLEE_TLV_H