/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-03-04 18:32
 * @FilePath: \Flee\src\util\ecdh.cpp
 * @Description:
 */
#include "ecdh.h"
#include "ByteArray.h"
#include "constants.h"
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <spdlog/spdlog.h>
#include <stdexcept>
#include <utility>

#include <openssl/bn.h>
#include <openssl/core_names.h>
#include <openssl/dh.h>
#include <openssl/ec.h>
#include <openssl/err.h>
#include <openssl/evp.h>
#include <openssl/param_build.h>
// #define CURVE CryptoPP::ASN1::secp256r1() // prime256v1
#define CURVE "P-256"

// #define DEFAULTPUBLICKEY                                                              \
//     Flee::ByteArray::fromHex(                                                         \
//         "04 ED B8 90 60 46 F5 BF BE 9A BB C5 A8 8B 37 D7 0A 60 06 BF BA BC 1F 0C D4 " \
//         "9D FB 33 50 5E 63 EF C5 D7 8E E4 E0 A4 59 50 33 B9 3D 02 09 6D CD 31 90 27 " \
//         "92 11 F7 B4 F6 78 50 79 E1 90 04 AA 0E 03 BC")

// #define DEFAULTSHAREDKEY \
//     Flee::ByteArray::fromHex("C1 29 ED BA 73 6F 49 09 EC C4 AB 8E 01 0F 46 A3")

static int get_key_values(EVP_PKEY* pkey) {
    int           result = 0;
    char          out_curvename[80];
    unsigned char out_pubkey[80];
    unsigned char out_privkey[80];
    BIGNUM*       out_priv = NULL;
    size_t        out_pubkey_len, out_privkey_len = 0;

    if(!EVP_PKEY_get_utf8_string_param(pkey, OSSL_PKEY_PARAM_GROUP_NAME, out_curvename,
                                       sizeof(out_curvename), NULL)) {
        fprintf(stderr, "Failed to get curve name\n");
        goto cleanup;
    }

    if(!EVP_PKEY_get_octet_string_param(pkey, OSSL_PKEY_PARAM_PUB_KEY, out_pubkey,
                                        sizeof(out_pubkey), &out_pubkey_len)) {
        fprintf(stderr, "Failed to get public key\n");
        goto cleanup;
    }

    if(!EVP_PKEY_get_bn_param(pkey, OSSL_PKEY_PARAM_PRIV_KEY, &out_priv)) {
        fprintf(stderr, "Failed to get private key\n");
        goto cleanup;
    }

    out_privkey_len = BN_bn2bin(out_priv, out_privkey);
    if(out_privkey_len <= 0 || out_privkey_len > sizeof(out_privkey)) {
        fprintf(stderr, "BN_bn2bin failed\n");
        goto cleanup;
    }

    fprintf(stdout, "Curve name: %s\n", out_curvename);
    fprintf(stdout, "Public key:\n");
    BIO_dump_indent_fp(stdout, out_pubkey, out_pubkey_len, 2);
    fprintf(stdout, "Private Key:\n");
    BIO_dump_indent_fp(stdout, out_privkey, out_privkey_len, 2);

    result = 1;
cleanup:
    /* Zeroize the private key data when we free it */
    BN_clear_free(out_priv);
    return result;
}

namespace Flee {

ByteArray ECDH::keyStr{ ByteArray::fromHex(
    "04EBCA94D733E399B2DB96EACDD3F69A8BB0F74224E2B44E3357812211D2E62EFBC91BB553"
    "098E25E33A799ADC7F76FEB208DA7C6522CDB0719A305180CC54A82E") };

ECDH::ECDH() {
    ERR_clear_error();

    OSSL_PARAM_BLD* paramBuild(OSSL_PARAM_BLD_new());
    OSSL_PARAM*     params;
    EVP_PKEY_CTX*   ctx;
    if((paramBuild == nullptr)
       || (!OSSL_PARAM_BLD_push_utf8_string(paramBuild, OSSL_PKEY_PARAM_GROUP_NAME,
                                            CURVE, 5))
       || ((params = OSSL_PARAM_BLD_to_param(paramBuild)) == nullptr)
       || ((ctx = EVP_PKEY_CTX_new_from_name(nullptr, "EC", nullptr)) == nullptr)
       || (EVP_PKEY_keygen_init(ctx) <= 0) || (!EVP_PKEY_CTX_set_params(ctx, params))
       || (EVP_PKEY_generate(ctx, &keyPair) <= 0)) {
        EVP_PKEY_CTX_free(ctx);
        OSSL_PARAM_free(params);
        OSSL_PARAM_BLD_free(paramBuild);
        throw std::runtime_error("Failed to generate ecdh.");
    }

    EVP_PKEY_CTX_free(ctx);
    OSSL_PARAM_free(params);
    OSSL_PARAM_BLD_free(paramBuild);
    // get_key_values(keyPair);

    calculateSharedKey(keyStr);
}
ECDH::ECDH(const ECDH& other) {}

ECDH::~ECDH() {
    EVP_PKEY_free(keyPair);
}

const ByteArray& ECDH::getSharedKey() const {
    return sharedKey;
}

const ByteArray& ECDH::getMaskedSharedKey() const {
    return maskedSharedKey;
}
ByteArray ECDH::getPublicKey() const {
    ERR_clear_error();
    ByteArray value(65);
    if(keyPair
       && EVP_PKEY_get_octet_string_param(keyPair, OSSL_PKEY_PARAM_PUB_KEY,
                                          ( uint8_t* )value.data(), 65, nullptr)) {
        return std::move(value);
    } else {
        throw std::runtime_error("Failed to get ecdh's public key.");
    }
    return {};
}

ByteArray ECDH::getPrivateKey() const {
    ERR_clear_error();
    BIGNUM* key_value = nullptr;
    if(keyPair
       && EVP_PKEY_get_bn_param(keyPair, OSSL_PKEY_PARAM_PRIV_KEY, &key_value)) {
        // 获取 BIGNUM 的二进制表示
        int       bn_length = BN_num_bytes(key_value);
        ByteArray bn_bytes(bn_length);
        BN_bn2bin(key_value, reinterpret_cast<unsigned char*>(bn_bytes.data()));
        BN_free(key_value);
        return std::move(bn_bytes);
    } else {
        BN_free(key_value);
        throw std::runtime_error("Failed to get ecdh's private key.");
    }
    return {};
}

const ByteArray& ECDH::getKeyStr() {
    return keyStr;
}

bool ECDH::calculateSharedKey(const ByteArray& pubKey) {

    ERR_clear_error();
    // 生成  EVP_PKEY
    OSSL_PARAM_BLD* paramBuild(OSSL_PARAM_BLD_new());
    OSSL_PARAM*     params           = nullptr;
    EVP_PKEY_CTX*   peerPublicKeyCtx = nullptr;
    EVP_PKEY*       peerPublicKey    = nullptr;
    if(paramBuild == nullptr
       || (!OSSL_PARAM_BLD_push_utf8_string(paramBuild, OSSL_PKEY_PARAM_GROUP_NAME,
                                            CURVE, 5))
       || (!OSSL_PARAM_BLD_push_octet_string(paramBuild, OSSL_PKEY_PARAM_PUB_KEY,
                                             pubKey.data(), pubKey.size()))
       || (params = OSSL_PARAM_BLD_to_param(paramBuild)) == nullptr
       || (peerPublicKeyCtx = EVP_PKEY_CTX_new_from_name(nullptr, "EC", nullptr))
              == nullptr
       || (EVP_PKEY_fromdata_init(peerPublicKeyCtx) <= 0)
       || (EVP_PKEY_fromdata(peerPublicKeyCtx, &peerPublicKey, EVP_PKEY_PUBLIC_KEY,
                             params)
           <= 0)) {
        throw std::runtime_error("Failed to load ecdh's public key.");
    }

    EVP_PKEY_CTX_free(peerPublicKeyCtx);
    OSSL_PARAM_free(params);
    OSSL_PARAM_BLD_free(paramBuild);

    // Create the derivation context.
    EVP_PKEY_CTX* derivationCtx(EVP_PKEY_CTX_new(keyPair, nullptr));
    size_t        sharedSecretLength = 0;
    if((derivationCtx == nullptr) || (EVP_PKEY_derive_init(derivationCtx) <= 0)
       || (EVP_PKEY_derive_set_peer(derivationCtx, peerPublicKey) <= 0)

       || (EVP_PKEY_derive(derivationCtx, nullptr, &sharedSecretLength) <= 0)
       || (sharedSecretLength == 0)
       || (EVP_PKEY_derive(derivationCtx, ( uint8_t* )sharedKey.data(),
                           &sharedSecretLength)
           <= 0)) {
        EVP_PKEY_CTX_free(derivationCtx);
        throw std::runtime_error("Failed to calculate ecdh's Shared Key.");
    }
    EVP_PKEY_CTX_free(derivationCtx);

    maskedSharedKey = md5(sharedKey.mid(0, 16));
    return true;
}

} // namespace Flee
