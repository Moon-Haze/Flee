#include "QQProtocol.h"
#include <map>
#include <utility>

namespace Flee {
APK::APK(std::string id, std::string name, std::string version, std::string ver,
         ByteArray sign, uint64_t buildTime, uint16_t appid, uint32_t subid,
         uint32_t bitmap, uint32_t sigmap, std::string sdkver, std::string display)
    : id(std::move(id)),
      name(std::move(name)),
      version(std::move(version)),
      ver(std::move(ver)),
      sign(std::move(sign)),
      buildTime(buildTime),
      appid(appid),
      subid(subid),
      bitmap(bitmap),
      sigmap(sigmap),
      sdkver(std::move(sdkver)),
      display(std::move(display)) {}

const APK& APK::getApk(const Platform& platform) {
    static std::map<Platform, APK> protocols{
        std::map<Platform, APK>::value_type{
            Android,
            APK{
                "com.tencent.mobileqq",
                "A8.8.80.7400",
                "8.8.80.7400",
                "8.8.80",
                { Byte(0xA6), Byte(0xB7), Byte(0x45), Byte(0xBF), Byte(0x24),
                  Byte(0xA2), Byte(0xC2), Byte(0x77), Byte(0x52), Byte(0x77),
                  Byte(0x16), Byte(0xF6), Byte(0xF3), Byte(0x6E), Byte(0xB6),
                  Byte(0x8D) },
                1640921786L,
                16,
                537113159,
                184024956,
                34869472L,
                "6.0.0.2494",
                "Android",
            } },
        std::map<Platform, APK>::value_type{
            Watch,
            APK{
                "com.tencent.qqlite",
                "A2.0.5",
                "2.0.5",
                "2.0.5",
                { Byte(0xA6), Byte(0xB7), Byte(0x45), Byte(0xBF), Byte(0x24),
                  Byte(0xA2), Byte(0xC2), Byte(0x77), Byte(0x52), Byte(0x77),
                  Byte(0x16), Byte(0xF6), Byte(0xF3), Byte(0x6E), Byte(0xB6),
                  Byte(0x8D) },
                1559564731L,
                16,
                537064446,
                16252796,
                34869472,
                "6.0.0.236",
                "Watch",
            } },
        std::map<Platform, APK>::value_type{
            aPad,
            APK{
                "com.tencent.minihd.qq",
                "A5.9.3.3468",
                "5.9.3.3468",
                "5.9.3",
                { Byte(0xAA), Byte(0x39), Byte(0x78), Byte(0xF4), Byte(0x1F),
                  Byte(0xD9), Byte(0x6F), Byte(0xF9), Byte(0x91), Byte(0x4A),
                  Byte(0x66), Byte(0x9E), Byte(0x18), Byte(0x64), Byte(0x74),
                  Byte(0xC7) },
                1637427966L,
                16,
                537067382,
                150470524,
                1970400,
                "6.0.0.2487",
                "aPad",
            } },
        std::map<Platform, APK>::value_type{
            iMac,
            APK{
                "com.tencent.minihd.qq",
                "A5.9.3.3468",
                "5.9.3.3468",
                "5.9.3",
                { Byte(0xAA), Byte(0x39), Byte(0x78), Byte(0xF4), Byte(0x1F),
                  Byte(0xD9), Byte(0x6F), Byte(0xF9), Byte(0x91), Byte(0x4A),
                  Byte(0x66), Byte(0x9E), Byte(0x18), Byte(0x64), Byte(0x74),
                  Byte(0xC7) },
                1637427966L,
                16,
                537128930,
                150470524,
                1970400,
                "6.0.0.2487",
                "aPad",
            } },
        std::map<Platform, APK>::value_type{
            iPad,
            APK{
                "com.tencent.minihd.qq",
                "A5.9.3.3468",
                "5.9.3.3468",
                "5.9.3",
                { Byte(0xAA), Byte(0x39), Byte(0x78), Byte(0xF4), Byte(0x1F),
                  Byte(0xD9), Byte(0x6F), Byte(0xF9), Byte(0x91), Byte(0x4A),
                  Byte(0x66), Byte(0x9E), Byte(0x18), Byte(0x64), Byte(0x74),
                  Byte(0xC7) },
                1637427966L,
                16,
                537118796,
                150470524,
                1970400,
                "6.0.0.2487",
                "aPad",
            } },
    };
    return protocols[platform];
}

} // namespace Flee