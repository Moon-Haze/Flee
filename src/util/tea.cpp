/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-06 23:49
 * @FilePath: \Flee\src\util\tea.cpp
 * @@Description::
 */

#include "tea.h"
#include "constants.h"
#include <assert.h>
#include <cmath>

#define DELTA 0x9e3779b9
#define UINT32_MASK 0xffffffff

Flee::ByteArray _encode(Flee::ByteArray value, const uint32_t key_0,
                        const uint32_t key_1, const uint32_t key_2,
                        const uint32_t key_3, int time = 0) {
    using namespace Flee;
    ByteArray encrypt_out, data;
    uint32_t  sum, left, right, tmpLeft, tmpRight;
    uint32_t  lastLeft0 = 0, lastRight0 = 0, lastLeft1 = 0, lastRight1 = 0;

    for(int i = 0; i < value.size() / 8; i++) {
        sum = 0;
        value >> left;  // v0
        value >> right; // v1

        // step 1  -> 原数据 异或 上次加密后的数据
        left ^= lastLeft1;
        right ^= lastRight1;
        tmpLeft  = left;
        tmpRight = right;
        for(int j = 0; j < time; j++) {
            sum = sum + DELTA & UINT32_MASK;
            left += ((right << 4) + key_0) ^ (right + sum) ^ ((right >> 5) + key_1);
            right += ((left << 4) + key_2) ^ (left + sum) ^ ((left >> 5) + key_3);
        }
        left ^= lastLeft0;
        right ^= lastRight0;
        // 原来的数据
        lastLeft0  = tmpLeft;
        lastRight0 = tmpRight;
        // 加密后的数据
        lastLeft1  = left;
        lastRight1 = right;
        encrypt_out << left << right;
    }
    return encrypt_out;
}

Flee::ByteArray _decode(Flee::ByteArray value, const uint32_t key_0,
                        const uint32_t key_1, const uint32_t key_2,
                        const uint32_t key_3, int time = 0) {
    using namespace Flee;
    ByteArray decrypt_out;
    uint32_t  sum, left, right, tmpLeft, tmpRight;
    uint32_t  lastLeft0 = 0, lastRight0 = 0, lastLeft1 = 0, lastRight1 = 0;
    for(size_t i = 0; i < value.size() / 8; i++) {
        sum = DELTA << ( int )(log(time) / log(2));
        value >> left;  // v0
        value >> right; // v1
        tmpLeft  = left;
        tmpRight = right;
        left ^= lastLeft0;
        right ^= lastRight0;

        for(int j = 0; j < time; j++) {
            right -= ((left << 4) + key_2) ^ (left + sum) ^ ((left >> 5) + key_3);
            left -= ((right << 4) + key_0) ^ (right + sum) ^ ((right >> 5) + key_1);
            sum -= DELTA;
        }

        lastLeft0  = left;
        lastRight0 = right;

        left ^= lastLeft1;
        right ^= lastRight1;

        lastLeft1  = tmpLeft;
        lastRight1 = tmpRight;
        decrypt_out << left << right;
    }
    return decrypt_out;
}

namespace Flee {

// using namespace Flee;

ByteArray Tea::encrypt(ByteArray key, const ByteArray& value) {
    uint32_t key_0, key_1, key_2, key_3;
    assert(key.size() == 16);

    key >> key_0;
    key >> key_1;
    key >> key_2;
    key >> key_3;

    ByteArray useData;
    int       size = (value.size() + 10) % 8;
    if(size != 0) { size = 8 - size; }
    useData << static_cast<std::byte>(getRandomInt() & 0xf8 | size);
    for(int i = 0; i < size + 2; i++) {
        useData << static_cast<std::byte>(getRandomInt() & 0xff);
    }
    useData << value;
    for(int i = 0; i < 7; i++) { useData << Byte(0x00); }
    return _encode(useData, key_0, key_1, key_2, key_3);
}

ByteArray Tea::decrypt(ByteArray key, const ByteArray& value) {
    uint32_t key_0, key_1, key_2, key_3;
    assert(key.size() == 16);
    key >> key_0;
    key >> key_1;
    key >> key_2;
    key >> key_3;
    ByteArray data = _decode(value, key_0, key_1, key_2, key_3);

    data.erase(data.begin(), data.begin() + ((static_cast<char>(data.at(0)) & 7) + 3));
    data.erase(data.end() - 7, data.end());

    return data;
}

} // namespace Flee