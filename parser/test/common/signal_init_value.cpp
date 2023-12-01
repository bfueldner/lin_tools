#include <string>
#include <variant>

#include <gtest/gtest.h>

#include <lin/common/parser/signal_init_value.hpp>
#include <lin/common/signal_init_value.hpp>

TEST(test_lin_common_signal_init_value_parser, scalar)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common;

    std::string text{ "100" };
    signal::init_value_t init_value{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::signal_init_value, x3::ascii::space, init_value);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *scalar = std::get_if< signal::init_value::scalar_t >(&init_value);
    ASSERT_NE(scalar, nullptr);
    EXPECT_EQ(*scalar, 100);
}

TEST(test_lin_common_signal_init_value_parser, array)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common;

    std::string text{ "{0x22, 0x11}" };
    signal::init_value_t init_value{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::signal_init_value, x3::ascii::space, init_value);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *array = std::get_if< signal::init_value::array_t >(&init_value);
    ASSERT_NE(array, nullptr);
    EXPECT_EQ(*array, (signal::init_value::array_t{ 0x22, 0x11 }));
}
