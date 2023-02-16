/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-02-07 13:28
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-16 13:16
 * @FilePath: \Flee\include\code\NetworkHandler.h
 * @Description: 封装 ASIO 的网络接口
 */
#ifndef FLEE_NETWORKHANDER_H
#define FLEE_NETWORKHANDER_H

#include "ByteArray.h"
#include <array>
#include <boost/asio.hpp>
#include <cstddef>
#include <functional>
#include <map>
#include <mutex>
#include <thread>

namespace Flee {

class NetworkHandler {

    boost::asio::ip::tcp::socket socket;
    boost::asio::io_service&     io_service;
    /* 数据接收解析缓存 */
    std::array<std::byte, 512> buffer;
    ByteArray                  packet_buffer;
    /* network thread */
    // std::thread* network_thread = nullptr;
    /* IP地址 */
    boost::asio::ip::tcp::resolver::iterator iter{};

public:
    explicit NetworkHandler(boost::asio::io_service& io_service);

    ~NetworkHandler();

    bool connect(const std::string& host, const std::string& port);

    bool connect(const std::string& host, uint_least16_t port);

    bool reconnect();

    void write(const ByteArray& buffer, std::function<void(std::size_t)> func);

    void async_write(const ByteArray& buffer, std::function<void(std::size_t)> func);

    void async_read(std::function<void(ByteArray&)> func);

    void close();

    void onReadToPacket(boost::system::error_code ec, std::size_t read_size,
                        std::function<void(ByteArray&)> func);
};

};     // namespace Flee
#endif // FLEE_NETWORKHANDER_H