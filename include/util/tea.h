#ifndef FLEE_TEA_H
#define FLEE_TEA_H

#include "ByteArray.h"

namespace Flee {

#ifndef DECRYPTER_16_ZERO
#define DECRYPTER_16_ZERO ByteArray(16, Byte(0x00))
#endif

class Tea {

public:
    /**
     * @brief tea 加密
     *
     * @param key 密钥
     * @param value 加密数据
     * @return ByteArray 加密后的数据
     */
    static ByteArray encrypt(ByteArray key, const ByteArray& value);
    /**
     * @brief tea 解密
     *
     * @param key 密钥
     * @param value 解密数据
     * @return ByteArray 解密后的数据
     */
    static ByteArray decrypt(ByteArray key, const ByteArray& value);

private:
    Tea() = default;
};
} // namespace Flee
#endif // FLEE_TEA_H