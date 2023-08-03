#include <gtest/gtest.h>

#include <lin/lexical/ldf/global.hpp>

TEST(test_lin_lexical_ldf_global, protocol_version)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::global;

    std::string text{ "LIN_protocol_version = \"2.2\" ;" };
    protocol_version_t protocol_version{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::protocol_version, x3::ascii::space, protocol_version);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(protocol_version.c_str(), "2.2");
}

TEST(test_lin_lexical_ldf_global, language_version)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::global;

    std::string text{ "LIN_language_version = \"2.2\" ;" };
    language_version_t language_version{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::language_version, x3::ascii::space, language_version);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(language_version.c_str(), "2.2");
}

TEST(test_lin_lexical_ldf_global, speed)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::global;

    std::string text{ "LIN_speed = 19.2 kbps;" };
    speed_t speed{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::speed, x3::ascii::space, speed);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(speed, 19.2);
}

TEST(test_lin_lexical_ldf_global, channel_name)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::global;

    std::string text{ "Channel_name = \"DB\";" };
    channel_name_t channel_name{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::channel_name, x3::ascii::space, channel_name);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(channel_name.c_str(), "DB");
}
