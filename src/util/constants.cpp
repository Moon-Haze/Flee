#include "constants.h"
#include "ByteArray.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <cstdint>
#include <string>
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

template <typename T>
T getRandom() {
    std::random_device              rd;
    std::mt19937                    gen(rd());
    std::uniform_int_distribution<> dis(std::numeric_limits<T>::min(),
                                        std::numeric_limits<T>::max());
    return std::move(dis(gen));
}

template uint8_t  getRandom<uint8_t>();
template uint16_t getRandom<uint16_t>();
template uint32_t getRandom<uint32_t>();

template int8_t  getRandom<int8_t>();
template int16_t getRandom<int16_t>();
template int32_t getRandom<int32_t>();

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
        byteArray.push_back(static_cast<std::byte>(getRandom<uint8_t>()));
    }
    return std::move(byteArray);
}

std::string generateUUID() {
    return std::move(boost::uuids::to_string(boost::uuids::random_generator()()));
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
std::string generateImei(uint32_t uin) {
    std::string  imei    = uin % 2 ? "86" : "35";
    unsigned int a       = uin >> 16;
    unsigned int b       = uin & 0xFFFFFF;
    std::string  uin_str = std::to_string(uin);
    if(a > 9999) {
        a = a / 10;
    } else if(a < 1000) {
        a = std::stoi(uin_str.substr(0, 4));
    }
    while(b > 9999999) {
        b = b >> 1;
    }
    if(b < 1000000) {
        b = std::stoi(uin_str.substr(0, 4)) + std::stoi(uin_str.substr(0, 3));
    }
    imei += std::to_string(a) + "0" + std::to_string(b);
    int sum = 0;
    for(int i = 0; i < imei.length(); ++i) {
        if(i % 2) {
            int j = (imei[i] - '0') * 2;
            sum += j % 10 + std::floor(j / 10);
        } else {
            sum += imei[i] - '0';
        }
    }
    return imei + std::to_string((100 - sum) % 10);
}

int64_t currentTimeMillis() {
    auto        now    = std::chrono::system_clock::now();
    std::time_t now_c  = std::chrono::system_clock::to_time_t(now);
    std::tm     now_tm = *std::localtime(&now_c);
    return std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch())
        .count();
}

ByteArray md5(const std::string& input) {
    if(!input.empty()) {
        // ?????? CryptoPP::MD5 ??????
        CryptoPP::Weak1::MD5 hash_md5;
        // ???????????????
        hash_md5.Update(reinterpret_cast<const CryptoPP::byte*>(input.data()),
                        input.size());
        // ???????????????
        ByteArray digest(CryptoPP::Weak1::MD5::DIGESTSIZE);
        hash_md5.Final(reinterpret_cast<CryptoPP::byte*>(digest.data()));
        return std::move(digest);
    }
    return std::move(ByteArray());
}

ByteArray md5(const ByteArray& input) {
    if(!input.empty()) {
        // ?????? CryptoPP::MD5 ??????
        CryptoPP::Weak1::MD5 hash_md5;
        // ???????????????
        hash_md5.Update(reinterpret_cast<const CryptoPP::byte*>(input.data()),
                        input.size());
        // ???????????????
        ByteArray digest(CryptoPP::Weak1::MD5::DIGESTSIZE);
        hash_md5.Final(reinterpret_cast<CryptoPP::byte*>(digest.data()));
        return std::move(digest);
    }
    return std::move(ByteArray());
}
}; // namespace Flee