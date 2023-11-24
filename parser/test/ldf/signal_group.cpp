#include <string>

#include <gtest/gtest.h>

#include <lin/ldf/parser/signal_group.hpp>
#include <lin/ldf/signal_group.hpp>

/* 9.2.3.3 Signal groups */

TEST(test_lin_ldf_signal_parser, signal_group_signal)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "CPMReqB4,32;" };
    signal::group::signal_t signal{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::signal_group_signal, x3::ascii::space, signal);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(signal.name.c_str(), "CPMReqB4");
    EXPECT_EQ(signal.offset, 32);
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_ldf_signal_parser, signal_group)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "CPMReq:64 {"
        "    CPMReqB0,0;"
        "    CPMReqB1,8;"
        "    CPMReqB2,16;"
        "    CPMReqB3,24;"
        "    CPMReqB4,32;"
        "    CPMReqB5,40;"
        "    CPMReqB6,48;"
        "    CPMReqB7,56;"
        "}"
    };
    signal::group_t group{};

    auto position = text.begin();
    auto result = phrase_parse(position, text.end(), parser::signal_group, x3::ascii::space, group);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(group.name.c_str(), "CPMReq");
    EXPECT_EQ(group.size, 64);

    int index = 0;
    for (auto const &signal : group.signals)
    {
        std::string const name = "CPMReqB" + std::to_string(index);

        EXPECT_STREQ(signal.name.c_str(), name.c_str());
        EXPECT_EQ(signal.offset, index * 8);
        index++;
    }
}
// NOLINTEND(readability-function-cognitive-complexity)

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_ldf_signal_parser, signal_groups)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "Signal_groups {"
        "    CPMReq:64 {"
        "        CPMReqB0,0;"
        "        CPMReqB1,8;"
        "        CPMReqB2,16;"
        "        CPMReqB3,24;"
        "        CPMReqB4,32;"
        "        CPMReqB5,40;"
        "        CPMReqB6,48;"
        "        CPMReqB7,56;"
        "    }"
        "    CPMResp:64 {"
        "        CPMRespB0,0;"
        "        CPMRespB1,8;"
        "        CPMRespB2,16;"
        "        CPMRespB3,24;"
        "        CPMRespB4,32;"
        "        CPMRespB5,40;"
        "        CPMRespB6,48;"
        "        CPMRespB7,56;"
        "    }"
        "}"
    };
    signal::groups_t groups{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::signal_groups, x3::ascii::space, groups);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(groups.size(), 2);

    EXPECT_STREQ(groups[0].name.c_str(), "CPMReq");
    EXPECT_EQ(groups[0].size, 64);

    int index = 0;
    for (auto const &signal : groups[0].signals)
    {
        std::string const name = "CPMReqB" + std::to_string(index);

        EXPECT_STREQ(signal.name.c_str(), name.c_str());
        EXPECT_EQ(signal.offset, index * 8);
        index++;
    }

    index = 0;
    for (auto const &signal : groups[1].signals)
    {
        std::string const name = "CPMRespB" + std::to_string(index);

        EXPECT_STREQ(signal.name.c_str(), name.c_str());
        EXPECT_EQ(signal.offset, index * 8);
        index++;
    }
}
// NOLINTEND(readability-function-cognitive-complexity)
