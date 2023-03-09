#ifndef FLEE_LOGINHANDER_H
#define FLEE_LOGINHANDER_H
#include "ByteArray.h"
#include <fstream>
#include <string>

namespace Flee {

class LogInHander {

public:
    void parseQtcode(ByteArray& buffer, const std::string& filename);

    void qrcode(const std::string& filename, const ByteArray& data);
};
} // namespace Flee

#endif // FLEE_LOGINHANDER_H