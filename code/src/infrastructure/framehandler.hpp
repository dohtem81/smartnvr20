#include <memory>
#include <hiredis/hiredis.h>
#include <string>
#include "../lib/iToString.hpp"
#include <iostream>
#include "framehandlerconfig.hpp"
#include "RedisClient/busclient.hpp"

namespace smartnvr20::infrastructure {
    class FrameHandler : smartnvr20::lib::iToString
    {
    public:
        friend std::shared_ptr<FrameHandler> FrameHandlerFactory(FrameHandlerConfig);
        friend std::shared_ptr<FrameHandler> FrameHandlerFactory(std::string host, int _port, std::string);
        std::string toString() const;

    private:
        FrameHandler(FrameHandlerConfig);
        static bool initialized;
        static std::shared_ptr<FrameHandler> _selfPtr;
        static std::shared_ptr<busclient::BusClient> busClient;
    };

    std::shared_ptr<FrameHandler> FrameHandlerFactory(FrameHandlerConfig);
    std::shared_ptr<FrameHandler> FrameHandlerFactory(std::string host, int _port, std::string);
} // namespace commbus.domain