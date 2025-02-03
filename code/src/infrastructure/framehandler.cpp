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
        
        FrameHandler::initialized = true;
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
        StartGrpcServer("0.0.0.0:50051");
        FrameHandler::initialized = true;
    }


    // ------------------------------------------------------------------
    void FrameHandler::StartGrpcServer(const std::string& address) {
        grpc::ServerBuilder builder;
        builder.AddListeningPort(address, grpc::InsecureServerCredentials());
        builder.RegisterService(this);
        grpcServer = builder.BuildAndStart();
    }


    // ------------------------------------------------------------------
    grpc::Status FrameHandler::SendHeartbeat(
        grpc::ServerContext* context,
        const HeartbeatRequest* request,
        HeartbeatResponse* response) {
        
        response->set_success(true);
        response->set_message("Heartbeat received from " + request->client_id());
        return grpc::Status::OK;
    }    

} // namespace commbus::domain