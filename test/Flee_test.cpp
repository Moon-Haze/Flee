#include "ByteArray.h"
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <json/json.h>
#include <ratio>
#include <spdlog/spdlog.h>
#include <string>
#include <thread>
#include <utility>

// using namespace Flee;

int main(int argc, char** argv) {
    // auto device = Device::getDevice("./device.json");
    // std::cout << device << std::endl;
    using namespace Flee;
    ByteArray bytes, array;
    bytes << 0xff << 0xff << 0xff << 0xaa00 << 0xbb << 0xab;
    std::cout << bytes << std::endl;
    std::cout << array << std::endl;

    std::copy(bytes.data() + 2, bytes.data() + 5, std::back_inserter(array));
    bytes.erase(bytes.begin() + 2, bytes.begin() + 5);
    std::cout << bytes.size() << std::endl;
    std::cout << bytes << std::endl;
    std::cout << array << std::endl;
    return 0;
}
