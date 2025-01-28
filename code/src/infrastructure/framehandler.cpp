#include "framehandler.hpp"

namespace smartnvr20::infrastructure {
    // Define the static member variable
    bool FrameHandler::initialized = false;
    std::shared_ptr<busclient::BusClient> FrameHandler::busClient = nullptr;
    std::shared_ptr<FrameHandler> FrameHandler::_selfPtr = nullptr;

    // ------------------------------------------------------------------
    std::string FrameHandler::toString() const
    {
        std::string outStr = "";

        outStr = "busClient: " + busClient->toString() + "\n";

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
        FrameHandler::_selfPtr = frameHandlerPtr;
        
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
        FrameHandler::_selfPtr = frameHandlerPtr;
        
        return frameHandlerPtr;
    }


    // ------------------------------------------------------------------
    FrameHandler::FrameHandler(FrameHandlerConfig _fhc)
    {
        busClient = busclient::BusClientFactory(_fhc.getHost(), _fhc.getPort(), _fhc.getPassword());
        FrameHandler::initialized = true;
    }


    // ------------------------------------------------------------------


} // namespace commbus::domain