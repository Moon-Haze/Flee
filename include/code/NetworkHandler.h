/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-02-07 13:28
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-09 20:48
 * @FilePath: \Flee\include\code\NetworkHandler.h
 * @Description:
 */
#ifndef FLEE_NETWORKHANDER_H
#define FLEE_NETWORKHANDER_H

#include "ByteArray.h"
#include <boost/asio.hpp>
#include <functional>
#include <map>
#include <thread>

namespace Flee {

class NetworkHandler {

    boost::asio::io_service      io_service{};
    boost::asio::ip::tcp::socket socket{ io_service };
    ByteArray                    buffer;
    std::thread                 * network_thread=nullptr;
    // std::mutex m_mutex;

public:
    explicit NetworkHandler();

    ~NetworkHandler();

    void connect(const std::string& host, const std::string& port);

    void write(const ByteArray& buffer);

    void read(std::function<void(const ByteArray&)> func);

    void readToPacket(std::function<void(const ByteArray&)> func);

    void close();

private:
    void readDatawithThread(std::function<void(const ByteArray&)> func);
};

}; // namespace Flee

#endif // FLEE_NETWORKHANDER_H