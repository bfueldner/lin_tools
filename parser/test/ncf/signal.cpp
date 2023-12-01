#include <string>
#include <variant>

#include <gtest/gtest.h>

#include <lin/ncf/parser/signal.hpp>
#include <lin/ncf/signal.hpp>

/* 8.2.5.2 Signal definition */

TEST(test_lin_ncf_signal_parser, signal)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string const text{ "fault_state {size = 2; init_value = 0; offset = 9; fault_enc;}" };
    signal_t signal{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::signal_, x3::ascii::space, signal);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(signal.name.c_str(), "fault_state");
    auto *scalar = std::get_if< signal::init_value::scalar_t >(&signal.init_value);
    ASSERT_NE(scalar, nullptr);
    EXPECT_EQ(*scalar, 0);
    EXPECT_EQ(signal.size, 2);
    EXPECT_EQ(signal.offset, 9);
    EXPECT_STREQ(signal.encoding.c_str(), "fault_enc");
}

TEST(test_lin_ncf_signal_parser, signals)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string const text{
        "signals {"
        "  state       {size = 8; init_value = 0; offset = 0;}"
        "  fault_state {size = 2; init_value = 0; offset = 9; fault_enc;}"
        "  error_bit   {size = 1; init_value = 0; offset = 8;}"
        "  angle       {size = 16; init_value = {0x22, 0x11}; offset = 16;}"
        "}"
    };
    signals_t signals{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::signals_, x3::ascii::space, signals);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(signals.size(), 4);
    // NOLINTBEGIN(readability-container-data-pointer)
    {
        auto signal = signals[0];
        EXPECT_STREQ(signal.name.c_str(), "state");
        auto *scalar = std::get_if< signal::init_value::scalar_t >(&signal.init_value);
        ASSERT_NE(scalar, nullptr);
        EXPECT_EQ(*scalar, 0);
        EXPECT_EQ(signal.size, 8);
        EXPECT_EQ(signal.offset, 0);
        EXPECT_STREQ(signal.encoding.c_str(), "");
    }
    {
        auto signal = signals[1];
        EXPECT_STREQ(signal.name.c_str(), "fault_state");
        auto *scalar = std::get_if< signal::init_value::scalar_t >(&signal.init_value);
        ASSERT_NE(scalar, nullptr);
        EXPECT_EQ(*scalar, 0);
        EXPECT_EQ(signal.size, 2);
        EXPECT_EQ(signal.offset, 9);
        EXPECT_STREQ(signal.encoding.c_str(), "fault_enc");
    }
    {
        auto signal = signals[2];
        EXPECT_STREQ(signal.name.c_str(), "error_bit");
        auto *scalar = std::get_if< signal::init_value::scalar_t >(&signal.init_value);
        ASSERT_NE(scalar, nullptr);
        EXPECT_EQ(*scalar, 0);
        EXPECT_EQ(signal.size, 1);
        EXPECT_EQ(signal.offset, 8);
        EXPECT_STREQ(signal.encoding.c_str(), "");
    }
    {
        auto signal = signals[3];
        EXPECT_STREQ(signal.name.c_str(), "angle");
        auto *scalar = std::get_if< signal::init_value::array_t >(&signal.init_value);
        ASSERT_NE(scalar, nullptr);
        EXPECT_EQ(*scalar, (signal::init_value::array_t{ 0x22, 0x11 }));
        EXPECT_EQ(signal.size, 16);
        EXPECT_EQ(signal.offset, 16);
        EXPECT_STREQ(signal.encoding.c_str(), "");
    }
    // NOLINTEND(readability-container-data-pointer)
}
