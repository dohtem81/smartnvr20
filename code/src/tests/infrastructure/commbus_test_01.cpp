#include <gtest/gtest.h>
#include <iostream>
#include "../../infrastructure/framehandler.hpp"
#include "../../infrastructure/RedisClient/busclient.hpp"
#include "../../infrastructure/framehandlerconfig.hpp"
#include <string>

using namespace smartnvr20::infrastructure;

class BusClientTestFixed : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up code here
    }

    void TearDown() override {
        // Clean up code here
    }
};

class BusClientTestConfigFile : public ::testing::Test {
protected:
    std::shared_ptr<smartnvr20::lib::FileLocation> fileLocation_OK;
    std::shared_ptr<smartnvr20::lib::FileLocation> fileLocation_WrongPassword;
    std::shared_ptr<smartnvr20::lib::FileLocation> fileLocation_WrongPort;
    std::shared_ptr<smartnvr20::lib::FileLocation> fileLocation_NoPasswd;

    void SetUp() override {
        // read config file
        fileLocation_OK = std::make_shared<smartnvr20::lib::FileLocation>("/usr/local/etc/smartnvr20_tests/", "commbus_test_01_OK.json");
        fileLocation_WrongPassword = std::make_shared<smartnvr20::lib::FileLocation>("/usr/local/etc/smartnvr20_tests/", "commbus_test_01_wrongPswd.json");
        fileLocation_WrongPort = std::make_shared<smartnvr20::lib::FileLocation>("/usr/local/etc/smartnvr20_tests/", "commbus_test_01_wrongPort.json");
        fileLocation_NoPasswd = std::make_shared<smartnvr20::lib::FileLocation>("/usr/local/etc/smartnvr20_tests/", "commbus_test_01_noPswd.json");            
    }

    void TearDown() override {
        // Clean up code here
    }
};;

TEST_F(BusClientTestFixed, _busClient01) {
    std::shared_ptr<busclient::BusClient> _busclient = busclient::BusClientFactory("localhost");
    EXPECT_EQ(_busclient, nullptr);
}

TEST_F(BusClientTestFixed, _busClient02) {
    std::shared_ptr<busclient::BusClient> _busclient = busclient::BusClientFactory("smartnvr20-dragonfly-1", 6379, "aabc");
    ASSERT_NE(_busclient, nullptr);     
    EXPECT_EQ(_busclient->toString(), "Redis host: smartnvr20-dragonfly-1 port: 6379 AUTH: YES STATUS: AUTH_ERROR\n");
}

TEST_F(BusClientTestFixed, _busClient03) {
    std::shared_ptr<busclient::BusClient> _busclient = busclient::BusClientFactory("smartnvr20-dragonfly-1", 6379, "DFlyPswd2025!");
    ASSERT_NE(_busclient, nullptr);     
    EXPECT_EQ(_busclient->toString(), "Redis host: smartnvr20-dragonfly-1 port: 6379 AUTH: YES STATUS: OK\n");
}

TEST_F(BusClientTestConfigFile, _busClient_SettOK) {
    std::shared_ptr<FrameHandlerConfig> frameHandlerConfig = std::make_shared<FrameHandlerConfig>(fileLocation_OK);
    std::shared_ptr<busclient::BusClient> _busclient = busclient::BusClientFactory(frameHandlerConfig->getHost(), frameHandlerConfig->getPort());
    ASSERT_NE(_busclient, nullptr);     
    EXPECT_EQ(_busclient->toString(), "Redis host: smartnvr20-dragonfly-1 port: 6379 AUTH: YES STATUS: OK\n");
}

TEST_F(BusClientTestConfigFile, _busClient_WrongPassword) {
    std::shared_ptr<FrameHandlerConfig> frameHandlerConfig = std::make_shared<FrameHandlerConfig>(fileLocation_WrongPassword);
    std::shared_ptr<busclient::BusClient> _busclient = busclient::BusClientFactory(frameHandlerConfig->getHost(), frameHandlerConfig->getPort(), frameHandlerConfig->getPassword());
    ASSERT_NE(_busclient, nullptr);     
    EXPECT_EQ(_busclient->toString(), "Redis host: smartnvr20-dragonfly-1 port: 6379 AUTH: YES STATUS: AUTH_ERROR\n");
}

TEST_F(BusClientTestConfigFile, _busClient_WrongPort) {
    std::shared_ptr<FrameHandlerConfig> frameHandlerConfig = std::make_shared<FrameHandlerConfig>(fileLocation_WrongPort);
    std::shared_ptr<busclient::BusClient> _busclient = busclient::BusClientFactory(frameHandlerConfig->getHost(), frameHandlerConfig->getPort(), frameHandlerConfig->getPassword());
    EXPECT_EQ(_busclient, nullptr);
}

TEST_F(BusClientTestConfigFile, _busClient_NoPassword) {
    std::shared_ptr<FrameHandlerConfig> frameHandlerConfig = std::make_shared<FrameHandlerConfig>(fileLocation_NoPasswd);
    std::shared_ptr<busclient::BusClient> _busclient = busclient::BusClientFactory(frameHandlerConfig->getHost(), frameHandlerConfig->getPort());
    ASSERT_NE(_busclient, nullptr);     
    EXPECT_EQ(_busclient->toString(), "Redis host: smartnvr20-dragonfly-1 port: 6379 AUTH: NO STATUS: AUTH_ERROR\n");
}



int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}