/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-14 19:06
 * @FilePath: \Flee\src\code\QQConfig.cpp
 * @Description:
 */

#include "QQConfig.h"
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>

namespace Flee {

QQConfig::QQConfig(uint64_t uin, const std::string& dir)
    : dir(dir),
      log_dir((std::stringstream() << dir << "logs/" << uin << "/log-" << uin << ".log")
                  .str()),
      data_dir((std::stringstream() << dir << "data/" << uin << '/').str()),
      device_dir(
          (std::stringstream() << data_dir << "device-" << uin << ".json").str()),
      token_dir((std::stringstream() << data_dir << "token").str()),
      qrcode_dir((std::stringstream() << data_dir << "qrcode.png").str()) {
    try {
        // if(!boost::filesystem::exists(log_dir)) {
        // boost::filesystem::create_directories(log_dir);
        // spdlog::info("creating directory: {}", log_dir);
        // }
        if(!boost::filesystem::exists(data_dir)) {
            boost::filesystem::create_directories(data_dir);
            spdlog::info("creating directory: {}", data_dir);
        }
    } catch(const boost::filesystem::filesystem_error& e) {
        spdlog::info("Error in creating directory: {}\n{}", data_dir, e.what());
    }
}

QQConfig::QQConfig(const QQConfig& other) : dir(other.dir), platform(other.platform) {}

const std::string& QQConfig::getDir() const {
    return dir;
}

void QQConfig::setDir(const std::string& dir) {
    this->dir = dir;
}

const std::string& QQConfig::getLogDir() const {
    return log_dir;
}

const std::string& QQConfig::getDataDir() const {
    return data_dir;
}
const std::string& QQConfig::getDeviceDir() const {
    return device_dir;
}
const std::string& QQConfig::getTokenDir() const {
    return token_dir;
}
const std::string& QQConfig::getQRCodeDir() const {
    return qrcode_dir;
}
}; // namespace Flee