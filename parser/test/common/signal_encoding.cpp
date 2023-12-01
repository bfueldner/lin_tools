#include <string>
#include <variant>

#include <gtest/gtest.h>

#include <lin/common/parser/signal_encoding.hpp>
#include <lin/common/signal_encoding.hpp>

TEST(test_lin_common_signal_encoding_parser, logical_value)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common;

    std::string text{ "logical_value, 0, \"off\";" };
    signal::encoding::logical_value_t logical_value{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::signal_encoding_logical_value,
        x3::ascii::space,
        logical_value);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(logical_value.value, 0);
    EXPECT_STREQ(logical_value.text_info.c_str(), "off");
}

TEST(test_lin_common_signal_encoding_parser, physical_range)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common;

    std::string text{ "physical_value, 1, 254, 1, 100, \"lux\";" };
    signal::encoding::physical_range_t physical_range{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::signal_encoding_physical_range,
        x3::ascii::space,
        physical_range);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(physical_range.min, 1);
    EXPECT_EQ(physical_range.max, 254);
    EXPECT_EQ(physical_range.scale, 1.0);
    EXPECT_EQ(physical_range.offset, 100.0);
    EXPECT_STREQ(physical_range.text_info.c_str(), "lux");
}

TEST(test_lin_common_signal_encoding_parser, bcd_value)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common;

    std::string text{ "bcd_value ;" };
    signal::encoding::bcd_value_t bcd_value{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::signal_encoding_bcd_value, x3::ascii::space, bcd_value);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());
}

TEST(test_lin_common_signal_encoding_parser, ascii_value)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common;

    std::string text{ "ascii_value ;" };
    signal::encoding::ascii_value_t ascii_value{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::signal_encoding_ascii_value, x3::ascii::space, ascii_value);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());
}

TEST(test_lin_common_signal_encoding_parser, value)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common;

    std::string text{ "logical_value, 1, \"on\";" };
    signal::encoding::value_t value;

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::signal_encoding_value, x3::ascii::space, value);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *logic = std::get_if< signal::encoding::logical_value_t >(&value);
    ASSERT_NE(logic, nullptr);
    EXPECT_EQ(logic->value, 1);
    EXPECT_STREQ(logic->text_info.c_str(), "on");
}
