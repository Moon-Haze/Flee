/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-03-04 16:44
 * @FilePath: \Flee\src\util\ecdh.cpp
 * @Description:
 */
#include "ecdh.h"
#include "ByteArray.h"
#include "constants.h"
#include <cryptopp/oids.h>
#include <cryptopp/osrng.h>
#include <iostream>
#include <spdlog/spdlog.h>
#include <utility>

#define CURVE CryptoPP::ASN1::secp256r1() // prime256v1

#define DEFAULTPUBLICKEY                                            \
    Flee::ByteArray::fromHex(                                       \
        "04 ED B8 90 60 46 F5 BF BE 9A BB C5 A8 8B 37 D7 0A 60 06 " \
        "BF BA BC 1F 0C D4 9D "                                     \
        "FB 33 50 5E 63 EF C5 D7 8E E4 E0 A4 59 50 33 B9 3D 02 09 " \
        "6D CD 31 90 27 92 11 "                                     \
        "F7 B4 F6 78 50 79 E1 90 04 AA 0E 03 BC")

#define DEFAULTSHAREKEY \
    Flee::ByteArray::fromHex("C1 29 ED BA 73 6F 49 09 EC C4 AB 8E 01 0F 46 A3")

namespace Flee {

ByteArray ECDH::keyStr{ ByteArray::fromHex(
    "04EBCA94D733E399B2DB96EACDD3F69A8BB0F74224E2B44E3357812211D2E62EFBC91BB553"
    "098E25E33A799ADC7F76"
    "FEB208DA7C6522CDB0719A305180CC54A82E") };

ECDH::ECDH()
    : domain(CURVE),
      privateKey(domain.PrivateKeyLength()),
      publicKey(domain.PublicKeyLength()),
      shareKey(0) {

    CryptoPP::AutoSeededX917RNG<CryptoPP::AES> rng;
    domain.GenerateKeyPair(rng, ( unsigned char* )privateKey.data(),
                           ( unsigned char* )publicKey.data());

    ByteArray share_key(32);
    if(!domain.Agree(( unsigned char* )share_key.data(),
                     ( unsigned char* )privateKey.data(),
                     ( unsigned char* )ECDH::keyStr.data())) {
        spdlog::error("ERROR in generating ECDH's Key Pair.");
    } else {
        share_key.discardExact(16, false);
        shareKey = std::move(md5(share_key));
    }
}

ECDH::ECDH(const ECDH& other)
    : privateKey(other.privateKey),
      publicKey(other.publicKey),
      shareKey(other.shareKey),
      domain(other.domain) {}

bool ECDH::isDefault() const {
    return this->publicKey == DEFAULTPUBLICKEY && this->shareKey == DEFAULTSHAREKEY;
}

bool ECDH::operator==(const ECDH& other) const {
    return this->privateKey == other.privateKey && this->publicKey == other.publicKey
           && this->shareKey == other.shareKey;
}

const ByteArray& ECDH::getShareKey() const {
    return shareKey;
}

void ECDH::setPrivateKey(const ByteArray& value) {
    ECDH::privateKey = value;
}

const ByteArray& ECDH::getPublicKey() const {
    return publicKey;
}

void ECDH::setPublicKey(const ByteArray& value) {
    ECDH::publicKey = value;
}

void ECDH::setShareKey(const ByteArray& value) {
    ECDH::shareKey = value;
}

const ByteArray& ECDH::getPrivateKey() const {
    return privateKey;
}

const ByteArray& ECDH::getKeyStr() {
    return keyStr;
}

} // namespace Flee
