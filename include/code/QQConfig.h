#ifndef FLEE_QQCONFIG_H
#define FLEE_QQCONFIG_H

#include "AccountSecrets.h"
#include "ByteArray.h"
#include "QQProtocol.h"
#include "constants.h"
#include "device.h"

#include <cstdint>
#include <string>

namespace Flee {

class QQConfig {
private:
    /* data */
    std::string dir;

public:
    Platform platform = Platform::Android;

public:
    explicit QQConfig(const std::string& dir = "./");

    QQConfig(const QQConfig& other);
    /**
     * @brief Get the Dir object
     *
     * @return std::string
     */
    std::string getDir() const;
    /**
     * @brief Set the Dir object
     *
     * @param dir
     */
    void setDir(const std::string& dir);

    ~QQConfig();
};

/**
 * @brief QQ账户的所有存储信息
 *
 */
class QQInfo {
    uint64_t  uin;
    ByteArray password;

public:
    QQConfig       config;
    AccountSecrets secrets;
    APK            apk;
    Device         device;

    explicit QQInfo(uint32_t uin, QQConfig config)
        : config(std::move(config)),
          secrets(uin),
          apk(APK::getApk(config.platform)),
          device(std::move(Device::getDevice(config.getDir()))) {}

    explicit QQInfo(const QQInfo& other)
        : config(other.config), secrets(other.secrets) {}

    uint64_t getUin() const { return uin; }

    void setPassword(const ByteArray& value) { password = value; }

    void setPassword(const std::string& value) { password = md5(value); }

    ByteArray getPassword() const { return password; }
};
};     // namespace Flee
#endif // FLEE_QQCONFIG_H