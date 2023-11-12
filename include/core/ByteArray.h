/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-02-09 13:33
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-03-04 21:35
 * @FilePath: \Flee\include\core\ByteArray.h
 * @Description: Flee库的数据存储class
 */
#ifndef FLEE_BYTEARRAY_H
#define FLEE_BYTEARRAY_H

#include <algorithm>
// #include <corecrt.h>
#include <boost/json/value.hpp>
#include <cstddef>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>


namespace Flee {

using Byte = std::byte;

class ByteArray : public std::vector<Byte> {

public:
    /**
     * @brief 创建一个长度为 @a __n 的对象，并且初始化为 0x00
     *
     * @param __n 初始化的长度
     */
    ByteArray(std::size_t __n = 0);

    /**
     * @brief 拷贝另外一个 @a other ByteArray 初始化对象
     *
     * @param other
     */
    ByteArray(const ByteArray& other);

    /**
     * @brief 从ByteArray的 @a begin 拷贝数据，直到 @a end
     *
     * @param begin
     * @param end
     */
    ByteArray(ByteArray::const_iterator begin, ByteArray::const_iterator end);

    /**
     * @brief 从ByteArray的 @a begin 拷贝数据，直到 @a end
     *
     * @param begin
     * @param end
     */
    ByteArray(std::byte* begin, std::byte* end);

    /**
     * @brief 从ByteArray的 @a begin 拷贝数据，拷贝 @a size
     *
     * @param data 起始位置的指针
     * @param size 拷贝的数据长度
     */
    ByteArray(std::byte* data, std::size_t size);

    /**
     * @brief 列表初始化 ByteArray
     *
     * @param il
     */
    ByteArray(std::initializer_list<std::byte> il);

    /**
     * @brief 从起始位置开始读取 @a T 的长度，并存储到 @a T 的对象中,
     *
     * @tparam T 数字类型
     * @param begin 起始位置，默认是 %ByteArray 的起始位置
     * @return T 存储读取到的数据
     *
     * 如果 %ByteArray 的长度小于 @a T 的长度，则只会读取所有的数据
     */
    template <typename T>
    T to(std::size_t begin = 0) const;

    /**
     * @brief 从 %ByteArray 的起始位置开始读取 @a T 的长度，并存储到 @a T 的对象中,
     * 并且删除读取的数据
     *
     * @tparam T 数字类型
     * @return T 存储读取到的数据
     *
     * 如果 %ByteArray 的长度小于 @a T 的长度，则只会读取所有的数据
     */
    template <typename T>
    T read();

    /**
     * @brief 读取从 @a begin 的索引到 @a end 的索引的数据，存储到%ByteArray
     *
     * @param begin 起始索引
     * @param end 截止索引
     * @return ByteArray 存储从 @a begin 的索引到 @a end 的索引的数据
     */
    ByteArray mid(size_t begin, size_t end) const;

    /**
     * @brief 从 @a index 开始读取数据，读取 @a read_size 长度
     *
     * @param read_size 所要读取的数据长度，默认值为0，表示从 @a index
     * 开始后面的所有的数据
     * @param index 所要读取数据的起始位置
     * @return ByteArray 存储从 @a index 的索引， @a read_size 的长度的数据
     */
    ByteArray readByteArray(size_t read_size = 0, size_t index = 0);

    /**
     * @brief 将从起始位置开始的读取 @a read_size 的长度转化为std::sting
     *
     * @param read_size 所要读取数据的长度，默认值为0，表示%ByteArray的长度
     * @return std::string 转化为 std::sting 的数据
     */
    std::string toString(size_t read_size = 0) const;

    /**
     * @brief 将从 @a index 开始的读取 @a read_size
     * 的长度转化为std::sting，并且删除此段数据
     *
     * @param read_size 所要读取数据的长度，默认值为0，表示%ByteArray的长度
     * @param index 所要读取数据的起始位置
     * @return std::string 转化为 std::sting 的数据
     */
    std::string readString(size_t read_size = 0, size_t index = 0);
    /**
     * @brief 删除从%ByteArrayy的起始位置/结尾位置，长度为 @a delete_size
     *
     * @param delete_size 所要删除的数据长度
     * @param is_start ture  %ByteArrayy的起始位置
     * @param is_start false %ByteArrayy的结尾位置
     */
    iterator discardExact(int64_t delete_size);

    size_t find(Flee::Byte data) const;

    /**
     * @brief 将数据转化为 hex进制的字符串
     *
     * @return std::string hex进制的字符串
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
     * @tparam T 数字、字符串
     * @param value 数据
     * @return ByteArray 从hex进制读取到数据
     */
    template <typename T>
    static ByteArray from(const T& value);
};

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
 * @brief ByteArray的 istream 重载，将 @a array 数据输出到 @a stream 中
 *
 * @param stream  输入流 如: std::cin
 * @param array ByteArray 输出数据
 * @return std::istream&  将 stream 流返回  输入流 如: std::cin
 */
std::istream& operator>>(std::istream& stream, ByteArray& array);

/**
 * @brief ByteArray 的 operator<< 数据输入 将 @a value 的数据拷贝到 @a array
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

/**
 * @brief ByteArray 的 operator<< 数据输入 将char数组 @a value 的数据拷贝到 @a array
 *
 * @param array  被输入的 ByteArray
 * @param value  输入值
 * @return ByteArray&  被输入的 ByteArray
 */
ByteArray& operator<<(ByteArray& array, const char value[]);

/**
 * @brief ByteArray 的 operator<< 数据输入 将%ByteArray @a value 的数据拷贝到 @a array
 *
 * @param array  被输入的 ByteArray
 * @param value  输入值
 * @return ByteArray&  被输入的 ByteArray
 */
template <>
ByteArray& operator<< <ByteArray>(ByteArray& array, const ByteArray& value);

/**
 * @brief ByteArray 的 operator<< 数据输入 将std::string @a value 的数据拷贝到 @a array
 *
 * @param array  被输入的 ByteArray
 * @param value  输入值
 * @return ByteArray&  被输入的 ByteArray
 */
template <>
ByteArray& operator<< <std::string>(ByteArray& array, const std::string& value);

/**
 * @brief ByteArray 的 operator>> 数据输出，读取%ByteArray @a array 的数据到 @a value 中
 *
 * @tparam T 各种数字类型
 * @param array 输出数据的源
 * @param value 输出数据的地方
 * @return ByteArray& 输出数据后的%ByteArray
 */
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

// template <>Flee::ByteArray boost::json::value::as<Flee::ByteArray>() const;

#endif // FLEE_BYTEARRAY_H