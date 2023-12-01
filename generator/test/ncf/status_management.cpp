#include <sstream>

#include <gtest/gtest.h>

#include <lin/ncf/generator/status_management.hpp>
#include <lin/ncf/status_management.hpp>

/* 8.2.6 Status management */

TEST(test_lin_ncf_status_management_generator, status_management)
{
    using namespace lin::ncf;

    status_management_t const status_management{ "error_bit", { "fault_state" } };

    std::stringstream stream{};
    stream << status_management;
    EXPECT_EQ(
        stream.str(),
        "status_management {\n"
        "    response_error = error_bit;\n"
        "    fault_state_signals = fault_state;\n"
        "}\n");
}
