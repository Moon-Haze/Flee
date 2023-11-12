/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-03-04 20:26
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-03-31 10:10
 * @FilePath: \Flee\include\handler\LogInHandler.h
 * @Description:
 */
#ifndef FLEE_LOGINHANDER_H
#define FLEE_LOGINHANDER_H
#include "ByteArray.h"
#include "handler.h"
#include <cstdint>
#include <fstream>
#include <string>

namespace Flee {

struct QRCodeResult {
    uint8_t   retcode = -1;
    uint32_t  uin;
    ByteArray t106, t16a, t318, tgtgt;
};

struct LoginResponse {
    uint8_t                       type;
    std::map<uint16_t, ByteArray> t;
};

class LogInHandler : public handler {

public:
    using handler::handler;

    bool parseQRCode(ByteArray& buffer, const std::string& filename) const;

    QRCodeResult parseQRCodeResult(ByteArray& buffer) const;

    void    qrcode(const std::string& filename, const ByteArray& data) const;
    uint8_t decodeLoginResponse(ByteArray& buffer) const;
};
} // namespace Flee

#endif // FLEE_LOGINHANDER_H