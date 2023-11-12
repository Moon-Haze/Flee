/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-11-08 17:31:12
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-11-09 16:05:17
 * @FilePath: /Flee/src/util/RSASecure.cpp
 * @Description:
 */

#include "RSASecure.h"
#include <openssl/err.h>
#include <openssl/evp.h>

namespace Flee {

ByteArray RSASecure::decrypt(ByteArray cyphertext, ByteArray key, ByteArray iv) {
    ERR_clear_error();
    // 检查密钥合法性(只能是16、24、32字节)
    assert(key.size() == 32);
    assert(iv.size() == 16);

    ByteArray       plaintext;
    EVP_CIPHER_CTX* ctx{ EVP_CIPHER_CTX_new() };

    if(!EVP_DecryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, ( unsigned char* )key.data(),
                           ( unsigned char* )iv.data())) {
        plaintext.clear();
        return plaintext;
    }
    if(!EVP_CIPHER_CTX_set_padding(ctx, EVP_PADDING_PKCS7)) {
        plaintext.clear();
        return plaintext;
    }
    int outlen = 0;
    plaintext.resize(cyphertext.size());
    if(!EVP_DecryptUpdate(ctx, ( unsigned char* )plaintext.data(), &outlen,
                          ( unsigned char* )cyphertext.data(), cyphertext.size())) {
        plaintext.clear();
        return plaintext;
    }
    int tmplen = 0;
    if(!EVP_DecryptFinal_ex(ctx, ( unsigned char* )plaintext.data() + outlen,
                            &tmplen)) {
        plaintext.clear();
        return plaintext;
    }
    EVP_CIPHER_CTX_free(ctx);
    return plaintext;
    // return plaintext.left(outlen + tmplen);
}

ByteArray RSASecure::encrypt(ByteArray plaintext, ByteArray key, ByteArray iv) {
    ERR_clear_error();
    // 检查密钥合法性(只能是16、24、32字节)
    assert(key.size() == 32);
    assert(iv.size() == 16);

    ByteArray       cyphertext;
    EVP_CIPHER_CTX* ctx{ EVP_CIPHER_CTX_new() };

    if(!EVP_EncryptInit_ex(ctx, EVP_aes_256_cbc(), NULL, ( unsigned char* )key.data(),
                           ( unsigned char* )iv.data())) {
        cyphertext.clear();
        return cyphertext;
    }
    if(!EVP_CIPHER_CTX_set_padding(ctx, EVP_PADDING_PKCS7)) {
        cyphertext.clear();
        return cyphertext;
    }
    int outlen = 0;
    cyphertext.resize(plaintext.size() + 16);
    if(!EVP_EncryptUpdate(ctx, ( unsigned char* )cyphertext.data(), &outlen,
                          ( const unsigned char* )plaintext.data(), plaintext.size())) {
        cyphertext.clear();
        return cyphertext;
    }
    int tmplen = 0;
    if(!EVP_EncryptFinal_ex(ctx, ( unsigned char* )cyphertext.data() + outlen,
                            &tmplen)) {
        cyphertext.clear();
        return cyphertext;
    }
    EVP_CIPHER_CTX_free(ctx);
    return cyphertext;
    // return cyphertext.left(outlen + tmplen);
}

std::string RSASecure::GetLastError() {
    unsigned long lastError = ERR_peek_last_error();
    if(lastError == 0) {
        return "";
    }
    char errorString[256];
    ERR_error_string_n(lastError, errorString, sizeof(errorString));
    return errorString;
}
}; // namespace Flee
