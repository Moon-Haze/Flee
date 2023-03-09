//
// Created by Moon on 2021/3/6.
//

#include "DataPacket.h"
namespace Flee {

DataPacket::DataPacket(int seq, const ByteArray& data,
                       const std::string& commandName)
    : seq(seq), data(data), cmd(commandName) {}

DataPacket::DataPacket(int seq, const ByteArray& data,
                       const std::string& commandName, int flag2)
    : seq(seq), data(data), cmd(commandName), flag2(flag2) {}

DataPacket::DataPacket(const DataPacket& packet)
    : seq(packet.seq),
      data(packet.data),
      cmd(packet.cmd),
      flag2(packet.flag2) {}

bool DataPacket::isEmpty() const {
    if(cmd == "" && seq == 0 && flag2 == -1 && data.empty()) {
        return true;
    }
    return false;
}
}; // namespace Flee