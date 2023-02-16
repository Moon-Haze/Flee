/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42:18
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-16 11:08
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
    /**
     * @brief 使用本地保存的token登录
     *
     * @param data token
     * @return true 登录成功
     * @return false 登录失败
     */
    bool tokenLogin(const ByteArray& data);
    /**
     * @brief 使用密码登录
     *
     * @param data 密码的md5加密
     * @return true 登录成功
     * @return false 登录失败
     */
    bool passwordLogin(const ByteArray& data);
    /**
     * @brief 扫码后登录账号
     *
     * @return true 登录成功
     * @return false 登录失败
     */
    bool qrcodeLogin();
    /**
     * @brief 获取二维码
     *
     * @return true 获取成功
     * @return false 获取失败
     */
    bool fetchQrcode();

    /**
     * @brief 未完待定
     *
     */
    void queryQrcodeResult();
};
};     // namespace Flee
#endif // FLEE_QQCLIENT_H