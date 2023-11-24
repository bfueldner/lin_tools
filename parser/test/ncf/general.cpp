#include <string>
#include <variant>

#include <gtest/gtest.h>

#include <lin/ncf/general.hpp>
#include <lin/ncf/parser/general.hpp>

TEST(test_lin_ncf_general_parser, bitrate_automatic_default)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string const text{ "automatic" };
    general::bitrate::automatic_t bitrate_automatic{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::general_bitrate_automatic,
        x3::ascii::space,
        bitrate_automatic);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_FALSE(bitrate_automatic.min);
    EXPECT_FALSE(bitrate_automatic.max);
}

TEST(test_lin_ncf_general_parser, bitrate_automatic_min)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string const text{ "automatic min 9.6 kbps" };
    general::bitrate::automatic_t bitrate_automatic{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::general_bitrate_automatic,
        x3::ascii::space,
        bitrate_automatic);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_TRUE(bitrate_automatic.min);
    if (bitrate_automatic.min)
    {
        EXPECT_EQ(bitrate_automatic.min.value(), 9.6);
    }
    EXPECT_FALSE(bitrate_automatic.max);
}

TEST(test_lin_ncf_general_parser, bitrate_automatic_max)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string const text{ "automatic max 19.2 kbps" };
    general::bitrate::automatic_t bitrate_automatic{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::general_bitrate_automatic,
        x3::ascii::space,
        bitrate_automatic);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_FALSE(bitrate_automatic.min);
    ASSERT_TRUE(bitrate_automatic.max);
    if (bitrate_automatic.max)
    {
        EXPECT_EQ(bitrate_automatic.max.value(), 19.2);
    }
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_ncf_general_parser, bitrate_automatic_min_max)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string const text{ "automatic min 9.6 kbps max 19.2 kbps" };
    general::bitrate::automatic_t bitrate_automatic{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::general_bitrate_automatic,
        x3::ascii::space,
        bitrate_automatic);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_TRUE(bitrate_automatic.min);
    if (bitrate_automatic.min)
    {
        EXPECT_EQ(bitrate_automatic.min.value(), 9.6);
    }
    ASSERT_TRUE(bitrate_automatic.max);
    if (bitrate_automatic.max)
    {
        EXPECT_EQ(bitrate_automatic.max.value(), 19.2);
    }
}
// NOLINTEND(readability-function-cognitive-complexity)

TEST(test_lin_ncf_general_parser, bitrate_select_single)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string const text{ "select { 19.2 kbps }" };
    general::bitrate::select_t bitrate_select{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::general_bitrate_select, x3::ascii::space, bitrate_select);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_FALSE(bitrate_select.empty());
    EXPECT_EQ(*bitrate_select.data(), 19.2);
}

TEST(test_lin_ncf_general_parser, bitrate_select_multiple)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string const text{ "select { 4.8 kbps, 9.6kbps, 19.2 kbps }" };
    general::bitrate::select_t bitrate_select{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::general_bitrate_select, x3::ascii::space, bitrate_select);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(bitrate_select.size(), 3);
    EXPECT_EQ(bitrate_select[0], 4.8);
    EXPECT_EQ(bitrate_select[1], 9.6);
    EXPECT_EQ(bitrate_select[2], 19.2);
}

TEST(test_lin_ncf_general_parser, bitrate_fixed)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string const text{ "19.2 kbps" };
    general::bitrate::fixed_t bitrate_fixed{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::general_bitrate_fixed, x3::ascii::space, bitrate_fixed);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(bitrate_fixed, 19.2);
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_ncf_general_parser, bitrate)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string const text{ "automatic min 9.6 kbps max 19.2 kbps" };
    general::bitrate_t bitrate{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::general_bitrate, x3::ascii::space, bitrate);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *automatic = std::get_if< general::bitrate::automatic_t >(&bitrate);
    ASSERT_NE(automatic, nullptr);
    ASSERT_TRUE(automatic->min);
    if (automatic->min)
    {
        EXPECT_EQ(automatic->min.value(), 9.6);
    }
    ASSERT_TRUE(automatic->max);
    if (automatic->max)
    {
        EXPECT_EQ(automatic->max.value(), 19.2);
    }
}
// NOLINTEND(readability-function-cognitive-complexity)

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_ncf_general_parser, general)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string const text{
        "general {"
        "    LIN_protocol_version = \"2.2\";"
        "    supplier = 0x0005; function = 0x0020; variant = 1;"
        "    bitrate = automatic min 10 kbps max 20 kbps;"
        "    sends_wake_up_signal = \"yes\";"
        "}"
    };
    general_t general{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::general, x3::ascii::space, general);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(general.protocol_version.c_str(), "2.2");
    EXPECT_EQ(general.supplier, 0x0005);
    EXPECT_EQ(general.function, 0x0020);
    EXPECT_EQ(general.variant, 0x01);
    auto *automatic = std::get_if< general::bitrate::automatic_t >(&general.bitrate);
    ASSERT_NE(automatic, nullptr);
    ASSERT_TRUE(automatic->min);
    if (automatic->min)
    {
        EXPECT_EQ(automatic->min.value(), 10.0);
    }
    ASSERT_TRUE(automatic->max);
    if (automatic->max)
    {
        EXPECT_EQ(automatic->max.value(), 20.0);
    }
    EXPECT_TRUE(general.sends_wake_up_signal);
}
// NOLINTEND(readability-function-cognitive-complexity)
