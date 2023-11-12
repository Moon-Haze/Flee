/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-16 11:09
 * @FilePath: \Flee\include\code\AccountSecrets.h
 * @Description:
 */
#ifndef FLEE_ACCOUNTSECRETS_H
#define FLEE_ACCOUNTSECRETS_H

#include "ByteArray.h"
#include "constants.h"
#include <atomic>
#include <cstdint>
#include <stdatomic.h>

namespace Flee {

struct BigData {
    std::string ip{};
    uint16_t    port = 0;
    ByteArray   sig_session{ 0 };
    ByteArray   session_key{ 0 };
    explicit BigData() = default;
    explicit BigData(const std::string& ip, uint16_t port, const ByteArray& sig_session,
                     const ByteArray& session_key)
        : ip(ip), port(port), sig_session(sig_session), session_key(session_key) {}
    explicit BigData(const BigData& other)
        : BigData(other.ip, other.port, other.sig_session, other.session_key){};
};
class AccountSecrets {

public:
    /* data */
    std::atomic_int16_t seq     = uint32_t(getRandomUInt8_t() & 0xfff);
    ByteArray           session = getRandomByteArray(4);
    ByteArray           randkey = getRandomByteArray(16);
    ByteArray           tgtgt   = getRandomByteArray(16);
    ByteArray           tgt{ 0 };
    ByteArray           skey{ 0 };
    ByteArray           d2{ 0 };
    ByteArray           d2key{ 0 };
    ByteArray           t104{ 0 };
    ByteArray           t174{ 0 };
    ByteArray           qrsig{ 0 };
    BigData             bigdata{};

    /**
     * @brief hb480 未完成
     */
    ByteArray hb480{ 9 };

    uint64_t emp_time  = 0;
    uint64_t time_diff = 0;

    AccountSecrets(uint32_t uin);

    int16_t seq_pp();

    AccountSecrets(const AccountSecrets& other);

    ~AccountSecrets() = default;
};
};     // namespace Flee
#endif // __ACCOUNTSECRETS_H__