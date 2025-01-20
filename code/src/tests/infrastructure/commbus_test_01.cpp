#include <gtest/gtest.h>
#include <iostream>
#include "../../infrastructure/framhandler.hpp"
#include <string>

using namespace smartnvr20::infrastructure;

class FrameHandlerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Set up code here
    }

    void TearDown() override {
        // Clean up code here
    }
};

TEST_F(FrameHandlerTest, FrameHandlerFactory_OK) {
    std::shared_ptr<FrameHandler> frameHandler_OK = FrameHandlerFactory(
        FrameHandlerConfig(std::make_shared<smartnvr20::lib::FileLocation>(
            "/usr/local/etc/smartnvr20_tests/", 
            "commbus_test_01_OK.json")));

    ASSERT_NE(frameHandler_OK, nullptr);
    EXPECT_EQ(frameHandler_OK->toString(), "expected_string_representation");
}

TEST_F(FrameHandlerTest, FrameHandlerFactory_WrongHost) {
    std::shared_ptr<FrameHandler> frameHandler_wh = FrameHandlerFactory(
        FrameHandlerConfig(std::make_shared<smartnvr20::lib::FileLocation>(
            "/usr/local/etc/smartnvr20_tests/", 
            "commbus_test_01_wrongHost.json")));

    ASSERT_EQ(frameHandler_wh, nullptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}