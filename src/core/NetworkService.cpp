/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-02-07 13:28
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-03-31 17:07
 * @FilePath: \Flee\src\core\NetworkService.cpp
 * @Description:
 */

#include "NetworkService.h"
#include "ByteArray.h"
#include "NetworkException.h"
#include <boost/asio/read.hpp>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <spdlog/spdlog.h>
#include <sstream>
#include <string>
#include <thread>
#include <utility>

namespace Flee {

NetworkService::NetworkService(boost::asio::io_service& io_service)
    : io_service(io_service), socket(io_service) {}

bool NetworkService::connect(const std::string& host, const std::string& port) {
    boost::asio::ip::tcp::resolver::query query(host, port);
    boost::asio::ip::tcp::resolver        resolver{ io_service };
    boost::system::error_code             ec;

    iter = resolver.resolve(query, ec);
    if(ec) {
        // throw NetworkException(ec.message(), NetworkException::ResolveError);
        return false;
    } else {
        socket.connect(*iter, ec);
        if(ec) {
            spdlog::info("Cann't connect to {}:{}\n{}", host, port, ec.message());
            return false;
            // throw NetworkException(ec.message(), NetworkException::ConnectionError);
        } else {
            spdlog::info("Connect to {}:{}", host, port);
            return true;
        }
    }
}
bool NetworkService::connect(const std::string& host, uint_least16_t port) {
    boost::system::error_code      ec;
    boost::asio::ip::tcp::endpoint endpoint(
        boost::asio::ip::address_v4::from_string(host), port);
    socket.connect(endpoint, ec);
    if(ec) {
        spdlog::info("Cann't connect to {}:{}\n{}", host, port, ec.message());
        return false;
        // throw NetworkException(ec.message(), NetworkException::ConnectionError);
    } else {
        spdlog::info("Connect to {}:{}", host, port);
        return true;
    }
}

bool NetworkService::reconnect() {
    boost::system::error_code ec;
    socket.connect(*iter, ec);
    if(ec) {
        spdlog::info("Cann't reconnect to {}:{}\n{}", iter->service_name(),
                     iter->host_name(), ec.message());
        return false;
        // throw NetworkException(ec.message(), NetworkException::ConnectionError);
    } else {
        spdlog::info("Reconnect to {}:{}", iter->service_name(), iter->host_name());
        return true;
    }
}

size_t NetworkService::write(const ByteArray& buffer) {
    boost::system::error_code ec;
    std::size_t               write_size;
    if(socket.is_open()) {
        write_size =
            boost::asio::write(socket, boost::asio::buffer(buffer, buffer.size()), ec);
        if(ec) {
            throw NetworkException(ec.message(), NetworkException::WriteError);
        } else {
            spdlog::info("send data successfully: size={}", write_size);
            return write_size;
        }
    } else {
        throw NetworkException(std::string(__FUNCTION__) + " Network not connected",
                               NetworkException::WriteError);
    }
}

void NetworkService::async_write(const ByteArray&                 buffer,
                                 std::function<void(std::size_t)> func) {

    if(socket.is_open()) {
        socket.async_write_some(
            boost::asio::buffer(buffer),
            [&func](boost::system::error_code ec, std::size_t write_size) {
                if(ec) {
                    throw NetworkException(ec.message(), NetworkException::WriteError);
                } else {
                    spdlog::info("send data successfully: size={}", write_size);
                    func(write_size);
                }
            });
    } else {
        throw NetworkException(std::string(__FUNCTION__) + " Network not connected",
                               NetworkException::WriteError);
    }
}

void NetworkService::async_read(std::function<void(ByteArray&)> func) {
    socket.async_read_some(boost::asio::buffer(buffer),
                           std::bind(&NetworkService::onReadToPacket, this,
                                     std::placeholders::_1, std::placeholders::_2,
                                     func));
}

void NetworkService::onReadToPacket(boost::system::error_code ec, std::size_t read_size,
                                    std::function<void(ByteArray&)> func) {
    static uint16_t ec_size = 0;
    if(ec) {
        spdlog::info("Error in read data.  code: {}  message {}", ec.value(),
                     ec.message());
    } else {
        socket.async_read_some(boost::asio::buffer(buffer),
                               std::bind(&NetworkService::onReadToPacket, this,
                                         std::placeholders::_1, std::placeholders::_2,
                                         func));
        if(read_size > 0) {
            spdlog::info("Network recevice data: size = {}", read_size);

            std::move(buffer.begin(), buffer.begin() + read_size,
                      std::back_inserter(packet_buffer));
            // spdlog::info("packet buffer: {}", packet_buffer.toHex());
            // 分割数据包
            uint32_t length = 0;
            while((length = (packet_buffer.read<uint32_t>() - 4))
                  <= packet_buffer.size()) {
                auto _temp_ = packet_buffer.readByteArray(length);
                spdlog::info("Network recevice packet: size = {}", _temp_.size());
                func(_temp_);
                _temp_.clear();
            }
        } else {
            ec_size++;
            if(ec_size == 0) {
                spdlog::info("Network recevice data size: 0");
            }
        }
    }
}

void NetworkService::close() {
    boost::system::error_code ec;
    io_service.stop();
    socket.close(ec);
    if(ec) {
        throw NetworkException(ec.message(), NetworkException::CloseError);
    }
}

NetworkService::~NetworkService() {
    this->close();
}

} // namespace Flee