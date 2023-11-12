/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-11-08 17:31:12
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-11-09 15:59:49
 * @FilePath: /Flee/include/util/RSASecure.h
 * @Description:
 */
#ifndef __RSASECURE_H__
#define __RSASECURE_H__

#include <ByteArray.h>

namespace Flee {

struct RSASecure {
    /**
     * @brief 解密函数
     *
     * @param cyphertext
     * @param key
     * @param iv
     * @return ByteArray
     */
    static ByteArray decrypt(ByteArray cyphertext, ByteArray key, ByteArray iv);

    /**
     * @brief 加密函数
     *
     * @param plaintext
     * @param key
     * @param iv
     * @return ByteArray
     */
    static ByteArray encrypt(ByteArray plaintext, ByteArray key, ByteArray iv);

    // 获取最后一次错误信息
    static std::string GetLastError();
};
} // namespace Flee

#endif // __RSASECURE_H__