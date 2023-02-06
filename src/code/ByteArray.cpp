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

namespace Flee {

ByteArray toByteArrayFromHex(std::string hex_data) {
    // 先将空格向字符串的后方移动，如何删除后方的全部字符串。
    hex_data.erase(std::remove(hex_data.begin(), hex_data.end(), ' '),
                   hex_data.end());
    // 将字符串中的小写字母全部变成大写
    std::transform(hex_data.begin(), hex_data.end(), hex_data.begin(),
                   ::toupper);
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

ByteArray operator+(const ByteArray& value_1, const ByteArray& value_2) {
    ByteArray bytes;
    bytes << value_1 << value_2;
    return std::move(bytes);
}

std::ostream& operator<<(std::ostream& stream, const Flee::ByteArray& array) {
    stream << std::hex << std::uppercase << std::setfill('0');
    for(auto it = array.begin(); it != array.end(); ++it) {
        stream << std::setw(2) << std::to_integer<short>(*it) << ' ';
    }
    return stream;
}
std::istream& operator>>(std::istream& stream, Flee::ByteArray& array) {
    std::string data;
    stream >> data;
    array << data;
    return stream;
}

template <>
ByteArray& operator<< <ByteArray>(ByteArray& array, const ByteArray& value) {
    std::copy(value.begin(), value.end(), std::back_inserter(array));
    return array;
}

template <>
ByteArray& operator<< <std::string>(ByteArray&         array,
                                    const std::string& value) {
    std::copy(reinterpret_cast<std::byte const*>(value.data()),
              reinterpret_cast<std::byte const*>(value.data() + value.size()),
              std::back_inserter(array));
    return array;
}

template <typename T>
T ByteArrayTo(const ByteArray& array) {
    T value;
    array >> value;
    return value;
}

template <>
std::string ByteArrayTo<std::string>(const ByteArray& array) {
    return std::string(reinterpret_cast<const char*>(array.data()),
                       array.size());
}

} // namespace Flee

template <>
Flee::ByteArray Json::Value::as<Flee::ByteArray>() const {
    if(isString() | isNumeric()) {
        auto str = asString();
        return std::move(Flee::toByteArray(str.c_str()));
    } else if(isArray()) {
        Flee::ByteArray res;
        for(auto& v : *this) {
            res.push_back(static_cast<std::byte>(v.asInt()));
        }
    }
    return {};
}