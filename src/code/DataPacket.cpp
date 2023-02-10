//
// Created by Moon on 2021/3/6.
//

#include "DataPacket.h"
namespace Flee {

DataPacket::DataPacket(int sequenceId, const ByteArray& data,
                       const std::string& commandName)
    : sequenceId(sequenceId), data(data), commandName(commandName) {}

DataPacket::DataPacket(int sequenceId, const ByteArray& data,
                       const std::string& commandName, int flag2)
    : sequenceId(sequenceId), data(data), commandName(commandName), flag2(flag2) {}

DataPacket::DataPacket(const DataPacket& packet)
    : sequenceId(packet.sequenceId),
      data(packet.data),
      commandName(packet.commandName),
      flag2(packet.flag2) {}

int DataPacket::getSequenceId() const {
    return sequenceId;
}

void DataPacket::setSequenceId(int id) {
    DataPacket::sequenceId = id;
}

const ByteArray& DataPacket::getData() const {
    return data;
}

void DataPacket::setData(const ByteArray& data) {
    DataPacket::data = data;
}

const std::string& DataPacket::getCommandName() const {
    return commandName;
}

void DataPacket::setCommandName(const std::string& commandName) {
    DataPacket::commandName = commandName;
}

int DataPacket::getFlag2() const {
    return flag2;
}

void DataPacket::setFlag2(int flag2) {
    DataPacket::flag2 = flag2;
}

bool DataPacket::isEmpty() const {
    if(commandName == "" && sequenceId == 0 && flag2 == -1 && data.empty()) {
        return true;
    }
    return false;
}
}; // namespace Flee