/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-03-04 19:53
 * @FilePath: \Flee\include\core\QQConfig.h
 * @Description:
 */

#ifndef FLEE_QQCONFIG_H
#define FLEE_QQCONFIG_H

#include "QQProtocol.h"
#include <string>

namespace Flee {

class QQConfig {
private:
    /* data */
    std::string dir;
    std::string log_dir;
    std::string data_dir;
    std::string device_dir;
    std::string token_dir;
    std::string qrcode_dir;

public:
    Platform platform = Platform::Android;

public:
    explicit QQConfig(uint64_t uin, const std::string& dir = "./");

    QQConfig(const QQConfig& other);
    /**
     * @brief Get the Dir object
     *
     * @return std::string
     */
    const std::string& getDir() const;
    /**
     * @brief Set the Dir object
     *
     * @param dir
     */
    void setDir(const std::string& dir);

    const std::string& getLogDir() const;

    const std::string& getDataDir() const;

    const std::string& getDeviceDir() const;

    const std::string& getTokenDir() const;

    const std::string& getQRCodeDir() const;
};

};     // namespace Flee
#endif // FLEE_QQCONFIG_H