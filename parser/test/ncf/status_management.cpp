#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <lin/ncf/parser/status_management.hpp>
#include <lin/ncf/status_management.hpp>

TEST(test_lin_ncf_status_management_parser, status_management)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string const text{
        "status_management { response_error = error_bit;"
        "                    fault_state_signals = fault_state; }"
    };
    status_management_t status_management{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::status_management, x3::ascii::space, status_management);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(status_management.response_error.c_str(), "error_bit");
    EXPECT_EQ(status_management.fault_state_signals, std::vector< std::string >{ "fault_state" });
}
