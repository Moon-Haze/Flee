/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-02-11 15:15
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-14 16:54
 * @FilePath: \Flee\include\code\QQPackTlv.h
 * @Description:
 */
#ifndef FLEE_QQPACKETLV_H
#define FLEE_QQPACKETLV_H

#include "DataPacket.h"
#include "PacketListener.h"
#include "Tlv.h"
#include "ecdh.h"
#include <spdlog/logger.h>

namespace Flee {
class QQPackTlv : public Tlv {

    ECDH ecdh{ ECDH::generateKeyPair() };

    PacketListener listener;
    // /* logger */
    std::shared_ptr<spdlog::logger> logger;

public:
    using Tlv::Tlv;

    void setLogger(std::shared_ptr<spdlog::logger> logger);

    PacketListener& getPacketListener();
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

    void parseFlagPacket(ByteArray& packet);

    DataPacket parseSsoPacket(ByteArray& packet);
};
}; // namespace Flee

#endif // FLEE_QQPACKETLV_H