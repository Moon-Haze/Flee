/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-02-09 13:33
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-09 20:03
 * @FilePath: \Flee\include\code\ByteArray.h
 * @Description:
 */
#ifndef FLEE_BYTEARRAY_H
#define FLEE_BYTEARRAY_H

#include <algorithm>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <json/value.h>
#include <string>
#include <vector>

namespace Flee {

using Byte = std::byte;

class ByteArray : public std::vector<Byte> {

public:
    ByteArray(std::size_t __n = 0);

    ByteArray(const ByteArray& other);

    ByteArray(ByteArray::const_iterator begin, ByteArray::const_iterator end);

    ByteArray(std::initializer_list<std::byte> il);

    template <typename T>
    T to(size_t index = 0) const;

    template <typename T>
    T readTo(size_t index = 0);

    ByteArray mid(size_t begin, size_t end) const;

    ByteArray readByteArray(size_t begin, size_t end);

    /**
     * @brief
     *
     * @param end_index
     */
    iterator discardExact(size_t end_index);
    /**
     * @brief
     *
     * @return std::string
     */
    std::string toHex() const;

    /**
     * @brief 读取Hex进制字符串的数据，存储在ByteArray中
     *
     * @param hex Hex进制字符串
     * @return ByteArray Hex进制的数据
     */
    static ByteArray fromHex(std::string hex);

    /**
     * @brief 从不同的数据类型读取数据
     *
     * @tparam T
     * @param value
     * @return ByteArray
     */
    template <typename T>
    static ByteArray from(const T& value);
};

template <>
std::string ByteArray::to<std::string>(size_t index) const;

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
template <typename T>
ByteArray& operator<<(ByteArray& array, const T& value) {
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

ByteArray& operator<<(ByteArray& array, const char value[]);

template <>
ByteArray& operator<< <ByteArray>(ByteArray& array, const ByteArray& value);

template <>
ByteArray& operator<< <std::string>(ByteArray& array, const std::string& value);

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
}; // namespace Flee

template <>
Flee::ByteArray Json::Value::as<Flee::ByteArray>() const;

#endif // FLEE_BYTEARRAY_H