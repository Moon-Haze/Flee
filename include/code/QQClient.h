/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42:18
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-14 16:52
 * @FilePath: \Flee\include\code\QQClient.h
 * @description:
 */
#ifndef FLEE_QQCLIENT_H
#define FLEE_QQCLIENT_H

#include "ByteArray.h"
#include "NetworkHandler.h"
#include "PacketListener.h"
#include "QQConfig.h"
#include "QQPackTlv.h"
#include <cstdint>
#include <spdlog/spdlog.h>

namespace Flee {

class QQClient {

    /* data */
    QQConfig  config;
    QQPackTlv packet;

    /* network */
    boost::asio::io_service io_service{};
    NetworkHandler          handler;

    /* listener */
    PacketListener& listener = packet.getPacketListener();
    /* logger */
    std::shared_ptr<spdlog::logger> logger;

public:
    explicit QQClient(uint64_t uin);
    void login();

private:
    // 登录的相关函数
    bool tokenLogin(const ByteArray& data);
    bool passwordLogin(const ByteArray& data);
    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool qrcodeLogin();
    /**
     * @brief
     *
     * @return true
     * @return false
     */
    bool fetchQrcode();
    /**
     * @brief 二维码登录的相关函数
     *
     */
    void queryQrcodeResult();
};
};     // namespace Flee
#endif // FLEE_QQCLIENT_H