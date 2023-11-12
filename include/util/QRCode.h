#ifndef FLEE_QRCODE_H
#define FLEE_QRCODE_H

#include "ByteArray.h"
#include <cstdint>

namespace Flee {

class QRCode {
public:
    ByteArray data;
    unsigned  width;
    unsigned  height;

    unsigned encode(const ByteArray& input_data);

    std::string toString() const;
};

} // namespace Flee

#endif /* FLEE_QRCODE_H */