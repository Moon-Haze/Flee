#ifndef FLEE_ACCOUNTSECRETS_H
#define FLEE_ACCOUNTSECRETS_H

#include "ByteArray.h"
#include "constants.h"

namespace Flee {

struct BigData {
    std::string ip   = "";
    uint16_t    port = 0;
    ByteArray   sig_session{ 0 };
    ByteArray   session_key{ 0 };
    explicit BigData() = default;
    explicit BigData(const std::string& ip, uint16_t port,
                     const ByteArray& sig_session, const ByteArray& session_key)
        : ip(ip),
          port(port),
          sig_session(sig_session),
          session_key(session_key) {}
    explicit BigData(const BigData& other)
        : BigData(other.ip, other.port, other.sig_session, other.session_key){};
};
struct AccountSecrets {
    /* data */
    uint32_t  seq     = getRandomUInt() & 0xfff;
    ByteArray session = getRandomByteArray(4);
    ByteArray randkey = getRandomByteArray(16);
    ByteArray tgtgt   = getRandomByteArray(16);
    ByteArray tgt{ 0 };
    ByteArray skey{ 0 };
    ByteArray d2{ 0 };
    ByteArray d2key{ 0 };
    ByteArray t104{ 0 };
    ByteArray t174{ 0 };
    ByteArray qrsig{ 0 };
    BigData   bigdata{};

    /**
     * @brief hb480 未完成
     */
    ByteArray hb480{ 9 };
    uint64_t  emp_time  = 0;
    uint64_t  time_diff = 0;

    AccountSecrets(uint32_t uin);
    AccountSecrets(const AccountSecrets& other);
    ~AccountSecrets() = default;
};
};     // namespace Flee
#endif // __ACCOUNTSECRETS_H__