#include <gtest/gtest.h>
#include <iostream>
#include "../../infrastructure/framehandler.hpp"
#include "../../infrastructure/framehandlerconfig.hpp"
#include <memory>
#include "heartbeat.grpc.pb.h" 

using namespace smartnvr20::infrastructure;

class FrameHandlerTestFixed : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up code here
    }

    void TearDown() override {
        // Clean up code here
    }
};

class FrameHandlerTestCfgFile : public ::testing::Test {
protected:
    FrameHandlerConfig frameHandlerConfig = FrameHandlerConfig();
    void SetUp() override {
        std::shared_ptr<smartnvr20::lib::FileLocation> fileLocation = 
            std::make_shared<smartnvr20::lib::FileLocation>("/usr/local/etc/smartnvr20_tests/", "commbus_test_01_OK.json");       
        frameHandlerConfig = std::move(FrameHandlerConfig(fileLocation));
    }

    void TearDown() override {
        // Clean up code here
    }
};

class FrameHandlerTestgRPC : public ::testing::Test {
protected:
    std::shared_ptr<FrameHandler> frameHandler;
    std::unique_ptr<smartnvr20::FrameHandlerService::Stub> stub;
    
    void SetUp() override {
        frameHandler = FrameHandlerFactory("localhost", 6379, "");
        auto channel = grpc::CreateChannel("localhost:50051", grpc::InsecureChannelCredentials());
        stub = smartnvr20::FrameHandlerService::NewStub(channel);
    }

    void TearDown() override {
        frameHandler.reset();
        stub.reset();
    }
};

TEST_F(FrameHandlerTestFixed, _fh_fixed_01) {
    std::shared_ptr<FrameHandler> _fh = FrameHandlerFactory("localhost", 6379, "");
    ASSERT_NE(_fh, nullptr);
    std::shared_ptr<FrameHandler> _fh2 = FrameHandlerFactory("localhost", 6379, "");
    ASSERT_EQ(_fh, _fh2);
}

TEST_F(FrameHandlerTestCfgFile, _fh_cfgf_01) {
    std::shared_ptr<FrameHandler> _fh = FrameHandlerFactory(frameHandlerConfig);
    // ASSERT_NE(_fh, nullptr);
    ASSERT_EQ(_fh->toString(), "busClient: Redis host: smartnvr20-dragonfly-1 port: 6379 AUTH: YES STATUS: OK\n");
}

TEST_F(FrameHandlerTestgRPC, SendHeartbeat_Success) {
    smartnvr20::HeartbeatRequest request;
    request.set_client_id("test_client");
    request.set_timestamp(std::time(nullptr));

    smartnvr20::HeartbeatResponse response;
    grpc::ClientContext context;

    grpc::Status status = stub->SendHeartbeat(&context, request, &response);

    ASSERT_TRUE(status.ok());
    ASSERT_TRUE(response.success());
    ASSERT_EQ(response.message(), "Heartbeat received from test_client");
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}