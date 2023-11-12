/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-02-08 14:09
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-11 22:07
 * @FilePath: \Flee\include\code\DataPacket.h
 * @Description: 接收到的数据经过处理分割后生成的数据包
 */
#ifndef FLEE_DATAPACKET_H
#define FLEE_DATAPACKET_H

#include "ByteArray.h"
#include <string>
#include <utility>

namespace Flee {

class DataPacket {
public:
    int         seq;
    ByteArray   data;
    std::string cmd;
    int         flag2 = -1;

    explicit DataPacket();

    DataPacket(int seq, const ByteArray& data, const std::string& commandName);

    DataPacket(int seq, const ByteArray& data, const std::string& commandName,
               int flag2);

    DataPacket(const DataPacket& packet);

    bool isEmpty() const;

    DataPacket& operator=(const DataPacket& packet) {
        this->seq   = packet.seq;
        this->data  = packet.data;
        this->cmd   = packet.cmd;
        this->flag2 = packet.flag2;
        return *this;
    }
};
}; // namespace Flee

#endif // FLEE_DATAPACKET_H
