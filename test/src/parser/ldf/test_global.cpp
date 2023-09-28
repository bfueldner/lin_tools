#include <string>

#include <gtest/gtest.h>

#include <lin/ldf/global.hpp>

#include <lin/ldf/parser/global.hpp>

TEST(test_lin_ldf_global_parser, lin_protocol_version)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf::global;

    std::string text{ "LIN_protocol_version = \"2.2\" ;" };
    lin_protocol_version_t lin_protocol_version{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::lin_protocol_version, x3::ascii::space, lin_protocol_version);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(lin_protocol_version.c_str(), "2.2");
}

TEST(test_lin_ldf_global_parser, lin_language_version)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf::global;

    std::string text{ "LIN_language_version = \"2.2\" ;" };
    lin_language_version_t lin_language_version{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::lin_language_version, x3::ascii::space, lin_language_version);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(lin_language_version.c_str(), "2.2");
}

TEST(test_lin_ldf_global_parser, lin_speed)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf::global;

    std::string text{ "LIN_speed = 19.2 kbps;" };
    lin_speed_t lin_speed{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::lin_speed, x3::ascii::space, lin_speed);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(lin_speed, 19.2);
}

TEST(test_lin_ldf_global_parser, channel_name)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf::global;

    std::string text{ "Channel_name = \"DB\";" };
    channel_name_t channel_name{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::channel_name, x3::ascii::space, channel_name);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(channel_name.c_str(), "DB");
}
