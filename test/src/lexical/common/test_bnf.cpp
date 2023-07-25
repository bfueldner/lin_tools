#include <gtest/gtest.h>

#include <lin/lexical/common/bnf.hpp>

TEST(test_lin_lexical_common_bnf, char_string)
{
    using namespace lin::lexical::common::bnf;
    namespace x3 = boost::spirit::x3;

    std::string text{ "\"Char String\"" };
    char_string_t char_string;

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::char_string, x3::ascii::space, char_string);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(char_string.c_str(), "Char String");
}

TEST(test_lin_lexical_common_bnf, identifier)
{
    using namespace lin::lexical::common::bnf;
    namespace x3 = boost::spirit::x3;

    std::string text{ "abc_XYZ_123" };
    identifier_t identifier;

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::identifier, x3::ascii::space, identifier);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(identifier.c_str(), "abc_XYZ_123");
}

TEST(test_lin_lexical_common_bnf, integer)
{
    using namespace lin::lexical::common::bnf;
    namespace x3 = boost::spirit::x3;

    std::string text{ "0x1234" };
    integer_t integer{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::integer, x3::ascii::space, integer);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(integer, 0x1234);
}

TEST(test_lin_lexical_common_bnf, real_or_integer)
{
    using namespace lin::lexical::common::bnf;
    namespace x3 = boost::spirit::x3;

    std::string text{ "19.2" };
    real_or_integer_t real_or_integer{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::real_or_integer, x3::ascii::space, real_or_integer);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(real_or_integer, 19.2);
}
