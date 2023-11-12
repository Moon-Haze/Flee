#ifndef FLEE_HANDLERCODE_H
#define FLEE_HANDLERCODE_H

#include <cstdint>
#include <string>

namespace Flee {
class HandlerCode {

private:
    std::string message;
    uint8_t     code;

public:
    HandlerCode(std::string message = "", uint8_t code = 0);
};
} // namespace Flee

#endif // FLEE_HANDLERCODE_H