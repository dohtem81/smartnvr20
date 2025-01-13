#include <memory>
#include <hiredis/hiredis.h>
#include <string>
#include "../../lib/iToString.hpp"
#include <iostream>

namespace smartnvr20::commbus::domain {
    class FrameHandler : smartnvr20::lib::iToString
    {
    public:
        friend std::shared_ptr<FrameHandler> FrameHandlerFactory();
        std::string toString() const;

    private:
        FrameHandler(const std::string&, int);
        static bool initialized;
        std::shared_ptr<redisContext> rContext;

        std::shared_ptr<redisContext> GetRedisContext(const std::string& _host, int _port);
    };

    std::shared_ptr<FrameHandler> FrameHandlerFactory();
} // namespace commbus.domain