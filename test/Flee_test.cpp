#include "ByteArray.h"
#include "Device.h"
#include "constants.h"
#include <algorithm>
#include <cctype>
#include <cstdint>
#include <fstream>
#include <iostream>
#include <json/json.h>
#include <spdlog/spdlog.h>
#include <string>
#include <vector>

using namespace Flee;

int main(int argc, char** argv) {
    // auto device = Device::getDevice("./device.json");
    // std::cout << device << std::endl;
    /**
1675520108195
1675519319669
1675520108
    */
    std::cout << currentTimeMillis() << std::endl;
    std::cout << currentTimeSeconds() << std::endl;
    return 0;
}
