#include "constants.h"
#include <cstdint>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include <cryptopp/md5.h>
#include <iostream>
#include <random>

namespace Flee {

int64_t getRandomNumber(int64_t min, int64_t max) {
    std::random_device              rd;
    std::mt19937                    gen(rd());
    std::uniform_int_distribution<> dis(min, max);
    return std::move(dis(gen));
}

std::string getRandom(int length, std::string seed) {
    std::string string;
    while(length--) {
        string.push_back(seed[getRandomNumber(0, seed.length() - 1)]);
    }
    return std::move(string);
}

ByteArray getRandomByteArray(size_t length) {
    ByteArray byteArray;
    for(int i = 0; i < length; i++) {
        byteArray.push_back(
            static_cast<std::byte>(getRandomNumber(0, UCHAR_MAX)));
    }
    return std::move(byteArray);
}

std::string generateUUID() {
    std::random_device                 rd;
    std::uniform_int_distribution<int> dist(0, 15);
    std::string                        uuid;
    for(int i = 0; i < 32; i++) {
        if(i == 8 || i == 12 || i == 16 || i == 20) {
            uuid += "-";
        }
        int val = dist(rd);
        uuid += "0123456789abcdef"[val];
    }
    return std::move(uuid);
}

uint8_t luhn(std::string imei) {
    bool odd = false;
    int  sum = 0;
    for(int i = imei.length() - 1; i >= 0; i--) {
        int digit = imei[i] - '0';
        if(odd) {
            digit *= 2;
            if(digit > 9) {
                digit -= 9;
            }
        }
        sum += digit;
        odd = !odd;
    }
    return (10 - sum % 10) % 10;
}

int64_t currentTimeMillis() {
    auto        now    = std::chrono::system_clock::now();
    std::time_t now_c  = std::chrono::system_clock::to_time_t(now);
    std::tm     now_tm = *std::localtime(&now_c);
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               now.time_since_epoch())
        .count();
}

ByteArray md5(const std::string& input) {
    if(!input.empty()) {
        // 创建 CryptoPP::MD5 对象
        CryptoPP::Weak1::MD5 hash_md5;
        // 更新哈希值
        hash_md5.Update(reinterpret_cast<const CryptoPP::byte*>(input.data()),
                        input.size());
        // 计算哈希值
        std::vector<std::byte> digest(CryptoPP::Weak1::MD5::DIGESTSIZE);
        hash_md5.Final(reinterpret_cast<CryptoPP::byte*>(digest.data()));
        return std::move(digest);
    }
    return std::move(ByteArray_0);
}

ByteArray md5(const ByteArray& input) {
    if(!input.empty()) {
        // 创建 CryptoPP::MD5 对象
        CryptoPP::Weak1::MD5 hash_md5;
        // 更新哈希值
        hash_md5.Update(reinterpret_cast<const CryptoPP::byte*>(input.data()),
                        input.size());
        // 计算哈希值
        std::vector<std::byte> digest(CryptoPP::Weak1::MD5::DIGESTSIZE);
        hash_md5.Final(reinterpret_cast<CryptoPP::byte*>(digest.data()));
        return std::move(digest);
    }
    return std::move(ByteArray_0);
}
}; // namespace Flee