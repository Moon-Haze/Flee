
#include "NetworkException.h"

std::string getMessage(const std::string&                           mgs,
                       Flee::NetworkException::NetworkExceptionType exception_type) {
    std::string _message_;
    switch(exception_type) {
    case Flee::NetworkException::ResolveError:
        _message_ = "Error in querying network address.\n" + mgs;
    case Flee::NetworkException::ConnectionError:
        _message_ = "Connection network address error.\n" + mgs;
    case Flee::NetworkException::WriteError:
        _message_ = "Network sending data error.\n" + mgs;
    case Flee::NetworkException::ReadError:
        _message_ = "Network receiving data error.\n" + mgs;
    case Flee::NetworkException::CloseError:
        _message_ = "Disconnection error.\n" + mgs;
    case Flee::NetworkException::UnknownError:
        _message_ = "Unknown network error.\n" + mgs;
    }
    return _message_;
}

namespace Flee {

NetworkException::NetworkException(const std::string&   message,
                                   NetworkExceptionType type)
    : runtime_error(getMessage(message, type)) {}
}; // namespace Flee