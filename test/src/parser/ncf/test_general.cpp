#include <string>
#include <variant>

#include <gtest/gtest.h>

#include <lin/ncf/general.hpp>

#include <lin/ncf/parser/general.hpp>

TEST(test_lin_ncf_general_parser, bitrate)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf::general;

    std::string text{ "19.2 kbps" };
    bitrate_t bitrate{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::bitrate, x3::ascii::space, bitrate);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(bitrate.value, 19.2);
}

TEST(test_lin_ncf_general_parser, bitrate_definition_automatic_default)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf::general;

    std::string text{ "automatic" };
    bitrate_definition::automatic_t bitrate_definition_automatic{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::bitrate_definition_automatic,
        x3::ascii::space,
        bitrate_definition_automatic);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_FALSE(bitrate_definition_automatic.min);
    EXPECT_FALSE(bitrate_definition_automatic.max);
}

TEST(test_lin_ncf_general_parser, bitrate_definition_automatic_min)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf::general;

    std::string text{ "automatic min 9.6 kbps" };
    bitrate_definition::automatic_t bitrate_definition_automatic{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::bitrate_definition_automatic,
        x3::ascii::space,
        bitrate_definition_automatic);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_FALSE(bitrate_definition_automatic.min);
    if (bitrate_definition_automatic.min)
    {
        EXPECT_EQ(bitrate_definition_automatic.min.value().value, 9.6);
    }
    EXPECT_FALSE(bitrate_definition_automatic.max);
}

TEST(test_lin_ncf_general_parser, bitrate_definition_automatic_max)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf::general;

    std::string text{ "automatic max 19.2 kbps" };
    bitrate_definition::automatic_t bitrate_definition_automatic{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::bitrate_definition_automatic,
        x3::ascii::space,
        bitrate_definition_automatic);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_FALSE(bitrate_definition_automatic.min);
    ASSERT_TRUE(bitrate_definition_automatic.max);
    if (bitrate_definition_automatic.max)
    {
        EXPECT_EQ(bitrate_definition_automatic.max.value().value, 19.2);
    }
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_ncf_general_parser, bitrate_definition_automatic_min_max)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf::general;

    std::string text{ "automatic min 9.6 kbps max 19.2 kbps" };
    bitrate_definition::automatic_t bitrate_definition_automatic{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::bitrate_definition_automatic,
        x3::ascii::space,
        bitrate_definition_automatic);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_TRUE(bitrate_definition_automatic.min);
    if (bitrate_definition_automatic.min)
    {
        EXPECT_EQ(bitrate_definition_automatic.min.value().value, 9.6);
    }
    ASSERT_TRUE(bitrate_definition_automatic.max);
    if (bitrate_definition_automatic.max)
    {
        EXPECT_EQ(bitrate_definition_automatic.max.value().value, 19.2);
    }
}
// NOLINTEND(readability-function-cognitive-complexity)

TEST(test_lin_ncf_general_parser, bitrate_definition_select_single)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf::general;

    std::string text{ "select { 19.2 kbps }" };
    bitrate_definition::select_t bitrate_definition_select{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::bitrate_definition_select,
        x3::ascii::space,
        bitrate_definition_select);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_FALSE(bitrate_definition_select.empty());
    EXPECT_EQ(bitrate_definition_select.data()->value, 19.2);
}

TEST(test_lin_ncf_general_parser, bitrate_definition_select_multiple)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf::general;

    std::string text{ "select { 4.8 kbps, 9.6kbps, 19.2 kbps }" };
    bitrate_definition::select_t bitrate_definition_select{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::bitrate_definition_select,
        x3::ascii::space,
        bitrate_definition_select);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(bitrate_definition_select.size(), 3);
    EXPECT_EQ(bitrate_definition_select[0].value, 4.8);
    EXPECT_EQ(bitrate_definition_select[1].value, 9.6);
    EXPECT_EQ(bitrate_definition_select[2].value, 19.2);
}

TEST(test_lin_ncf_general_parser, bitrate_definition_fixed)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf::general;

    std::string text{ "19.2 kbps" };
    bitrate_definition::fixed_t bitrate_definition_fixed{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::bitrate_definition_fixed,
        x3::ascii::space,
        bitrate_definition_fixed);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(bitrate_definition_fixed.value, 19.2);
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_ncf_general_parser, bitrate_definition)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf::general;

    std::string text{ "automatic min 9.6 kbps max 19.2 kbps" };
    bitrate_definition_t bitrate_definition{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::bitrate_definition, x3::ascii::space, bitrate_definition);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *automatic = std::get_if< bitrate_definition::automatic_t >(&bitrate_definition);
    ASSERT_NE(automatic, nullptr);
    ASSERT_TRUE(automatic->min);
    if (automatic->min)
    {
        EXPECT_EQ(automatic->min.value().value, 9.6);
    }
    ASSERT_TRUE(automatic->max);
    if (automatic->max)
    {
        EXPECT_EQ(automatic->max.value().value, 19.2);
    }
}
// NOLINTEND(readability-function-cognitive-complexity)

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_ncf_general_parser, general)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string text{
        "general {"
        "    LIN_protocol_version = \"2.2\";"
        "    supplier = 0x0005; function = 0x0020; variant = 1;"
        "    bitrate = automatic min 10 kbps max 20 kbps;"
        "    sends_wake_up_signal = \"yes\";"
        "}"
    };
    general_t general{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::general_definition, x3::ascii::space, general);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(general.protocol_version.c_str(), "2.2");
    EXPECT_EQ(general.supplier_id, 0x0005);
    EXPECT_EQ(general.function_id, 0x0020);
    EXPECT_EQ(general.variant_id, 0x01);
    auto *automatic =
        std::get_if< general::bitrate_definition::automatic_t >(&general.bitrate_definition);
    ASSERT_NE(automatic, nullptr);
    ASSERT_TRUE(automatic->min);
    if (automatic->min)
    {
        EXPECT_EQ(automatic->min.value().value, 10.0);
    }
    ASSERT_TRUE(automatic->max);
    if (automatic->max)
    {
        EXPECT_EQ(automatic->max.value().value, 20.0);
    }
    EXPECT_TRUE(general.sends_wake_up_signal);
}
// NOLINTEND(readability-function-cognitive-complexity)
