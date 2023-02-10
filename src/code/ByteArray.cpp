#include "ByteArray.h"
#include <algorithm>
#include <codecvt>
#include <cstddef>
#include <cstdint>
#include <cstring>
#include <iomanip>
#include <regex>
#include <sstream>
#include <string>
#include <utility>

namespace Flee {

template <typename T>
ByteArray ByteArray::from(const T& value) {
    ByteArray bytes;
    return std::move(bytes << value);
}

template ByteArray ByteArray::from<std::string>(const std::string& value);

template ByteArray ByteArray::from<uint8_t>(const uint8_t& value);
template ByteArray ByteArray::from<uint16_t>(const uint16_t& value);
template ByteArray ByteArray::from<uint32_t>(const uint32_t& value);
template ByteArray ByteArray::from<uint64_t>(const uint64_t& value);

template ByteArray ByteArray::from<int8_t>(const int8_t& value);
template ByteArray ByteArray::from<int16_t>(const int16_t& value);
template ByteArray ByteArray::from<int32_t>(const int32_t& value);
template ByteArray ByteArray::from<int64_t>(const int64_t& value);

ByteArray ByteArray::fromHex(std::string hex_data) {
    // 先将空格向字符串的后方移动，如何删除后方的全部字符串。
    hex_data.erase(std::remove(hex_data.begin(), hex_data.end(), ' '), hex_data.end());
    // 将字符串中的小写字母全部变成大写
    std::transform(hex_data.begin(), hex_data.end(), hex_data.begin(), ::toupper);
    // 如何字符串的字符数为奇数，则在字符串后面添加 '0'
    if(hex_data.size() % 2) {
        hex_data += "0";
    }
    // 检查字符串是否是十六进制数字
    std::regex hex_pattern("[A-F0-9]{2}([A-F0-9]{2})*");
    if(std::regex_match(hex_data, hex_pattern)) {
        // 输入字符串可以转换为十六进制数据
        ByteArray bytes;
        bytes.reserve(hex_data.size() / 2);
        // 遍历十六进制数据字符串
        for(auto it = hex_data.begin(); it != hex_data.end(); ++it) {
            // 将十六进制字符转换为整数
            uint8_t b1 = *it >= '0' && *it <= '9' ? *it - '0' : *it - 'A' + 10;
            ++it;
            uint8_t b2 = *it >= '0' && *it <= '9' ? *it - '0' : *it - 'A' + 10;
            // 将两个整数合并为一个字节
            bytes.push_back(static_cast<std::byte>((b1 << 4) | b2));
        }
        return std::move(bytes);
    } else {
        // 输入字符串不能转换为十六进制数据
        throw std::invalid_argument("格式错误");
    }
}

ByteArray::ByteArray(std::size_t __n) : std::vector<std::byte>(__n, std::byte(0x00)) {}

ByteArray::ByteArray(const ByteArray& other) : std::vector<std::byte>(other) {}

ByteArray::ByteArray(std::vector<std::byte>::const_iterator begin,
                     std::vector<std::byte>::const_iterator end)
    : std::vector<std::byte>(begin, end) {}

ByteArray::ByteArray(std::initializer_list<std::byte> il)
    : std::vector<std::byte>(il) {}

template <typename T>
T ByteArray::to(size_t index) const {
    size_t size = sizeof(T);
    T      value;
    if(this->size() < (index + 1)) {
        return value;
    } else if((this->size() - index) > size) {
        std::reverse_copy(this->begin() + index, this->begin() + index + size,
                          reinterpret_cast<std::byte*>(&value));
    } else {
        std::reverse_copy(this->begin() + index, this->end(),
                          reinterpret_cast<std::byte*>(&value));
    }
    return value;
}

template uint8_t  ByteArray::to<uint8_t>(size_t index) const;
template uint16_t ByteArray::to<uint16_t>(size_t index) const;
template uint32_t ByteArray::to<uint32_t>(size_t index) const;
template uint64_t ByteArray::to<uint64_t>(size_t index) const;

template int8_t  ByteArray::to<int8_t>(size_t index) const;
template int16_t ByteArray::to<int16_t>(size_t index) const;
template int32_t ByteArray::to<int32_t>(size_t index) const;
template int64_t ByteArray::to<int64_t>(size_t index) const;

template <>
std::string ByteArray::to<std::string>(size_t index) const {
    if(this->size() < (index + 1)) {
        return std::string();
    }
    return std::move(
        std::string(reinterpret_cast<const char*>(this->data() + index), this->size()));
}

template <typename T>
T ByteArray::readTo(size_t index) {
    size_t size = sizeof(T);
    T      value;
    if(this->size() < (index + 1)) {
        return value;
    } else if((this->size() - index) > size) {
        // 将array的前sizeof(T)个元素拷贝到value的内存中
        std::reverse_copy(this->begin() + index, this->begin() + index + size,
                          reinterpret_cast<std::byte*>(&value));

        this->erase(this->begin() + index, this->begin() + index + size);

    } else {
        std::reverse_copy(this->begin() + index, this->end(),
                          reinterpret_cast<std::byte*>(&value));
        this->erase(this->begin(), this->end());
    }
    return std::move(value);
}

template uint8_t  ByteArray::readTo<uint8_t>(size_t index);
template uint16_t ByteArray::readTo<uint16_t>(size_t index);
template uint32_t ByteArray::readTo<uint32_t>(size_t index);
template uint64_t ByteArray::readTo<uint64_t>(size_t index);

template int8_t  ByteArray::readTo<int8_t>(size_t index);
template int16_t ByteArray::readTo<int16_t>(size_t index);
template int32_t ByteArray::readTo<int32_t>(size_t index);
template int64_t ByteArray::readTo<int64_t>(size_t index);

template <>
std::string ByteArray::readTo<std::string>(size_t index) {
    if(this->size() < (index + 1)) {
        return std::string();
    }
    std::string str(reinterpret_cast<const char*>(this->data() + index), this->size());
    this->erase(this->begin() + index, this->end());
    return std::move(str);
}

ByteArray ByteArray::mid(size_t begin, size_t end) const {
    return ByteArray((ByteArray::const_iterator)(this->begin() + begin),
                     (ByteArray::const_iterator)(this->begin() + end));
}

ByteArray ByteArray::readByteArray(size_t begin, size_t end) {
    ByteArray array;
    std::copy(this->begin() + begin, this->begin() + end, std::back_inserter(array));
    this->erase(this->begin() + begin, this->begin() + end);
    return std::move(array);
}

ByteArray::iterator ByteArray::discardExact(size_t end_index) {
    return erase(begin(), begin() + end_index);
}

std::string ByteArray::toHex() const {
    std::stringstream ss;
    ss << (*this);
    return ss.str();
}

ByteArray operator+(const ByteArray& value_1, const ByteArray& value_2) {
    ByteArray bytes;
    bytes << value_1 << value_2;
    return std::move(bytes);
}
std::ostream& operator<<(std::ostream& stream, const ByteArray& array) {
    stream << std::hex << std::uppercase << std::setfill('0');
    for(auto it = array.begin(); it != array.end(); ++it) {
        stream << std::setw(2) << std::to_integer<short>(*it) << ' ';
    }
    stream << std::dec;
    return stream;
}
std::istream& operator>>(std::istream& stream, Flee::ByteArray& array) {
    std::string data;
    stream >> data;
    array << data;
    return stream;
}
ByteArray& operator<<(ByteArray& array, const char value[]) {
    std::copy(reinterpret_cast<std::byte const*>(value),
              reinterpret_cast<std::byte const*>(value + strlen(value)),
              std::back_inserter(array));
    return array;
}
template <>
ByteArray& operator<< <ByteArray>(ByteArray& array, const ByteArray& value) {
    std::copy(value.begin(), value.end(), std::back_inserter(array));
    return array;
}

template <>
ByteArray& operator<< <std::string>(ByteArray& array, const std::string& value) {
    std::copy(reinterpret_cast<std::byte const*>(value.data()),
              reinterpret_cast<std::byte const*>(value.data() + value.size()),
              std::back_inserter(array));
    return array;
}
} // namespace Flee
template <>
Flee::ByteArray Json::Value::as<Flee::ByteArray>() const {
    if(isString() | isNumeric()) {
        auto str = asString();
        return std::move(Flee::ByteArray::from(str.c_str()));
    } else if(isArray()) {
        Flee::ByteArray res;
        for(auto& v : *this) {
            res.push_back(static_cast<std::byte>(v.asInt()));
        }
        return std::move(res);
    }
    return {};
}