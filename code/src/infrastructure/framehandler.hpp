#include <memory>
#include <hiredis/hiredis.h>
#include <string>
#include "../lib/iToString.hpp"
#include <iostream>
#include "framehandlerconfig.hpp"
#include "RedisClient/busclient.hpp"
#include <grpcpp/grpcpp.h>
#include "heartbeat.grpc.pb.h"

namespace smartnvr20::infrastructure {
    class FrameHandler : public smartnvr20::lib::iToString, FrameHandlerService::Service
    {
    public:
        friend std::shared_ptr<FrameHandler> FrameHandlerFactory(FrameHandlerConfig);
        friend std::shared_ptr<FrameHandler> FrameHandlerFactory(std::string host, int _port, std::string);
        std::string toString() const;
        grpc::Status SendHeartbeat(
            grpc::ServerContext* context, 
            const HeartbeatRequest* request,
            HeartbeatResponse* response) override;

    private:
        FrameHandler(FrameHandlerConfig);
        static bool initialized;
        static std::shared_ptr<FrameHandler> _selfPtr;
        static std::shared_ptr<busclient::BusClient> busClient;
        std::unique_ptr<grpc::Server> grpcServer;
        void StartGrpcServer(const std::string& address);         
    };

    std::shared_ptr<FrameHandler> FrameHandlerFactory(FrameHandlerConfig);
    std::shared_ptr<FrameHandler> FrameHandlerFactory(std::string host, int _port, std::string);
} // namespace commbus.domain