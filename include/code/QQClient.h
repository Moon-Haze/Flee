#ifndef FLEE_CLIENT_H
#define FLEE_CLIENT_H

#include "PackTlv.h"
#include "QQConfig.h"
#include <spdlog/spdlog.h>

namespace Flee {

class QQClient {
private:
    /* data */
    QQInfo  info;
    PackTlv packet;

    /* logger */
    std::shared_ptr<spdlog::logger> logger;

public:
    explicit QQClient(uint32_t uin, QQConfig config = QQConfig());

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

    // 登录数据包构建
    ByteArray buildCode2dPacket(uint8_t cmdid, uint32_t head,
                                const ByteArray& body);
};
};     // namespace Flee
#endif // FLEE_CLIENT_H