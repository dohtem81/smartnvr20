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
};

class BusClientTestOperations : public ::testing::Test {
protected:
    std::shared_ptr<smartnvr20::lib::FileLocation> fileLocation_OK;
    std::shared_ptr<busclient::BusClient> _busclient;

    void SetUp() override {
        // read config file
        fileLocation_OK = std::make_shared<smartnvr20::lib::FileLocation>("/usr/local/etc/smartnvr20_tests/", "commbus_test_01_OK.json");       
        std::shared_ptr<FrameHandlerConfig> frameHandlerConfig = std::make_shared<FrameHandlerConfig>(fileLocation_OK);
        _busclient = busclient::BusClientFactory(frameHandlerConfig->getHost(), frameHandlerConfig->getPort(), frameHandlerConfig->getPassword());          
    }

    void TearDown() override {
        // Clean up code here
    }
};

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
    std::shared_ptr<busclient::BusClient> _busclient = busclient::BusClientFactory(frameHandlerConfig->getHost(), frameHandlerConfig->getPort(), frameHandlerConfig->getPassword());
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
    std::shared_ptr<busclient::BusClient> _busclient = busclient::BusClientFactory(frameHandlerConfig->getHost(), frameHandlerConfig->getPort(), frameHandlerConfig->getPassword());
    ASSERT_NE(_busclient, nullptr);     
    EXPECT_EQ(_busclient->toString(), "Redis host: smartnvr20-dragonfly-1 port: 6379 AUTH: YES STATUS: AUTH_ERROR\n");
}

TEST_F(BusClientTestOperations, _busClient_StoreAndGetKey) {
    _busclient->StoreInRedis("test_key", std::string("test_value"));
    std::string value;
    _busclient->GetFromRedis("test_key", value);
    EXPECT_EQ(value, "test_value");
}

TEST_F(BusClientTestOperations, _busClient_StoreAndGetExpiredKey) {
    _busclient->StoreInRedis("test_key", std::string("test_value"));
    bool success = _busclient->SetExpiration("test_key", 1);
    EXPECT_EQ(success, true);
    std::string value;
    success = _busclient->GetFromRedis("test_key", value);
    EXPECT_EQ(value, "test_value");
    sleep(2);
    std::string expiredValue;
    success = _busclient->GetFromRedis("test_key", expiredValue);
    //EXPECT_EQ(value, nullptr);
    EXPECT_EQ(success, false);
}

TEST_F(BusClientTestOperations, _busClient_StoreAndGetQueue) {
    _busclient->AddToRedisQueue("test_queu", 1);
    _busclient->AddToRedisQueue("test_queu", 2);
    _busclient->AddToRedisQueue("test_queu", 3);
    _busclient->AddToRedisQueue("test_queu", 4);
    _busclient->AddToRedisQueue("test_queu", 5);
    int queueLength = _busclient->GetQueueLength("test_queu");
    EXPECT_EQ(queueLength, 5);
    int value;
    _busclient->GetFromRedisQueue("test_queu", value);
    EXPECT_EQ(value, 1);
    _busclient->GetFromRedisQueue("test_queu", value);
    EXPECT_EQ(value, 2);
    _busclient->GetFromRedisQueue("test_queu", value);
    EXPECT_EQ(value, 3);
    _busclient->GetFromRedisQueue("test_queu", value);
    EXPECT_EQ(value, 4);
    _busclient->GetFromRedisQueue("test_queu", value);
    EXPECT_EQ(value, 5);
    queueLength = _busclient->GetQueueLength("test_queu");
    EXPECT_EQ(queueLength, 0);
}

TEST_F(BusClientTestOperations, _busClient_StoreAndGetExpiringQueue) {
    _busclient->AddToRedisQueueWithExpiry("test_exq", 1, 4);
    _busclient->AddToRedisQueueWithExpiry("test_exq", 2, 4);
    int queueLength = _busclient->GetExpiringQueueLength("test_exq");
    EXPECT_EQ(queueLength, 2);
    sleep(1);
    queueLength = _busclient->GetExpiringQueueLength("test_exq");
    EXPECT_EQ(queueLength, 2);    
    _busclient->AddToRedisQueueWithExpiry("test_exq", 3, 4);
    _busclient->AddToRedisQueueWithExpiry("test_exq", 4, 4);
    _busclient->AddToRedisQueueWithExpiry("test_exq", 5, 4);
    queueLength = _busclient->GetExpiringQueueLength("test_exq");
    EXPECT_EQ(queueLength, 5);
    sleep(3);
    queueLength = _busclient->GetExpiringQueueLength("test_exq");
    EXPECT_EQ(queueLength, 3);    
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}