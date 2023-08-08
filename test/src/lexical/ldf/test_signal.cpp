#include <gtest/gtest.h>

#include <lin/lexical/ldf/signal.hpp>

TEST(test_lin_lexical_ldf_signal, standard_signal_init_value_scalar)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::signal::standard_signal;

    std::string text{ "100" };
    init_value_t init_value{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::init_value, x3::ascii::space, init_value);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *scalar = std::get_if< init_value_scalar_t >(&init_value);
    ASSERT_NE(scalar, nullptr);
    EXPECT_EQ(*scalar, 100);
}

TEST(test_lin_lexical_ldf_signal, standard_signal_init_value_array)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::signal::standard_signal;

    std::string text{ "{ 0xA0, 0xB0 }" };
    init_value_t init_value{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::init_value, x3::ascii::space, init_value);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *array = std::get_if< init_value_array_t >(&init_value);
    ASSERT_NE(array, nullptr);
    EXPECT_EQ(*array, (init_value_array_t{ 0xA0, 0xB0 }));
}

TEST(test_lin_lexical_ldf_signal, standard_signal)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::signal;

    std::string text{ "InternalLightsRequest: 2, 0, CEM, LSM, RSM;" };
    standard_signal_t standard_signal{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::standard_signal, x3::ascii::space, standard_signal);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(standard_signal.signal_name.c_str(), "InternalLightsRequest");
    EXPECT_EQ(standard_signal.signal_size, 2);
    auto *init_value =
        std::get_if< standard_signal::init_value_scalar_t >(&standard_signal.init_value);
    ASSERT_NE(init_value, nullptr);
    EXPECT_EQ(*init_value, 0);
    EXPECT_STREQ(standard_signal.published_by.c_str(), "CEM");
    EXPECT_EQ(standard_signal.subscribed_by, (std::vector< std::string >{ "LSM", "RSM" }));
}

TEST(test_lin_lexical_ldf_signal, standard_signals)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::signal;

    std::string text{
        "Signals {"
        "   LSMerror: 1, 0, LSM;"
        "   RSMerror: 1, 1, RSM, CEM;"
        "}"
    };
    standard_signals_t standard_signals;

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::standard_signals, x3::ascii::space, standard_signals);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(standard_signals.size(), 2);

    EXPECT_STREQ(standard_signals[0].signal_name.c_str(), "LSMerror");
    EXPECT_EQ(standard_signals[0].signal_size, 1);
    {
        auto *init_value =
            std::get_if< standard_signal::init_value_scalar_t >(&standard_signals[0].init_value);
        ASSERT_NE(init_value, nullptr);
        EXPECT_EQ(*init_value, 0);
    }
    EXPECT_STREQ(standard_signals[0].published_by.c_str(), "LSM");
    EXPECT_EQ(standard_signals[0].subscribed_by, (std::vector< std::string >{}));

    EXPECT_STREQ(standard_signals[1].signal_name.c_str(), "RSMerror");
    EXPECT_EQ(standard_signals[1].signal_size, 1);
    {
        auto *init_value =
            std::get_if< standard_signal::init_value_scalar_t >(&standard_signals[1].init_value);
        ASSERT_NE(init_value, nullptr);
        EXPECT_EQ(*init_value, 1);
    }
    EXPECT_STREQ(standard_signals[1].published_by.c_str(), "RSM");
    EXPECT_EQ(standard_signals[1].subscribed_by, (std::vector< std::string >{ "CEM" }));
}
