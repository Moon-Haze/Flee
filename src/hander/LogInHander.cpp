/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-03-04 20:57
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-03-05 18:58
 * @FilePath: \Flee\src\hander\LogInHander.cpp
 * @Description:
 */
#include "LogInHander.h"

namespace Flee {

void LogInHander::qrcode(const std::string& filename, const ByteArray& data) {
    std::ofstream ofs;
    ofs.open(filename, std::ios::binary);
    if(ofs.is_open()) {
        ofs << data;
        // ofs.write(( char* )data.data(), data.size());
    }
    ofs.close();
}
} // namespace Flee