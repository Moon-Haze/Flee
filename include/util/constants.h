#ifndef FLEE_CONSTANTS_H
#define FLEE_CONSTANTS_H

#include <chrono>
#include <cstddef>
#include <ctime>

#include <ByteArray.h>
#include <boost/locale/encoding.hpp>
#include <climits>
#include <random>
#include <string>

namespace Flee {

#ifdef __WIN32
#include <winsock2.h>
// This is windows
#include <windows.h>

#define isGBK() GetConsoleOutputCP() == 936
#else
#define isGBK() false
#endif

/**
 * @brief 产生一个随机数
 *
 * @param min 随机数的最小值
 * @param max 随机数的最大值
 * @return int64_t
 */
template <typename T>
T getRandomNumber(T min, T max);

#define getRandomByte() std::byte(getRandom<uint8_t>())

#define fromUTFToGBK(_data_)

#define toGBK(__data__) boost::locale::conv::from_utf(__data__, "GBK")

#define toConsole(__data__) isGBK() ? toGBK(__data__) : __data__

template <typename T>
T getRandom();

/**
 * @brief Get the Random Byte Array object
 *
 * @param length
 * @return ByteArray
 */
ByteArray getRandomByteArray(size_t length);

/**
 * @brief
 *
 */
#define getRandomInt32_t() getRandom<int32_t>()

/**
 * @brief
 *
 */
#define getRandomUInt8_t() getRandom<uint8_t>()
/**
 * @brief Get the Random object
 *
 * @param length
 * @param seed
 * @return std::string
 */
std::string getRandom(int length, std::string seed);
/**
 * @brief
 *
 */
#define getRandomNumString(length) getRandom(length, "0123456789")

/**
 * @brief
 *
 */
#define getRandomBool() getRandom<bool>()

/**
 * @brief
 *
 */
#define getRandomString(length)                                                       \
    getRandom(length, "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXY" \
                      "Z")

/**
 * @brief
 *
 */
std::string generateUUID();

/**
 * @brief
 *
 * @param imei
 * @return uint8_t
 */
uint8_t luhn(std::string imei);

/**
 * @brief
 *
 * @param uin
 * @return std::string
 */
std::string generateImei(uint32_t uin);

/**
 * @brief
 *
 * @return int64_t
 */
int64_t currentTimeMillis();

/**
 * @brief
 *
 * @param format
 * @return std::string
 */
std::string getFormatDateTime(const std::string& format);

/**
 * @brief
 *
 * @return int64_t
 */
#define currentTimeSeconds() currentTimeMillis() / 1000

/**
 * @brief
 *
 * @return int64_t
 */
ByteArray md5(const std::string& str);

/**
 * @brief
 *
 * @param byteArray
 * @return ByteArray
 */
ByteArray md5(const ByteArray& byteArray);
} // namespace Flee
#endif // FLEE_CONSTANTS_H