#ifndef FLEE_HANDER_H
#include "QQPackTlv.h"

namespace Flee {

class handler {
protected:
    QQPackTlv& packet;

public:
    handler(QQPackTlv& packet) : packet(packet) {}
};
} // namespace Flee
#endif // FLEE_HANDER_H