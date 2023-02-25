/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-02-25 08:49
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-25 09:24
 * @FilePath: \Flee\include\code\log.h
 * @Description:
 */
#ifndef FLEE_LOG_H
#define FLEE_LOG_H
#include <boost/log/trivial.hpp>
#include <boost/log/utility/setup.hpp>
#include <string>

namespace Flee {

void initLog(const std::string& filename);

#define Flee_Trace BOOST_LOG_TRIVIAL(trace)
#define Flee_Debug BOOST_LOG_TRIVIAL(debug)
#define Flee_Info BOOST_LOG_TRIVIAL(info)
#define Flee_Warn BOOST_LOG_TRIVIAL(warning)
#define Flee_Error BOOST_LOG_TRIVIAL(error)

}; // namespace Flee

#endif // FLEE_LOG_H