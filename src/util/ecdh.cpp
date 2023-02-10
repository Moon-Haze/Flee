#include "ecdh.h"
#include <cryptopp/oids.h>
#include <cryptopp/osrng.h>
#include <iostream>
#include <spdlog/spdlog.h>

#define CURVE CryptoPP::ASN1::secp256r1() // prime256v1

#define DEFAULTPUBLICKEY                                            \
    Flee::ByteArray::fromHex(                                       \
        "04 ED B8 90 60 46 F5 BF BE 9A BB C5 A8 8B 37 D7 0A 60 06 " \
        "BF BA BC 1F 0C D4 9D "                                     \
        "FB 33 50 5E 63 EF C5 D7 8E E4 E0 A4 59 50 33 B9 3D 02 09 " \
        "6D CD 31 90 27 92 11 "                                     \
        "F7 B4 F6 78 50 79 E1 90 04 AA 0E 03 BC")
#define DEFAULTSHAREKEY                                                      \
    Flee::ByteArray::fromHex("C1 29 ED BA 73 6F 49 09 EC C4 AB 8E 01 0F 46 " \
                             "A3")

namespace Flee {

ByteArray ECDH::keyStr{ ByteArray::fromHex(
    "04EBCA94D733E399B2DB96EACDD3F69A8BB0F74224E2B44E3357812211D2E62EFBC91BB553"
    "098E25E33A799ADC7F76"
    "FEB208DA7C6522CDB0719A305180CC54A82E") };

ECDH::ECDH()
    : domain(CURVE),
      privateKey(domain.PrivateKeyLength()),
      publicKey(DEFAULTPUBLICKEY),
      shareKey(DEFAULTSHAREKEY),
      maskedShareKey(domain.AgreedValueLength()) {}
ECDH::ECDH(const ECDH& other)
    : privateKey(other.privateKey),
      publicKey(other.publicKey),
      shareKey(other.shareKey),
      domain(other.domain) {}

ECDH::ECDH(ByteArray privateKey, ByteArray publicKey, ByteArray shareKey,
           ByteArray maskedShareKey, CryptoPP::ECDH<CryptoPP::ECP>::Domain domain)
    : privateKey(std::move(privateKey)),
      publicKey(std::move(publicKey)),
      shareKey(std::move(shareKey)),
      maskedShareKey(std::move(maskedShareKey)),
      domain(std::move(domain)) {}

ECDH ECDH::generateKeyPair() {
    CryptoPP::AutoSeededX917RNG<CryptoPP::AES> rng;
    CryptoPP::ECDH<CryptoPP::ECP>::Domain      dh(CURVE);

    ByteArray privateKey(dh.PrivateKeyLength()), publicKey(dh.PublicKeyLength()),
        shareKey(dh.AgreedValueLength());
    try {
        dh.GenerateKeyPair(rng, ( unsigned char* )privateKey.data(),
                           ( unsigned char* )publicKey.data());

        dh.Agree(( unsigned char* )shareKey.data(), ( unsigned char* )privateKey.data(),
                 ( unsigned char* )ECDH::keyStr.data());
    } catch(const std::exception& e) {
        spdlog::error("ERROR in generating ECDH's Key Pair \n{}", e.what());
    }
    return ECDH{ privateKey, publicKey, ByteArray(), shareKey, dh };
}

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

const ByteArray& ECDH::getMaskedShareKey() const {
    return maskedShareKey;
}

void ECDH::setMaskedShareKey(const ByteArray& value) {
    ECDH::maskedShareKey = value;
}

const ByteArray& ECDH::getKeyStr() {
    return keyStr;
}

void ECDH::setKeyStr(const ByteArray& value) {
    ECDH::keyStr = value;
}
} // namespace Flee
