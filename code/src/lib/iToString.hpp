#ifndef ITOSTRING_HPP
#define ITOSTRING_HPP

#include <string>

namespace smartnvr20::lib {

class iToString {
public:
    virtual std::string toString() const = 0;
};

} // namespace smartnvr20::lib

#endif // ITOSTRING_HPP