#include <string>

#include <gtest/gtest.h>

#include <lin/ncf/frame.hpp>

#include <lin/ncf/parser/frame.hpp>

/* 8.2.5 Frame definition */

TEST(test_lin_ncf_frame_parser, frame_kind)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string const text{ "subscribe" };
    frame::kind_t frame_kind{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::frame_kind, x3::ascii::space, frame_kind);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(frame_kind, frame::kind_t::subscribe);
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_ncf_frame_parser, frame)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string const text{
        "publish node_status {"
        "    length = 4; min_period = 10 ms; max_period = 100 ms;"
        "    signals {"
        "        state {size = 8; init_value = 0; offset = 0;}"
        "        fault_state {size = 2; init_value = 0; offset = 9; fault_enc;}"
        "    }"
        "}"
    };
    frame_t frame{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::frame, x3::ascii::space, frame);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(frame.kind, frame::kind_t::publish);
    EXPECT_STREQ(frame.name.c_str(), "node_status");
    EXPECT_EQ(frame.size, 4);
    ASSERT_TRUE(frame.min_period);
    if (frame.min_period)
    {
        EXPECT_EQ(frame.min_period, 10);
    }
    ASSERT_TRUE(frame.max_period);
    if (frame.max_period)
    {
        EXPECT_EQ(frame.max_period, 100);
    }
    EXPECT_FALSE(frame.event_triggered_frame);
    ASSERT_EQ(frame.signals.size(), 2);
    EXPECT_STREQ(frame.signals[0].name.c_str(), "state");
    EXPECT_EQ(frame.signals[0].size, 8);
    EXPECT_EQ(frame.signals[0].offset, 0);
    EXPECT_STREQ(frame.signals[1].name.c_str(), "fault_state");
    EXPECT_EQ(frame.signals[1].size, 2);
    EXPECT_EQ(frame.signals[1].offset, 9);
    EXPECT_STREQ(frame.signals[1].encoding.c_str(), "fault_enc");
}
// NOLINTEND(readability-function-cognitive-complexity)

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_ncf_frame_parser, frames)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string const text{
        "frames {"
        "    publish node_status {"
        "        length = 4; min_period = 10 ms; max_period = 100 ms;"
        "        signals {"
        "            state {size = 8; init_value = 0; offset = 0;}"
        "            fault_state {size = 2; init_value = 0; offset = 9; fault_enc;}"
        "            error_bit {size = 1; init_value = 0; offset = 8;}"
        "            angle {size = 16; init_value = {0x22, 0x11}; offset = 16;}"
        "        }"
        "    }"
        "    subscribe control {"
        "        length = 1; max_period = 100 ms;"
        "        signals {"
        "            command {size = 8; init_value = 0; offset = 0; position;}"
        "        }"
        "    }"
        "}"
    };
    frames_t frames{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::frames, x3::ascii::space, frames);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(frames.size(), 2);
    EXPECT_EQ(frames[0].kind, frame::kind_t::publish);
    EXPECT_STREQ(frames[0].name.c_str(), "node_status");
    EXPECT_EQ(frames[1].kind, frame::kind_t::subscribe);
    EXPECT_STREQ(frames[1].name.c_str(), "control");
}
// NOLINTEND(readability-function-cognitive-complexity)
