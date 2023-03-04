#ifndef FLEE_ECDH_H
#define FLEE_ECDH_H
#include "ByteArray.h"
#include <cryptopp/eccrypto.h>
namespace Flee {

class ECDH {
private:
    /* data */
    CryptoPP::ECDH<CryptoPP::ECP>::Domain domain;
    ByteArray                             privateKey;
    ByteArray                             publicKey;
    ByteArray                             shareKey;
    ByteArray                             maskedShareKey;

    static ByteArray keyStr;

public:
    explicit ECDH();
    ECDH(const ECDH& other);
    ~ECDH() = default;

    const ByteArray& getPrivateKey() const;

    void setPrivateKey(const ByteArray& privateKey);

    const ByteArray& getPublicKey() const;

    void setPublicKey(const ByteArray& value);

    const ByteArray& getShareKey() const;

    void setShareKey(const ByteArray& value);

    static const ByteArray& getKeyStr();

    bool isDefault() const;

    bool operator==(const ECDH& other) const;

    // bool calculateShareKey(const ECDH &pair);

    /**
     * @brief 通过输入的公钥，计算Share key
     *
     * @param pubKey 输入的公钥
     * @return true 如果成功，则返回true;
     * @return false 如果失败，则返回false。
     */
    bool calculateShareKey(const ByteArray& pubKey);
};
} // namespace Flee
#endif // FLEE_ECDH_H