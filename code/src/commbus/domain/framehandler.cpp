#include "framhandler.hpp"

namespace smartnvr20::commbus::domain {
    // Define the static member variable
    bool FrameHandler::initialized = false;

    std::string FrameHandler::toString() const
    {
        std::string outStr = "";

        if (rContext == nullptr)
        {
            outStr = "Redis conection not initialized\n";
        }
        else
        {
            // print redis host and port asigned to rContext
            outStr = "Redis connection initialized with host: " + std::string(rContext->tcp.host) 
                + " and port: " + std::to_string(rContext->tcp.port) + "\n";
        }

        return outStr;
    }

    std::shared_ptr<FrameHandler> FrameHandlerFactory()
    {
        // ensure only one instace is created
        if (FrameHandler::initialized)
        {
            return nullptr;
        }

        std::string host = "smartnvr20-dragonfly-1";
        std::shared_ptr<FrameHandler> frameHandlerPtr = 
            std::shared_ptr<FrameHandler>(new FrameHandler(host, 6379));
        
        return frameHandlerPtr;
    }

    FrameHandler::FrameHandler(const std::string& _host, int _port)
    {
        rContext = GetRedisContext(_host, _port);
        FrameHandler::initialized = true;
    }

    std::shared_ptr<redisContext> FrameHandler::GetRedisContext(const std::string& _host, int _port)
    {
        redisContext* rawContext = redisConnect(_host.c_str(), _port);
        if (rawContext == nullptr || rawContext->err)
        {
            if (rawContext->err)
            {
                std::cerr << "Connection error (" << _host << ":" << std::to_string(_port) << "): " 
                    << rawContext->errstr << " .. ";
            }
            else
            {
                std::cerr << "Connection error (" << _host << ":" << std::to_string(_port) << "): " 
                    << "can't allocate redis context" << " .. ";
            }

            if (rawContext) {
                redisFree(rawContext);
            }
            return nullptr;
        }
        std::shared_ptr<redisContext> context(rawContext, redisFree);
        return context;
    }
} // namespace commbus::domain