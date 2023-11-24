#include <string>

#include <gtest/gtest.h>

#include <lin/common/bnf.hpp>
#include <lin/common/parser/bnf.hpp>

TEST(test_lin_common_bnf_parser, char_string)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common;

    std::string text{ "\"Char String\"" };
    bnf::char_string_t char_string;

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::char_string, x3::ascii::space, char_string);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(char_string.c_str(), "Char String");
}

TEST(test_lin_common_bnf_parser, identifier)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common;

    std::string text{ "abc_XYZ_123" };
    bnf::identifier_t identifier;

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::identifier, x3::ascii::space, identifier);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(identifier.c_str(), "abc_XYZ_123");
}

TEST(test_lin_common_bnf_parser, integer_decimal)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common;

    std::string text{ "1234" };
    bnf::integer_t integer{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::integer, x3::ascii::space, integer);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(integer, 1234);
}

TEST(test_lin_common_bnf_parser, integer_hexadecimal)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common;

    std::string text{ "0x1234" };
    bnf::integer_t integer{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::integer, x3::ascii::space, integer);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(integer, 0x1234);
}

TEST(test_lin_common_bnf_parser, real_or_integer)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common;

    std::string text{ "19.2" };
    bnf::real_or_integer_t real_or_integer{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::real_or_integer, x3::ascii::space, real_or_integer);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(real_or_integer, 19.2);
}
