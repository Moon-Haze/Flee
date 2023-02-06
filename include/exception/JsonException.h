#ifndef FLEE_JSONEXCEPTION_H
#define FLEE_JSONEXCEPTION_H
#include <exception>
#include <string>
namespace Flee {
class JSONException : public std::exception {
public:
    JSONException(const std::string& message) : message_(message) {}
    virtual const char* what() const throw() { return message_.c_str(); }

private:
    std::string message_;
};
}; // namespace Flee

#endif