#ifndef FLEE_PACKETLV_H
#define FLEE_PACKETLV_H

#include "ByteArray.h"
#include "QQConfig.h"

#include <map>

namespace Flee {

template <typename T = uint16_t>
class DataPacket {
    /* data */
    ByteArray data;
    T         offset;

public:
    DataPacket(const ByteArray& data, T offset = 0);

    DataPacket(const std::string& data, T offset = 0);

    template <typename Z>
    DataPacket(Z data, T offset = 0)
        : data(std::move(toByteArray<Z>(data))), offset(offset) {}

    T                getOffset() const;
    const ByteArray& getData() const;
};

template <typename T>
ByteArray& operator<<(ByteArray& array, const DataPacket<T>& packet);

class PackTlv {
    const QQInfo& info;

public:
    explicit PackTlv(const QQInfo& info);
    ByteArray t01() const;
    ByteArray t08() const;
    ByteArray t16() const;
    ByteArray t18() const;
    ByteArray t1B() const;
    ByteArray t1D() const;
    ByteArray t1F() const;
    ByteArray t33() const;
    ByteArray t35() const;
    ByteArray t100(uint8_t emp = 0) const;
    ByteArray t104() const;
    ByteArray t106() const;
    ByteArray t107() const;
    ByteArray t109() const;
    ByteArray t10a() const;
    ByteArray t116() const;
    ByteArray t124() const;
    ByteArray t128() const;
    ByteArray t141() const;
    ByteArray t142() const;
    ByteArray t143() const;
    ByteArray t144() const;
    ByteArray t145() const;
    ByteArray t147() const;
    ByteArray t154() const;
    ByteArray t16e() const;
    ByteArray t174() const;
    ByteArray t177() const;
    ByteArray t17a() const;
    ByteArray t17c(const ByteArray& code) const;
    ByteArray t187() const;
    ByteArray t188() const;
    ByteArray t191() const;
    ByteArray t193(const ByteArray& ticket) const;
    ByteArray t194() const;
    ByteArray t197() const;
    ByteArray t198() const;
    ByteArray t202() const;
    ByteArray t400() const;
    ByteArray t401() const;
    ByteArray t511() const;
    ByteArray t516() const;
    ByteArray t521() const;
    ByteArray t525() const;
    ByteArray t52d() const;
};
};     // namespace Flee
#endif // FLEE_PACKETLV_H