/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-01-24 20:42
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-02-14 17:39
 * @FilePath: \Flee\test\Flee_test.cpp
 * @Description:
 */

#include <climits>
#include <cstddef>
#include <cstdint>
#include <cwchar>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <json/json.h>
#include <json/value.h>
#include <limits>
#include <random>
#include <string>

int main(int argc, char** argv) {
    Json::Value root;
    root["name"]        = "swx";
    root["description"] = "hello, testing json.";
    Json::StreamWriterBuilder           writerBuilder;
    std::unique_ptr<Json::StreamWriter> jsonWriter(writerBuilder.newStreamWriter());
    // 将 Json::Value 对象转换为字符串
    std::ofstream stream(std::string("test.json"));
    jsonWriter->write(root, &stream);
    stream.close();
    return 0;
}
