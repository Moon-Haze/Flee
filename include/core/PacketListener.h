/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-02-11 12:44
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-11 13:11
 * @FilePath: \Flee\include\code\packetListener.h
 * @Description:
 */
#ifndef FLEE_PACKETLISTENER_H
#define FLEE_PACKETLISTENER_H
#include "ByteArray.h"
#include <cstdint>
#include <functional>
#include <map>
#include <mutex>
namespace Flee {
class PacketListener {
private:
    using listen_function = std::function<void(ByteArray&)>;
    std::map<uint32_t, listen_function> func_pool;
    std::mutex                          d_mutex;

public:
    // PacketListener();

    void add(uint32_t seq, listen_function func);

    bool contain(uint32_t seq) const;

    listen_function get(uint32_t seq);
};
}; // namespace Flee

#endif // FLEE_PACKETLISTENER_H