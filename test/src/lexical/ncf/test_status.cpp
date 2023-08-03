#include <gtest/gtest.h>

#include <lin/lexical/ncf/status.hpp>
#include <vector>

TEST(test_lin_lexical_ncf_status, status_management)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ncf;

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
