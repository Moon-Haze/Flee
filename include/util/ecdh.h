#ifndef FLEE_ECDH_H
#define FLEE_ECDH_H
#include "ByteArray.h"
#include <openssl/types.h>

namespace Flee {

class ECDH {
private:
    /* data */
    ByteArray sharedKey{ 32 };
    ByteArray maskedSharedKey;

    /* openssl object  */
    EVP_PKEY* keyPair = nullptr;

    static ByteArray keyStr;

public:
    explicit ECDH();
    ECDH(const ECDH& other);
    ~ECDH();

    ByteArray getPrivateKey() const;

    ByteArray getPublicKey() const;

    const ByteArray& getSharedKey() const;

    const ByteArray& getMaskedSharedKey() const;

    static const ByteArray& getKeyStr();

    /**
     * @brief 通过输入的公钥，计算Share key
     *
     * @param pubKey 输入的公钥
     * @return true 如果成功，则返回true;
     * @return false 如果失败，则返回false。
     */
    bool calculateSharedKey(const ByteArray& pubKey);
};
} // namespace Flee
#endif // FLEE_ECDH_H