/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42:18
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-07 15:59
 * @FilePath: \Flee\include\code\QQClient.h
 * @description:
 */
#ifndef FLEE_CLIENT_H
#define FLEE_CLIENT_H

#include "ByteArray.h"
#include "QQConfig.h"
#include "QQPackTlv.h"
#include "ecdh.h"
#include <cstdint>
#include <spdlog/spdlog.h>

namespace Flee {

class QQClient {
private:
    /* data */
    QQConfig  config;
    QQPackTlv packet;

    ECDH ecdh{ ECDH::generateKeyPair() };

    /* logger */
    std::shared_ptr<spdlog::logger> logger;

public:
    explicit QQClient(uint64_t uin);
    bool login();

    ~QQClient();

private:
    // 登录的相关函数
    bool tokenLogin(const ByteArray& data);
    bool passwordLogin(const ByteArray& data);
    bool qrcodeLogin();
    bool fetchQrcode();
    // 二维码登录的相关函数
    void queryQrcodeResult();

    /**
     * @brief
     *
     * @param cmd
     * @param body "wtlogin.login" "wtlogin.exchange_emp" "wtlogin.trans_emp"
     * "StatSvc.register" "Client.CorrectTime"
     * @param type 0  1  2
     * @return ByteArray
     */
    ByteArray buildLoginPacket(std::string cmd, const ByteArray& body,
                               uint8_t type = 2);
    // buildCode2dPacket(this: BaseClient, cmdid: number, head: number, body: Buffer)
    ByteArray buildCode2dPacket(uint16_t cmdid, uint32_t head, const ByteArray& body);
};
};     // namespace Flee
#endif // FLEE_CLIENT_H