
#include "ParsingException.h"

std::string getMessage(const std::string&                  mgs,
                       Flee::ParsingException::ParsingType exception_type) {
    std::string _message_;
    switch(exception_type) {
    case Flee::ParsingException::JsonError:
        _message_ = "Error in parsing Json.\n" + mgs;
        break;
    case Flee::ParsingException::PacketError:
        _message_ = "Error in parsing packet from network.\n" + mgs;
        break;
    case Flee::ParsingException::FlagError:
        _message_ = "unknown flag:\n" + mgs;
        break;
    }

    return _message_;
}
namespace Flee {

ParsingException::ParsingException(const std::string& message, ParsingType type)
    : runtime_error(getMessage(message, type)) {}
}; // namespace Flee