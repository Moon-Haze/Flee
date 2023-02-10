/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-02-07 13:28
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-10 14:15
 * @FilePath: \Flee\src\code\NetworkHandler.cpp
 * @Description:
 */

#include "NetworkHandler.h"
#include "ByteArray.h"
#include "NetworkException.h"
#include <boost/asio/read.hpp>
#include <cstddef>
#include <cstdint>
#include <minwindef.h>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>
#include <thread>
#include <utility>

namespace Flee {

NetworkHandler::NetworkHandler() {}

void NetworkHandler::connect(const std::string& host, const std::string& port) {

    boost::asio::ip::tcp::resolver::query query(host, port);

    boost::asio::ip::tcp::resolver resolver{ io_service };
    boost::system::error_code      ec;

    boost::asio::ip::tcp::resolver::iterator iter = resolver.resolve(query, ec);
    if(ec) {
        throw NetworkException(ec.message(), NetworkException::ResolveError);
    } else {
        socket.connect(*iter, ec);
        if(ec) {
            spdlog::error("Cann't connect to {}:{}\n{}", host, port, ec.message());
            throw NetworkException(ec.message(), NetworkException::ConnectionError);
        } else {
            spdlog::info("Connect to {}:{}", host, port);
        }
    }
}

void NetworkHandler::write(const ByteArray& buffer) {
    if(socket.is_open()) {
        boost::system::error_code ec;
        socket.write_some(boost::asio::buffer(buffer, buffer.size()), ec);
        if(ec) {
            throw NetworkException(ec.message(), NetworkException::WriteError);
        } else {
            spdlog::info("send data: size={}", buffer.size());
        }
    } else {
        throw NetworkException(std::string(__FUNCTION__) + " Network not connected",
                               NetworkException::WriteError);
    }
}

void NetworkHandler::read(std::function<void(const ByteArray&)> func) {
    if(socket.is_open()) {
        spdlog::info("socket is opening.");
        while(socket.available() <= 0) {
        }
        spdlog::info("socket available: {}", socket.available());
        std::size_t               data_size;
        boost::system::error_code ec;
        while((data_size = socket.available()) > 0) {
            ByteArray buffer;
            buffer.resize(data_size);
            spdlog::info("data_size: {}", data_size);
            data_size = socket.read_some(boost::asio::buffer(buffer), ec);
            spdlog::info("data_size: {}", data_size);
        }
    }
}
void NetworkHandler::readToPacket(std::function<void(const ByteArray&)> func) {
    // network_thread
    network_thread = new std::thread(&NetworkHandler::readDatawithThread, this, func);
    // network_thread.r
    network_thread->join();
}

void NetworkHandler::readDatawithThread(std::function<void(const ByteArray&)> func) {
    std::array<std::byte, 512> temp;
    boost::system::error_code  ec;
    std::size_t                available_size = 0, read_size = 0;
    uint32_t                   length = 0;
    while(socket.is_open()) {
        if((available_size = socket.available()) > 0) {
            spdlog::info("socket available: {}", available_size);
            read_size = socket.read_some(boost::asio::buffer(temp), ec);
            if(ec) {
                spdlog::info("ec.message={}", ec.message());
            } else if(read_size > 0) {
                spdlog::info("Network recevice data (size={})", read_size);
                std::move(temp.begin(), temp.end(), std::back_inserter(buffer));
                spdlog::info("Now recevice data in buffer (size={}) \n", buffer.size(),
                             buffer.toHex());
                // 分割数据包
                while((length = buffer.to<uint32_t>()) <= buffer.size()) {
                    auto _temp_ = buffer.readByteArray(0, length);
                    spdlog::info("Network recevice data: \n {}", _temp_.toHex());
                    func(_temp_);
                    _temp_.clear();
                }
            } else {
            }
        }
    }
}

void NetworkHandler::close() {
    boost::system::error_code ec;
    socket.close(ec);
    if(ec) {
        throw NetworkException(ec.message(), NetworkException::CloseError);
    }
}

NetworkHandler::~NetworkHandler() {
    this->close();
    if(network_thread->joinable()) {
        network_thread->join();
    }
}
} // namespace Flee