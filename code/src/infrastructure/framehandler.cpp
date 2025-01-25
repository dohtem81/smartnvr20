#include "framehandler.hpp"

namespace smartnvr20::infrastructure {
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

    std::shared_ptr<FrameHandler> FrameHandlerFactory(FrameHandlerConfig _fhc)
    {
        // ensure only one instace is created
        if (FrameHandler::initialized)
        {
            return nullptr;
        }
        
        std::shared_ptr<FrameHandler> frameHandlerPtr = 
            std::shared_ptr<FrameHandler>(new FrameHandler(_fhc));
        
        return frameHandlerPtr;
    }

    FrameHandler::FrameHandler(FrameHandlerConfig _fhc)
    {
        rContext = GetRedisContext(_fhc);
        FrameHandler::initialized = true;
    }

    std::shared_ptr<redisContext> FrameHandler::GetRedisContext(FrameHandlerConfig _fhc)
    {
        redisContext* rawContext = redisConnect(_fhc.getHost().c_str() , _fhc.getPort());
        if (rawContext == nullptr || rawContext->err)
        {
            redisReply* reply = (redisReply*)redisCommand(rawContext, "AUTH %s", _fhc.getPassword().c_str());
            if (reply == nullptr || reply->type == REDIS_REPLY_ERROR)
            {
                std::cerr << "Failed to authenticate to redis server" << std::endl;
                if(reply != nullptr)
                {
                    redisFree(rawContext);
                }
            } else {
                // Handle connection error
                if (rawContext) redisFree(rawContext);
                throw std::runtime_error("Connection failed to Redis server");
            }
            return nullptr;
        }
        std::shared_ptr<redisContext> context(rawContext, redisFree);
        return context;
    }
} // namespace commbus::domain