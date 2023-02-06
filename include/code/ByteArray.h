#ifndef FLEE_BYTEARRAY_H
#define FLEE_BYTEARRAY_H

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <json/value.h>
#include <string>
#include <vector>

/*
/usr/bin/g++ --driver-mode=g++ -DFMT_SHARED -DSPDLOG_COMPILED_LIB
-DSPDLOG_FMT_EXTERNAL -DSPDLOG_SHARED_LIB -Dflee_EXPORTS -
I/mnt/c/Users/Moon/code/VSCodeProject/Flee/include/code
-I/mnt/c/Users/Moon/code/VSCodeProject/Flee/include/exception -
I/mnt/c/Users/Moon/code/VSCodeProject/Flee/include/util -isystem
/usr/include/jsoncpp -g -fPIC -c -x c++-header -std=gnu++17 -resource-
dir=/usr/lib/llvm-14/lib/clang/14.0.6 --
*/

namespace Flee {

using Byte      = std::byte;
using ByteArray = std::vector<std::byte>;

#define ByteArray_0 ByteArray(0, Byte(0x00))

/**
 * @brief
 *
 * @param value_1
 * @param value_2
 * @return ByteArray
 */
ByteArray operator+(const ByteArray& value_1, const ByteArray& value_2);

/**
 * @brief ByteArray的 ostream 重载
 *
 * @param stream 输出流 如: std::cout
 * @param array ByteArray 输入数据
 * @return std::ostream& 将 stream 流返回  输出流 如: std::cout
 */
std::ostream& operator<<(std::ostream& stream, const ByteArray& array);

/**
 * @brief ByteArray的 istream 重载
 *
 * @param stream  输入流 如: std::cin
 * @param array ByteArray 输出数据
 * @return std::istream&  将 stream 流返回  输入流 如: std::cin
 */
std::istream& operator>>(std::istream& stream, ByteArray& array);

/**
 * @brief ByteArray 的 operator<< 数据输入
 *
 * @tparam T 任何数据类型的数据
 * @param array 被输入的 ByteArray
 * @param value 输入值
 * @return ByteArray& 被输入的 ByteArray
 */
template <typename T = uint8_t>
inline ByteArray& operator<<(ByteArray& array, const T& value) {
    static_assert(std::is_arithmetic<T>::value | std::is_same<T, char>::value
                      | std::is_same<T, std::byte>::value,
                  "T must be a numeric, char, byte type");
    size_t size = sizeof(T);
    // 将value的数据逆序拷贝到array
    std::reverse_copy(reinterpret_cast<std::byte const*>(&value),
                      reinterpret_cast<std::byte const*>(&value + 1),
                      std::back_inserter(array));
    return array;
}

template <>
ByteArray& operator<< <ByteArray>(ByteArray& array, const ByteArray& value);

template <>
ByteArray& operator<< <std::string>(ByteArray& array, const std::string& value);

inline ByteArray& operator<<(ByteArray& array, const char value[]) {
    std::copy(reinterpret_cast<std::byte const*>(value),
              reinterpret_cast<std::byte const*>(value + strlen(value)),
              std::back_inserter(array));
    return array;
}

template <typename T>
ByteArray& operator>>(ByteArray& array, T& value) {
    size_t size = sizeof(T);
    if(array.size() > size) {
        // 将array的前sizeof(T)个元素拷贝到value的内存中
        std::reverse_copy(array.begin(), array.begin() + size,
                          reinterpret_cast<std::byte*>(&value));
        // 将array的前sizeof(T)个元素删除
        array.erase(array.begin(), array.begin() + size);
    } else {
        std::reverse_copy(array.begin(), array.end(),
                          reinterpret_cast<std::byte*>(&value));
        // 将array的前sizeof(T)个元素删除
        array.erase(array.begin(), array.end());
    }
    return array;
}

/**
 * @brief 读取Hex进制字符串的数据，存储在ByteArray中
 *
 * @param hex Hex进制字符串
 * @return ByteArray Hex进制的数据
 */
ByteArray toByteArrayFromHex(std::string hex);

/**
 * @brief 从不同的数据类型读取数据
 *
 * @tparam T
 * @param value
 * @return ByteArray
 */
template <typename T>
ByteArray toByteArray(const T& value) {
    ByteArray bytes;
    return std::move(bytes << value);
}

template <typename T>
inline T ByteArrayTo(const ByteArray& array);

template <>
std::string ByteArrayTo<std::string>(const ByteArray& array);

}; // namespace Flee

template <>
Flee::ByteArray Json::Value::as<Flee::ByteArray>() const;

#endif // FLEE_BYTEARRAY_H
