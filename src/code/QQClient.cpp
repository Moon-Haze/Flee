#include "QQClient.h"
#include "ByteArray.h"
#include "PackTlv.h"
#include "constants.h"
#include <filesystem>
#include <fstream>
#include <spdlog/sinks/rotating_file_sink.h> // support for rotating file logging
#include <spdlog/sinks/stdout_color_sinks.h> // support for basic file logging
#include <string>

namespace Flee {
// bool isInit = true;

QQClient::QQClient(uint32_t uin, QQConfig config)
    : info(uin, std::move(config)), packet(info) {

    std::string uin_str = std::to_string(uin);
    std::string dir     = config.getDir() + "logs/" + uin_str + ".log";

    std::vector<spdlog::sink_ptr> sinks = {
        std::make_shared<spdlog::sinks::stdout_color_sink_mt>(),
        std::make_shared<spdlog::sinks::rotating_file_sink_mt>(
            dir, 1024 * 1024 * 10, 10)
    };
    //<2.创建使用多个sink的单个logger，logger会把内容输出到不同位置，此处是控制台以及RotatingFileLog.txt
    std::string loggerName =
        std::to_string(config.platform) + ":" + std::to_string(uin);
    logger = std::make_shared<spdlog::logger>(loggerName, sinks.begin(),
                                              sinks.end());
}

bool QQClient::login() {
    uint32_t          id       = info.getUin();
    ByteArray         password = info.getPassword();
    std::stringstream ss;
    ss << info.config.getDir() << "/" << id << "/token";
    std::string dir = ss.str();
    if(password.empty()) {
        if(std::filesystem::exists(dir)) {
            ByteArray    token;
            std::fstream token_file{ dir };
            token_file >> token;
            // token 登录
            return tokenLogin(token);
        } else {
            // 扫码登录 或者 扫码后操作
            return this->info.secrets.qrsig.size() ? qrcodeLogin()
                                                   : fetchQrcode();
        }
    } else {
        // 密码登录
        return passwordLogin(password);
    }
    return false;
}

bool QQClient::tokenLogin(const ByteArray& data) { return false; }

bool QQClient::passwordLogin(const ByteArray& data) { return false; }

bool QQClient::qrcodeLogin() { return false; }

bool QQClient::fetchQrcode() {
    ByteArray body;
    /*
    const body = new writer_1.default()
    .writeU16(0)
    .writeU32(16)
    .writeU64(0)
    .writeU8(8)
    .writeTlv(constants_1.BUF0)
    .writeU16(6)
    .writeBytes(t(0x16))
    .writeBytes(t(0x1B))
    .writeBytes(t(0x1D))
    .writeBytes(t(0x1F))
    .writeBytes(t(0x33))
    .writeBytes(t(0x35))
    .read();
     */
    body << uint16_t(0) << uint32_t(16) << uint64_t(0) << uint8_t(8)
         << DataPacket(ByteArray_0) << uint16_t(6);

    return false;
}

void QQClient::queryQrcodeResult() {
    if(!this->info.secrets.qrsig.size()) {
    } else {
        ByteArray body;
        body << uint16_t(5) << uint8_t(1) << uint32_t(16)
             << DataPacket(this->info.secrets.qrsig) << uint64_t(0)
             << uint8_t(8) << DataPacket<uint16_t>(ByteArray_0) << uint16_t(0);
    }
}

ByteArray QQClient::buildCode2dPacket(uint8_t cmdid, uint32_t head,
                                      const ByteArray& body) {
    /*
    body = new writer_1.default()
        .writeU32(head)
        .writeU32(0x1000)
        .writeU16(0)
        .writeU32(0x72000000)
        .writeU32((0, constants_1.timestamp)())
        .writeU8(2)
        .writeU16(44 + body.length)
        .writeU16(cmdid)
        .writeBytes(Buffer.alloc(21))
        .writeU8(3)
        .writeU16(0)
        .writeU16(50)
        .writeU32(this.sig.seq + 1)
        .writeU64(0)
        .writeBytes(body)
        .writeU8(3)
        .read();
    */
    ByteArray temp;
    temp << head << uint32_t(0x1000) << uint16_t(0) << uint32_t(0x72000000)
         << uint32_t(currentTimeMillis()) << uint8_t(2)
         << uint16_t(44 + body.size()) << uint16_t(cmdid)
         << ByteArray(21, Byte(0)) << uint8_t(3) << uint16_t(0) << uint16_t(50)
         << uint32_t(this->info.secrets.seq + 1) << uint64_t(0) << body
         << uint8_t(3);

    return ByteArray();
}
QQClient::~QQClient() {}
}; // namespace Flee