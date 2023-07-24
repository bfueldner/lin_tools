#include <gtest/gtest.h>

#include <lin/lexical/ncf/general.hpp>

TEST(test_lin_lexical_ncf_general, bitrate)
{
    using namespace lin::lexical::ncf::general;
    namespace x3 = boost::spirit::x3;

    std::string text{ "19.2 kbps" };
    bitrate_t bitrate{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::bitrate, x3::ascii::space, bitrate);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_EQ(bitrate, 19.2);
}

TEST(test_lin_lexical_ncf_general, bitrate_definition_automatic_default)
{
    using namespace lin::lexical::ncf::general;
    namespace x3 = boost::spirit::x3;

    std::string text{ "automatic" };
    bitrate_definition::automatic_t bitrate_definition_automatic{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::bitrate_definition_automatic,
        x3::ascii::space,
        bitrate_definition_automatic);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_EQ(bitrate_definition_automatic.min, 1.0);
    EXPECT_EQ(bitrate_definition_automatic.max, 20.0);
}

TEST(test_lin_lexical_ncf_general, bitrate_definition_automatic_min)
{
    using namespace lin::lexical::ncf::general;
    namespace x3 = boost::spirit::x3;

    std::string text{ "automatic min 9.6 kbps" };
    bitrate_definition::automatic_t bitrate_definition_automatic{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::bitrate_definition_automatic,
        x3::ascii::space,
        bitrate_definition_automatic);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_EQ(bitrate_definition_automatic.min, 9.6);
    EXPECT_EQ(bitrate_definition_automatic.max, 20.0);
}

TEST(test_lin_lexical_ncf_general, bitrate_definition_automatic_max)
{
    using namespace lin::lexical::ncf::general;
    namespace x3 = boost::spirit::x3;

    std::string text{ "automatic max 19.2 kbps" };
    bitrate_definition::automatic_t bitrate_definition_automatic{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::bitrate_definition_automatic,
        x3::ascii::space,
        bitrate_definition_automatic);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_EQ(bitrate_definition_automatic.min, 1.0);
    EXPECT_EQ(bitrate_definition_automatic.max, 19.2);
}

TEST(test_lin_lexical_ncf_general, bitrate_definition_automatic_min_max)
{
    using namespace lin::lexical::ncf::general;
    namespace x3 = boost::spirit::x3;

    std::string text{ "automatic min 9.6 kbps max 19.2 kbps" };
    bitrate_definition::automatic_t bitrate_definition_automatic{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::bitrate_definition_automatic,
        x3::ascii::space,
        bitrate_definition_automatic);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_EQ(bitrate_definition_automatic.min, 9.6);
    EXPECT_EQ(bitrate_definition_automatic.max, 19.2);
}

TEST(test_lin_lexical_ncf_general, bitrate_definition_select_single)
{
    using namespace lin::lexical::ncf::general;
    namespace x3 = boost::spirit::x3;

    std::string text{ "select { 19.2 kbps }" };
    bitrate_definition::select_t bitrate_definition_select{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::bitrate_definition_select,
        x3::ascii::space,
        bitrate_definition_select);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_EQ(bitrate_definition_select, bitrate_definition::select_t{ 19.2 });
}

TEST(test_lin_lexical_ncf_general, bitrate_definition_select_multiple)
{
    using namespace lin::lexical::ncf::general;
    namespace x3 = boost::spirit::x3;

    std::string text{ "select { 4.8 kbps, 9.6kbps, 19.2 kbps }" };
    bitrate_definition::select_t bitrate_definition_select{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::bitrate_definition_select,
        x3::ascii::space,
        bitrate_definition_select);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_EQ(bitrate_definition_select, (bitrate_definition::select_t{ 4.8, 9.6, 19.2 }));
}

TEST(test_lin_lexical_ncf_general, bitrate_definition_fixed)
{
    using namespace lin::lexical::ncf::general;
    namespace x3 = boost::spirit::x3;

    std::string text{ "19.2 kbps" };
    bitrate_definition::fixed_t bitrate_definition_fixed{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::bitrate_definition_fixed,
        x3::ascii::space,
        bitrate_definition_fixed);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_EQ(bitrate_definition_fixed, 19.2);
}

TEST(test_lin_lexical_ncf_general, bitrate_definition)
{
    using namespace lin::lexical::ncf::general;
    namespace x3 = boost::spirit::x3;

    std::string text{ "automatic min 9.6 kbps max 19.2 kbps" };
    bitrate_definition_t bitrate_definition{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::bitrate_definition, x3::ascii::space, bitrate_definition);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    auto *automatic = std::get_if< bitrate_definition::automatic_t >(&bitrate_definition);
    EXPECT_NE(automatic, nullptr);
    EXPECT_EQ(automatic->min, 9.6);
    EXPECT_EQ(automatic->max, 19.2);
}

TEST(test_lin_lexical_ncf_general, general)
{
    using namespace lin::lexical::ncf;
    namespace x3 = boost::spirit::x3;

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
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_STREQ(general.protocol_version.c_str(), "2.2");
    EXPECT_EQ(general.supplier_id, 0x0005);
    EXPECT_EQ(general.function_id, 0x0020);
    EXPECT_EQ(general.variant_id, 0x01);
    auto *automatic =
        std::get_if< general::bitrate_definition::automatic_t >(&general.bitrate_definition);
    EXPECT_NE(automatic, nullptr);
    EXPECT_EQ(automatic->min, 10.0);
    EXPECT_EQ(automatic->max, 20.0);
    EXPECT_TRUE(general.sends_wake_up_signal);
}
