#include <string>
#include <variant>

#include <gtest/gtest.h>

#include <lin/common/signal_encoding_type.hpp>

#include <lin/common/parser/signal_encoding_type.hpp>

TEST(test_lin_common_signal_encoding_type_parser, logical_value)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common::signal_encoding_type;

    std::string text{ "logical_value, 0, \"off\";" };
    logical_value_t logical_value{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::logical_value, x3::ascii::space, logical_value);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(logical_value.signal_value, 0);
    EXPECT_STREQ(logical_value.text_info.c_str(), "off");
}

TEST(test_lin_common_signal_encoding_type_parser, physical_value)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common::signal_encoding_type;

    std::string text{ "physical_value, 1, 254, 1, 100, \"lux\";" };
    physical_range_t physical_range;

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::physical_range, x3::ascii::space, physical_range);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(physical_range.min_value, 1);
    EXPECT_EQ(physical_range.max_value, 254);
    EXPECT_EQ(physical_range.scale, 1.0);
    EXPECT_EQ(physical_range.offset, 100.0);
    EXPECT_STREQ(physical_range.text_info.c_str(), "lux");
}

TEST(test_lin_common_signal_encoding_type_parser, bcd_value)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common::signal_encoding_type;

    std::string text{ "bcd_value ;" };
    bcd_value_t bcd_value;

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::bcd_value, x3::ascii::space, bcd_value);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());
}

TEST(test_lin_common_signal_encoding_type_parser, encoding_ascii_value)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common::signal_encoding_type;

    std::string text{ "ascii_value ;" };
    ascii_value_t ascii_value;

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::ascii_value, x3::ascii::space, ascii_value);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());
}

TEST(test_lin_common_signal_encoding_type_parser, encoding_value)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common::signal_encoding_type;

    std::string text{ "logical_value, 1, \"on\";" };
    value_t value;

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::value, x3::ascii::space, value);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *logic = std::get_if< logical_value_t >(&value);
    ASSERT_NE(logic, nullptr);
    EXPECT_EQ(logic->signal_value, 1);
    EXPECT_STREQ(logic->text_info.c_str(), "on");
}
