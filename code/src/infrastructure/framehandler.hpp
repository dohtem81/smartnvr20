#include <memory>
#include <hiredis/hiredis.h>
#include <string>
#include "../lib/iToString.hpp"
#include <iostream>
#include "framehandlerconfig.hpp"

namespace smartnvr20::infrastructure {
    class FrameHandler : smartnvr20::lib::iToString
    {
    public:
        friend std::shared_ptr<FrameHandler> FrameHandlerFactory(FrameHandlerConfig);
        std::string toString() const;

    private:
        FrameHandler(FrameHandlerConfig);
        static bool initialized;
        std::shared_ptr<redisContext> rContext;

        std::shared_ptr<redisContext> GetRedisContext(FrameHandlerConfig);
    };

    std::shared_ptr<FrameHandler> FrameHandlerFactory(FrameHandlerConfig);
} // namespace commbus.domain