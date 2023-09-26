#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <lin/common/parser/comment.hpp>

TEST(test_lin_common_comment_parser, single_line_comment)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common::comment;

    std::string text{ "123 456 // comment 789" };
    std::vector< int > numbers{};

    auto const parser = x3::skip(x3::ascii::space | parser::single_line_comment)[*x3::int_];

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser, x3::ascii::space, numbers);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(numbers.size(), 2);
    EXPECT_EQ(numbers[0], 123);
    EXPECT_EQ(numbers[1], 456);
}

TEST(test_lin_common_comment_parser, block_comment)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common::comment;

    std::string text{ "123 /* comment */ 456" };
    std::vector< int > numbers{};

    auto const parser = x3::skip(x3::ascii::space | parser::block_comment)[*x3::int_];

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser, x3::ascii::space, numbers);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(numbers.size(), 2);
    EXPECT_EQ(numbers[0], 123);
    EXPECT_EQ(numbers[1], 456);
}

TEST(test_lin_common_comment_parser, comment)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common::comment;

    std::string text{
        "123 // line comments 234\n"
        "\n"
        "/* block 345\n"
        "   comments */ 456\n"
        "\n"
        "567\n"
        "\n"
        "/* 678 /* nested\n"
        "   789 block */ comments 890 */\n"
        "\n"
        "901"
    };
    std::vector< int > numbers{};

    auto const parser = x3::skip(parser::comment)[*x3::int_];

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser, x3::ascii::space, numbers);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(numbers.size(), 4);
    EXPECT_EQ(numbers[0], 123);
    EXPECT_EQ(numbers[1], 456);
    EXPECT_EQ(numbers[2], 567);
    EXPECT_EQ(numbers[3], 901);
}
