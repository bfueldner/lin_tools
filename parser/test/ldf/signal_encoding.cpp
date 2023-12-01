#include <string>
#include <variant>

#include <gtest/gtest.h>

#include <lin/ldf/parser/signal_encoding.hpp>
#include <lin/ldf/signal_encoding.hpp>

/* 9.2.6.1 Signal encoding type definition */

TEST(test_lin_ldf_signal_parser, signal_encoding)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "LightEncoding {"
        "    logical_value, 0, \"Off\";"
        "    physical_value, 1, 254, 1, 100, \"lux\";"
        "    logical_value, 255, \"error\";"
        "}"
    };
    signal::encoding_t encoding{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::signal_encoding, x3::ascii::space, encoding);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(encoding.name.c_str(), "LightEncoding");
    ASSERT_EQ(encoding.values.size(), 3);
    // NOLINTBEGIN(readability-container-data-pointer)
    {
        auto *logic = std::get_if< signal::encoding::logical_value_t >(&encoding.values[0]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->value, 0);
        EXPECT_STREQ(logic->text_info.c_str(), "Off");
    }
    {
        auto *physical = std::get_if< signal::encoding::physical_range_t >(&encoding.values[1]);
        ASSERT_NE(physical, nullptr);
        EXPECT_EQ(physical->min, 1);
        EXPECT_EQ(physical->max, 254);
        EXPECT_EQ(physical->scale, 1.0);
        EXPECT_EQ(physical->offset, 100.0);
        EXPECT_STREQ(physical->text_info.c_str(), "lux");
    }
    {
        auto *logic = std::get_if< signal::encoding::logical_value_t >(&encoding.values[2]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->value, 255);
        EXPECT_STREQ(logic->text_info.c_str(), "error");
    }
    // NOLINTEND(readability-container-data-pointer)
}
