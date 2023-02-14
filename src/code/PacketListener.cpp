/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-02-11 12:44
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-11 13:19
 * @FilePath: \Flee\src\code\packetListener.cpp
 * @Description:
 */
#include "PacketListener.h"

namespace Flee {
void PacketListener::add(uint32_t seq, listen_function func) {
    d_mutex.lock();
    if(this->func_pool.count(seq) == 0) {
        func_pool[seq] = func;
    }
    d_mutex.unlock();
}

bool PacketListener::contain(uint32_t seq) const {
    return (this->func_pool.count(seq) > 0);
}

PacketListener::listen_function PacketListener::get(uint32_t seq) {
    if(this->func_pool.count(seq) > 0) {
        d_mutex.lock();
        auto func = func_pool[seq];
        func_pool.erase(seq);
        d_mutex.unlock();
        return func;
    } else {
        return {};
    }
    return {};
}

} // namespace Flee