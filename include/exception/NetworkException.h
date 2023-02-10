/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-02-07 13:35
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-07 18:56
 * @FilePath: \Flee\include\exception\NetworkException.h
 * @Description:
 */
#ifndef FLEE_JSONEXCEPTION_H
#define FLEE_JSONEXCEPTION_H

#include <stdexcept>
#include <string>

namespace Flee {

class NetworkException : public std::runtime_error {

public:
    enum NetworkExceptionType {
        ResolveError,
        ConnectionError,
        WriteError,
        ReadError,
        CloseError,
        UnknownError = -1
    };

    NetworkException(const std::string&   message,
                     NetworkExceptionType type = UnknownError);

private:
    NetworkExceptionType exception_type;
};

};     // namespace Flee
#endif // FLEE_NETWORKEXCEPTION_H