/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-10 16:07
 * @FilePath: \Flee\src\code\QQConfig.cpp
 * @Description:
 */
/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42:18
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-10 15:33
 * @FilePath: \Flee\src\code\QQConfig.cpp
 * @Description:
 */
#include "QQConfig.h"
#include <string>

namespace Flee {

QQConfig::QQConfig(uint64_t uin, const std::string& dir)
    : dir(dir),
      log_dir((std::stringstream() << dir << "logs/" << uin << "/").str()),
      data_dir((std::stringstream() << dir << "data/" << uin << "/").str()),
      device_dir(
          (std::stringstream() << data_dir << "device-" << uin << ".json").str()) {}

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

template class DataPacket<uint16_t>;
template class DataPacket<uint32_t>;

template <typename T>
DataPacket<T>::DataPacket(const ByteArray& data, T offset)
    : data(data), offset(offset) {
    static_assert(std::is_arithmetic<T>::value | std::is_same<T, char>::value
                      | std::is_same<T, std::byte>::value,
                  "T must be a numeric,char,byte type");
}

template <typename T>
DataPacket<T>::DataPacket(const std::string& data, T offset)
    : data(std::move(ByteArray::from(data))), offset(offset) {}

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

template ByteArray& operator<< <uint32_t>(ByteArray&                  array,
                                          const DataPacket<uint32_t>& packet);

}; // namespace Flee