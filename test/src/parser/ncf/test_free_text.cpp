#include <string>

#include <gtest/gtest.h>

#include <lin/ncf/free_text.hpp>

#include <lin/ncf/parser/free_text.hpp>

/* 8.2.7 Free text definition */

TEST(test_lin_ncf_free_text_parser, free_text_definition)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string text{
        "free_text {"
        "    \"step_motor signal values outside 0 - 199 are ignored\""
        "}"
    };
    free_text_t free_text{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::free_text_definition, x3::ascii::space, free_text);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(free_text.c_str(), "step_motor signal values outside 0 - 199 are ignored");
}
