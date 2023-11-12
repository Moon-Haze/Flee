/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42:18
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-03-31 16:35
 * @FilePath: \Flee\include\core\QBaseClient.h
 * @description:
 */
#ifndef FLEE_QBASECLIENT_H
#define FLEE_QBASECLIENT_H

#include "ByteArray.h"
#include "NetworkService.h"
#include "PacketListener.h"
#include "QQConfig.h"
#include "QQPackTlv.h"
#include <cstdint>
#include <spdlog/spdlog.h>
// handler
#include "LogInHandler.h"

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
    LogInHandler loginHandler{ packet };

    /* timer */
    boost::asio::deadline_timer timer1{ io_service, boost::posix_time::seconds(1) };

public:
    explicit QBaseClient(uint64_t uin);

    void login();

private:
    /**
     * @brief 登录账号 统一封装发送数据
     *
     * @param cmd
     * @param body
     */
    void FN_SEND_LOGIN(const std::string& cmd, const ByteArray& body);

    /**
     * @brief 使用本地保存的token登录
     *
     * @param data token
     */
    void tokenLogin(const ByteArray& data);
    /**
     * @brief 使用密码登录
     *
     * @param data 密码的md5加密
     */
    void passwordLogin(const ByteArray& data);
    /**
     * @brief 扫码后登录账号
     *
     */
    void qrcodeLogin(const QRCodeResult& result);
    /**
     * @brief 获取二维码
     *
     */
    void fetchQrcode();

    /**
     * @brief 获取二维码的扫码的情况，可以定时查询
     *
     */
    void queryQrcodeResult();
};
};     // namespace Flee
#endif // FLEE_QBASECLIENT_H