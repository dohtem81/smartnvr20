#ifndef IBUSCLIENT_HPP
#define IBUSCLIENT_HPP 

namespace smartnvr20::lib
{
class iBusClient
{
public:
    virtual std::string toString() const = 0;
    
};    
}

#endif // IBUSCLIENT_HPP