#include <gtest/gtest.h>

#include <lin/lexical/ldf/signal.hpp>

/* 9.2.3.1 Standard signals */

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

/* 9.2.3.2 Diagnostic signals */

TEST(test_lin_lexical_ldf_signal, diagnostic_signal)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::signal;

    std::string text{ "MasterReqB0: 8, 0 ;" };
    diagnostic_signal_t diagnostic_signal{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::diagnostic_signal, x3::ascii::space, diagnostic_signal);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(diagnostic_signal.signal_name.c_str(), "MasterReqB0");
    EXPECT_EQ(diagnostic_signal.signal_size, 8);
    auto *init_value =
        std::get_if< diagnostic_signal::init_value_scalar_t >(&diagnostic_signal.init_value);
    ASSERT_NE(init_value, nullptr);
    EXPECT_EQ(*init_value, 0);
}

TEST(test_lin_lexical_ldf_signal, diagnostic_signals)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::signal;

    std::string text{
        "Diagnostic_signals {"
        "    MasterReqB0: 8, 0 ;"
        "    MasterReqB1: 8, 0 ;"
        "    MasterReqB2: 8, 0 ;"
        "    MasterReqB3: 8, 0 ;"
        "    MasterReqB4: 8, 0 ;"
        "    MasterReqB5: 8, 0 ;"
        "    MasterReqB6: 8, 0 ;"
        "    MasterReqB7: 8, 0 ;"
        "    SlaveRespB0: 8, 0 ;"
        "    SlaveRespB1: 8, 0 ;"
        "    SlaveRespB2: 8, 0 ;"
        "    SlaveRespB3: 8, 0 ;"
        "    SlaveRespB4: 8, 0 ;"
        "    SlaveRespB5: 8, 0 ;"
        "    SlaveRespB6: 8, 0 ;"
        "    SlaveRespB7: 8, 0 ;"
        "}"
    };
    diagnostic_signals_t diagnostic_signals{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::diagnostic_signals, x3::ascii::space, diagnostic_signals);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    for (int index = 0; index < 8; index++)
    {
        std::string name = "MasterReqB" + std::to_string(index);

        EXPECT_STREQ(diagnostic_signals[index].signal_name.c_str(), name.c_str());
        EXPECT_EQ(diagnostic_signals[index].signal_size, 8);
        auto *init_value = std::get_if< diagnostic_signal::init_value_scalar_t >(
            &diagnostic_signals[index].init_value);
        ASSERT_NE(init_value, nullptr);
        EXPECT_EQ(*init_value, 0);
    }

    for (int index = 0; index < 8; index++)
    {
        std::string name = "SlaveRespB" + std::to_string(index);

        EXPECT_STREQ(diagnostic_signals[index + 8].signal_name.c_str(), name.c_str());
        EXPECT_EQ(diagnostic_signals[index + 8].signal_size, 8);
        auto *init_value = std::get_if< diagnostic_signal::init_value_scalar_t >(
            &diagnostic_signals[index + 8].init_value);
        ASSERT_NE(init_value, nullptr);
        EXPECT_EQ(*init_value, 0);
    }
}
