#include <sstream>

#include <gtest/gtest.h>

#include <lin/ncf/status.hpp>

#include <lin/ncf/generator/status.hpp>

/* 8.2.6 Status management */

TEST(test_lin_ncf_status_generator, status_management)
{
    using namespace lin::ncf;

    status_t const status{ "error_bit", { "fault_state" } };

    std::stringstream stream{};
    stream << status;
    EXPECT_EQ(
        stream.str(),
        "status_management {\n"
        "    response_error = error_bit;\n"
        "    fault_state_signals = fault_state;\n"
        "}\n");
}
