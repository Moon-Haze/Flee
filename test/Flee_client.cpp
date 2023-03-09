/*
 * @Author: Moon-Haze swx1126200515@outlook.com
 * @Date: 2023-02-10 15:09
 * @LastEditors: Moon-Haze swx1126200515@outlook.com
 * @LastEditTime: 2023-03-04 21:22
 * @FilePath: \Flee\test\Flee_client.cpp
 * @Description:
 */
#include "QBaseClient.h"
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/uuid_generators.hpp>
#include <boost/uuid/uuid_io.hpp>
#include <iostream>
#include <ostream>
#include <string>

int main(int argc, char** argv) {
    using namespace Flee;
    QBaseClient client(2163973016);
    client.login();
    return 0;
}