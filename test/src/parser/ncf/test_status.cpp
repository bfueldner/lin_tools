#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <lin/ncf/status.hpp>

#include <lin/ncf/parser/status.hpp>

TEST(test_lin_ncf_status_parser, status_management)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string text{
        "status_management { response_error = error_bit;"
        "                    fault_state_signals = fault_state; }"
    };
    status_t status{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::status_management, x3::ascii::space, status);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(status.response_error.c_str(), "error_bit");
    EXPECT_EQ(status.fault_state_signals, std::vector< std::string >{ "fault_state" });
}
