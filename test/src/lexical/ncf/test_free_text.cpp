#include <gtest/gtest.h>

#include <lin/lexical/ncf/free_text.hpp>


TEST(test_lin_lexical_ncf_free_text, free_text)
{
    using namespace lin::lexical::ncf;
    namespace x3 = boost::spirit::x3;

    std::string text{
        "free_text {"
        "    \"step_motor signal values outside 0 - 199 are ignored\""
        "}"
    };
    free_text_t free_text{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::free_text_definition, x3::ascii::space, free_text);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_STREQ(free_text.c_str(), "step_motor signal values outside 0 - 199 are ignored");
}
