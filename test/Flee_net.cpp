/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-02-07 17:23
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-09 20:26
 * @FilePath: \Flee\test\Flee_net.cpp
 * @Description:
 */
#include "ByteArray.h"
#include "NetworkHandler.h"
#include <cstdlib>
#include <iostream>
#include <string>

int main(int argc, char** argv) {
    //
    using namespace Flee;
    try {
        NetworkHandler handler;
        handler.connect("www.baidu.com", "80");
        std::string str = std::string("GET / HTTP 1.1\r\nHost: www.baidu.com\r\n\r\n");
        ByteArray   buffer;
        buffer << str;
        handler.write(buffer);
        /**
            boost::asio::io_service     io_service;
            boost::asio::deadline_timer timer(io_service,
           boost::posix_time::seconds(5)); timer.async_wait([](const
           boost::system::error_code& ec) { std::cout << ec.message() << std::endl;
                std::cout << "5 s." << std::endl;
            });
            io_service.run();
        */
        handler.readToPacket([](const ByteArray& data) {
            std::cout << "recevice=>" << data.to<std::string>() << std::endl;
        });

    } catch(const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}