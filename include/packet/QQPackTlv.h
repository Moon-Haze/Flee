/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-02-11 15:15
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-03-04 20:56
 * @FilePath: \Flee\include\packet\QQPackTlv.h
 * @Description:
 */
#ifndef FLEE_QQPACKETLV_H
#define FLEE_QQPACKETLV_H

#include "ByteArray.h"
#include "DataPacket.h"
#include "PacketListener.h"
#include "Tlv.h"
#include "ecdh.h"
#include <spdlog/logger.h>

namespace Flee {
class QQPackTlv : public Tlv {

    PacketListener listener;
    // /* logger */
    std::shared_ptr<spdlog::logger> logger;

public:
    using Tlv::Tlv;
    ECDH ecdh{};
    void setLogger(std::shared_ptr<spdlog::logger> logger);

    PacketListener& getPacketListener();
    /**
     * @brief 构建数据包
     *
     * @param cmd
     * @param body "wtlogin.login" "wtlogin.exchange_emp" "wtlogin.trans_emp"
     * "StatSvc.register" "Client.CorrectTime"
     * @param type 0  1  2
     * @return ByteArray
     */
    ByteArray buildLoginPacket(std::string cmd, const ByteArray& body,
                               uint8_t type = 2);

    /**
     * @brief 构建数据包
     *
     * @param cmdid
     * @param head
     * @param body
     * @return ByteArray
     */
    ByteArray buildCode2dPacket(uint16_t cmdid, uint32_t head, const ByteArray& body);

    /**
     * @brief 读取 flag 分割接收数据
     *
     * @param packet 所要处理的数据
     */
    void parseFlagPacket(ByteArray& packet);

    /**
     * @brief sso分割数据包
     *
     * @param packet 所要处理的数据
     * @return DataPacket 分割后封装的数据包


     */
    DataPacket parseSsoPacket(ByteArray& packet);

    void requestQImei() const;
    /**
     * @brief
     *
     * @param buffer
     * @return std::map<uint16_t, ByteArray>
     */
    static std::map<uint16_t, ByteArray> readTlv(ByteArray& buffer);
};
}; // namespace Flee

#endif // FLEE_QQPACKETLV_H