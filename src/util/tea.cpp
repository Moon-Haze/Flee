/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-03-04 18:33
 * @FilePath: \Flee\src\util\tea.cpp
 * @@Description::
 */

#include "tea.h"
#include "constants.h"
#include <assert.h>
#include <cmath>
#include <cstdint>
#include <utility>

#define DELTA 0x9e3779b9
#define UINT32_MASK 0xffffffff

Flee::ByteArray _encrypt_(Flee::ByteArray value, const uint32_t key_0,
                          const uint32_t key_1, const uint32_t key_2,
                          const uint32_t key_3, uint8_t time = 16) {
    using namespace Flee;
    ByteArray encrypt_out;
    uint32_t  sum, left, right, tmpLeft, tmpRight;
    uint32_t  lastLeft0 = 0, lastRight0 = 0, lastLeft1 = 0, lastRight1 = 0;

    while(value.size()) {
        sum = 0;
        value >> left;  // v0
        value >> right; // v1

        // step 1  -> 原数据 异或 上次加密后的数据
        left ^= lastLeft1;
        right ^= lastRight1;

        tmpLeft  = left;
        tmpRight = right;
        for(uint8_t i = 0; i < time; i++) {
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
    return std::move(encrypt_out);
}

Flee::ByteArray _decode_(Flee::ByteArray value, const uint32_t key_0,
                         const uint32_t key_1, const uint32_t key_2,
                         const uint32_t key_3, const uint8_t time = 16) {
    using namespace Flee;
    ByteArray decrypt_out;
    uint32_t  sum, left, right, tmpLeft, tmpRight;
    uint32_t  lastLeft0 = 0, lastRight0 = 0, lastLeft1 = 0, lastRight1 = 0;
    while(value.size()) {
        sum = DELTA << ( int )(log(time) / log(2));
        value >> left;  // v0
        value >> right; // v1

        tmpLeft  = left;
        tmpRight = right;

        left ^= lastLeft0;
        right ^= lastRight0;

        for(uint8_t i = 0; i < time; i++) {
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
    return std::move(decrypt_out);
}

namespace Flee {

ByteArray Tea::encrypt(const ByteArray& key, const ByteArray& value) {
    assert(key.size() == 16);

    ByteArray useData;
    uint8_t   size = (value.size() + 10) % 8;
    if(size != 0) {
        size = 8 - size;
    }
    useData << Byte(getRandom<uint8_t>() & 0xf8 | size);
    for(int i = 0; i < size + 2; i++) {
        useData << Byte(getRandom<uint8_t>() & 0xff);
    }
    useData << value << uint32_t(0) << uint16_t(0) << uint8_t(0);

    return std::move(_encrypt_(std::move(useData), key.to<uint32_t>(),
                               key.to<uint32_t>(4), key.to<uint32_t>(8),
                               key.to<uint32_t>(12)));
}

ByteArray Tea::decrypt(const ByteArray& key, const ByteArray& value) {
    assert(key.size() == 16);
    assert(value.size() % 8 == 0);
    ByteArray data = _decode_(value, key.to<uint32_t>(), key.to<uint32_t>(4),
                              key.to<uint32_t>(8), key.to<uint32_t>(12));
    data.discardExact((static_cast<char>(data.at(0)) & 7) + 3);
    data.discardExact(-7);
    return std::move(data);
}

} // namespace Flee