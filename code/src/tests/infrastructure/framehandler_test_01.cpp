#include <gtest/gtest.h>
#include <iostream>
#include "../../infrastructure/framehandler.hpp"
#include "../../infrastructure/framehandlerconfig.hpp"
#include <memory>

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

TEST_F(FrameHandlerTestFixed, _fh_fixed_01) {
    // std::string host = "localhost";
    // std::shared_ptr<FrameHandlerConfig> _fhc = FrameHandlerConfig(host);
    std::shared_ptr<FrameHandler> _fh = FrameHandlerFactory("localhost", 6379, "");
    EXPECT_EQ(_fh, nullptr);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}