/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-10 16:01
 * @FilePath: \Flee\include\code\QQConfig.h
 * @Description:
 */
#ifndef FLEE_QQCONFIG_H
#define FLEE_QQCONFIG_H

#include "ByteArray.h"
#include "QQProtocol.h"
#include <cstdint>
#include <string>

namespace Flee {

class QQConfig {
private:
    /* data */
    std::string dir;
    std::string log_dir;
    std::string data_dir;
    std::string device_dir;

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
};

template <typename T = uint16_t>
class DataPacket {
    /* data */
    ByteArray data;
    T         offset;

public:
    DataPacket(const ByteArray& data, T offset = 0);

    DataPacket(const std::string& data, T offset = 0);

    template <typename Z>
    DataPacket(Z data, T offset = 0)
        : data(std::move(ByteArray::from<Z>(data))), offset(offset) {}

    T                getOffset() const;
    const ByteArray& getData() const;
};

template <typename T>
ByteArray& operator<<(ByteArray& array, const DataPacket<T>& packet);

#define DataPacketWithLength(data) DataPacket<uint32_t>(data, 4)

};     // namespace Flee
#endif // FLEE_QQCONFIG_H