#include <string>
#include <variant>
#include <vector>

#include <gtest/gtest.h>

#include <lin/ldf/parser/signal_standard.hpp>
#include <lin/ldf/signal_standard.hpp>

/* 9.2.3.1 Standard signals */

TEST(test_lin_ldf_signal_parser, standard_signal)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "InternalLightsRequest: 2, 0, CEM, LSM, RSM;" };
    signal::standard_t signal{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::standard_signal, x3::ascii::space, signal);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(signal.name.c_str(), "InternalLightsRequest");
    EXPECT_EQ(signal.size, 2);
    auto *init_value = std::get_if< signal::standard::init_value::scalar_t >(&signal.init_value);
    ASSERT_NE(init_value, nullptr);
    EXPECT_EQ(*init_value, 0);
    EXPECT_STREQ(signal.published_by.c_str(), "CEM");
    EXPECT_EQ(signal.subscribed_by, (std::vector< std::string >{ "LSM", "RSM" }));
}

TEST(test_lin_ldf_signal_parser, standard_signals)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "Signals {"
        "   LSMerror: 1, 0, LSM;"
        "   RSMerror: 1, 1, RSM, CEM;"
        "}"
    };
    signal::standards_t signals{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::standard_signals, x3::ascii::space, signals);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(signals.size(), 2);

    EXPECT_STREQ(signals[0].name.c_str(), "LSMerror");
    EXPECT_EQ(signals[0].size, 1);
    {
        auto *init_value =
            std::get_if< signal::standard::init_value::scalar_t >(&signals[0].init_value);
        ASSERT_NE(init_value, nullptr);
        EXPECT_EQ(*init_value, 0);
    }
    EXPECT_STREQ(signals[0].published_by.c_str(), "LSM");
    EXPECT_EQ(signals[0].subscribed_by, (std::vector< std::string >{}));

    EXPECT_STREQ(signals[1].name.c_str(), "RSMerror");
    EXPECT_EQ(signals[1].size, 1);
    {
        auto *init_value =
            std::get_if< signal::standard::init_value::scalar_t >(&signals[1].init_value);
        ASSERT_NE(init_value, nullptr);
        EXPECT_EQ(*init_value, 1);
    }
    EXPECT_STREQ(signals[1].published_by.c_str(), "RSM");
    EXPECT_EQ(signals[1].subscribed_by, (std::vector< std::string >{ "CEM" }));
}
