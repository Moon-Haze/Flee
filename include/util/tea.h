/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-11 15:42
 * @FilePath: \Flee\include\util\tea.h
 * @Description:
 */
#ifndef FLEE_TEA_H
#define FLEE_TEA_H

#include "ByteArray.h"

namespace Flee {

class Tea {

public:
    /**
     * @brief tea 加密
     *
     * @param key 密钥
     * @param value 加密数据
     * @return ByteArray 加密后的数据
     */
    static ByteArray encrypt(const ByteArray& key, const ByteArray& value);
    /**
     * @brief tea 解密
     *
     * @param key 密钥
     * @param value 解密数据
     * @return ByteArray 解密后的数据
     */
    static ByteArray decrypt(const ByteArray& key, const ByteArray& value);

private:
    Tea() = default;
};
} // namespace Flee
#endif // FLEE_TEA_H