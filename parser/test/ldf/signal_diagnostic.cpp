#include <string>
#include <variant>

#include <gtest/gtest.h>

#include <lin/ldf/parser/signal_diagnostic.hpp>
#include <lin/ldf/signal_diagnostic.hpp>

/* 9.2.3.2 Diagnostic signals */

TEST(test_lin_ldf_signal_parser, diagnostic_signal)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "MasterReqB0: 8, 0 ;" };
    signal::diagnostic_t signal{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::diagnostic_signal, x3::ascii::space, signal);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(signal.name.c_str(), "MasterReqB0");
    EXPECT_EQ(signal.size, 8);
    auto *init_value = std::get_if< signal::diagnostic::init_value::scalar_t >(&signal.init_value);
    ASSERT_NE(init_value, nullptr);
    EXPECT_EQ(*init_value, 0);
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_ldf_signal_parser, diagnostic_signals)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

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
    signal::diagnostics_t signals{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::diagnostic_signals, x3::ascii::space, signals);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    for (int index = 0; index < 8; index++)
    {
        std::string const name = "MasterReqB" + std::to_string(index);

        EXPECT_STREQ(signals[index].name.c_str(), name.c_str());
        EXPECT_EQ(signals[index].size, 8);
        auto *init_value =
            std::get_if< signal::diagnostic::init_value::scalar_t >(&signals[index].init_value);
        ASSERT_NE(init_value, nullptr);
        EXPECT_EQ(*init_value, 0);
    }

    for (int index = 0; index < 8; index++)
    {
        std::string const name = "SlaveRespB" + std::to_string(index);

        EXPECT_STREQ(signals[index + 8].name.c_str(), name.c_str());
        EXPECT_EQ(signals[index + 8].size, 8);
        auto *init_value =
            std::get_if< signal::diagnostic::init_value::scalar_t >(&signals[index + 8].init_value);
        ASSERT_NE(init_value, nullptr);
        EXPECT_EQ(*init_value, 0);
    }
}
// NOLINTEND(readability-function-cognitive-complexity)
