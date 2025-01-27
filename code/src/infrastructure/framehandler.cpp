#include "framehandler.hpp"

namespace smartnvr20::infrastructure {
    // Define the static member variable
    bool FrameHandler::initialized = false;
    std::shared_ptr<busclient::BusClient> FrameHandler::busClient = nullptr;

    // ------------------------------------------------------------------
    std::string FrameHandler::toString() const
    {
        std::string outStr = "";

        // if (rContext == nullptr)
        // {
        //     outStr = "Redis conection not initialized\n";
        // }
        // else
        // {
        //     // print redis host and port asigned to rContext
        //     outStr = "Redis connection initialized with host: " + std::string(rContext->tcp.host) 
        //         + " and port: " + std::to_string(rContext->tcp.port) + "\n";
        // }

        return outStr;
    }


    // ------------------------------------------------------------------
    std::shared_ptr<FrameHandler> FrameHandlerFactory(FrameHandlerConfig _fhc)
    {
        // ensure only one instace is created
        if (FrameHandler::initialized)
        {
            return FrameHandler::_selfPtr;
        }
        
        std::shared_ptr<FrameHandler> frameHandlerPtr = 
            std::shared_ptr<FrameHandler>(new FrameHandler(_fhc));
        
        return frameHandlerPtr;
    }


    // ------------------------------------------------------------------
    std::shared_ptr<FrameHandler> FrameHandlerFactory(std::string _host, int _port = 6379, std::string _dbPasswd = "")
    {
        // ensure only one instace is created
        if (FrameHandler::initialized)
        {
            return FrameHandler::_selfPtr;
        }
        
        std::shared_ptr<FrameHandler> frameHandlerPtr = 
            std::shared_ptr<FrameHandler>(new FrameHandler(FrameHandlerConfig(_host, _port, _dbPasswd)));
        
        return frameHandlerPtr;
    }


    // ------------------------------------------------------------------
    FrameHandler::FrameHandler(FrameHandlerConfig _fhc)
    {
        busClient = busclient::BusClientFactory(_fhc.getHost(), _fhc.getPort(), _fhc.getPassword());
        FrameHandler::initialized = true;
    }

} // namespace commbus::domain