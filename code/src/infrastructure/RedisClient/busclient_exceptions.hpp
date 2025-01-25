#ifndef BUSCLIENT_EXCEPTIONS_HPP
#define BUSCLIENT_EXCEPTIONS_HPP

#include <exception>
#include <string>

namespace smartnvr20::infrastructure::busclient {

class BusClientException : public std::exception {
public:
    explicit BusClientException(const std::string& message) : msg_(message) {}
    virtual const char* what() const noexcept override {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

class BusClientAuthException : public std::exception {
public:
    explicit BusClientAuthException(const std::string& message) : msg_(message) {}
    virtual const char* what() const noexcept override {
        return msg_.c_str();
    }
private:
    std::string msg_;
};

} // namespace smartnvr20::infrastructure::busclient

#endif // BUSCLIENT_EXCEPTIONS_HPP