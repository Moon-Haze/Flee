#ifndef FLEE_QQPROTOCOL_H
#define FLEE_QQPROTOCOL_H

#include "ByteArray.h"
#include <string>

namespace Flee {

/** 支持的登录设备平台 */
enum Platform {
    Android = 1,
    aPad    = 2,
    Watch   = 3,
    iMac    = 4,
    iPad    = 5,
};

class APK {
public:
    std::string id;
    std::string name;
    std::string version;
    std::string ver;
    ByteArray   sign;
    uint64_t    buildTime;
    uint16_t    appid;
    uint32_t    subid;
    uint32_t    bitmap;
    uint32_t    sigmap;
    std::string sdkver;
    std::string display;

    explicit APK() = default;
    explicit APK(std::string id, std::string name, std::string version, std::string ver,
                 ByteArray sign, uint64_t buildTime, uint16_t appid, uint32_t subid,
                 uint32_t bitmap, uint32_t sigmap, std::string sdkver, std::string display);

    static const APK& getApk(const Platform& protocol);
};

} // namespace Flee
#endif // FLEE_QQPROTOCOL_H