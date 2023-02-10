/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-02-08 14:09
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-08 14:12
 * @FilePath: \Flee\include\code\DataPacket.h
 * @Description:
 */
//
// Created by Moon on 2021/3/6.
//

#ifndef Flee_DATAPACKET_H
#define Flee_DATAPACKET_H

#include "ByteArray.h"
#include <string>
#include <utility>

namespace Flee {

class DataPacket {
    int         sequenceId;
    ByteArray   data;
    std::string commandName;
    int         flag2 = -1;

public:
    explicit DataPacket();

    DataPacket(int sequenceId, const ByteArray& data, const std::string& commandName);

    DataPacket(int sequenceId, const ByteArray& data, const std::string& commandName,
               int flag2);

    DataPacket(const DataPacket& packet);

    int getSequenceId() const;

    void setSequenceId(int id);

    const ByteArray& getData() const;

    void setData(const ByteArray& data);

    const std::string& getCommandName() const;

    void setCommandName(const std::string& commandName);

    int getFlag2() const;

    void setFlag2(int flag2);

    bool isEmpty() const;

    DataPacket& operator=(const DataPacket& packet) {
        this->sequenceId  = packet.sequenceId;
        this->data        = packet.data;
        this->commandName = packet.commandName;
        this->flag2       = packet.flag2;
        return *this;
    }
};
}; // namespace Flee

#endif // Flee_DATAPACKET_H
