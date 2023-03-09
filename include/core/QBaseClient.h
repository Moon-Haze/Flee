/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42:18
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-03-04 21:25
 * @FilePath: \Flee\include\core\QBaseClient.h
 * @description:
 */
#ifndef FLEE_QBASECLIENT_H
#define FLEE_QBASECLIENT_H

#include "ByteArray.h"
#include "LogInhander.h"
#include "NetworkService.h"
#include "PacketListener.h"
#include "QQConfig.h"
#include "QQPackTlv.h"
#include <cstdint>
#include <spdlog/spdlog.h>

namespace Flee {

class QBaseClient {

    /* data */
    QQConfig  config;
    QQPackTlv packet;

    /* network */
    boost::asio::io_service io_service{};
    NetworkService          netService;

    /* listener */
    PacketListener& listener = packet.getPacketListener();
    /* logger */
    std::shared_ptr<spdlog::logger> logger;
    /* hander*/
    LogInHander loginHander{};

public:
    explicit QBaseClient(uint64_t uin);
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

    void parseQtcode(ByteArray& buffer);
};
};     // namespace Flee
#endif // FLEE_QBASECLIENT_H