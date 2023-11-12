/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-11 13:36
 * @FilePath: \Flee\include\exception\ParsingException.h
 * @Description:
 */
#ifndef FLEE_PARSINGEXCEPTION_H
#define FLEE_PARSINGEXCEPTION_H

#include <stdexcept>

namespace Flee {

class ParsingException : public std::runtime_error {
public:
    enum ParsingType { JsonError, PacketError, FlagError, ReturnCodeError };
    ParsingException(const std::string& msg, ParsingType type);

private:
    ParsingType exception_type;
};

};     // namespace Flee
#endif // FLEE_PARSINGEXCEPTION_H