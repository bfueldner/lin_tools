#include <string>

#include <gtest/gtest.h>

#include <lin/ncf/frame.hpp>

#include <lin/ncf/parser/frame.hpp>

TEST(test_lin_ncf_frame_parser, frame_kind)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf::frame;

    std::string text{ "subscribe" };
    frame_kind_t frame_kind{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::frame_kind, x3::ascii::space, frame_kind);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(frame_kind, frame_kind_t::subscribe);
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_ncf_frame_parser, single_frame)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf::frame;

    std::string text{
        "publish node_status {"
        "    length = 4; min_period = 10 ms; max_period = 100 ms;"
        "    signals {"
        "        state {size = 8; init_value = 0; offset = 0;}"
        "        fault_state {size = 2; init_value = 0; offset = 9; fault_enc;}"
        "    }"
        "}"
    };
    single_frame_t single_frame{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::single_frame, x3::ascii::space, single_frame);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(single_frame.frame_kind, frame_kind_t::publish);
    EXPECT_STREQ(single_frame.frame_name.c_str(), "node_status");
    EXPECT_EQ(single_frame.frame_properties.length, 4);
    ASSERT_TRUE(single_frame.frame_properties.min_period);
    if (single_frame.frame_properties.min_period)
    {
        EXPECT_EQ(single_frame.frame_properties.min_period, 10);
    }
    ASSERT_TRUE(single_frame.frame_properties.max_period);
    if (single_frame.frame_properties.max_period)
    {
        EXPECT_EQ(single_frame.frame_properties.max_period, 100);
    }
    EXPECT_FALSE(single_frame.frame_properties.event_triggered_frame);
    ASSERT_EQ(single_frame.signal_definition.size(), 2);
    EXPECT_STREQ(single_frame.signal_definition[0].signal_name.c_str(), "state");
    EXPECT_EQ(single_frame.signal_definition[0].signal_properties.size, 8);
    EXPECT_EQ(single_frame.signal_definition[0].signal_properties.offset, 0);
    EXPECT_STREQ(single_frame.signal_definition[1].signal_name.c_str(), "fault_state");
    EXPECT_EQ(single_frame.signal_definition[1].signal_properties.size, 2);
    EXPECT_EQ(single_frame.signal_definition[1].signal_properties.offset, 9);
    EXPECT_STREQ(
        single_frame.signal_definition[1].signal_properties.encoding_name.c_str(), "fault_enc");
}
// NOLINTEND(readability-function-cognitive-complexity)

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_ncf_frame_parser, frames)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string text{
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
    auto result =
        phrase_parse(position, text.end(), parser::frame_definition, x3::ascii::space, frames);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(frames.size(), 2);
    EXPECT_EQ(frames[0].frame_kind, frame::frame_kind_t::publish);
    EXPECT_STREQ(frames[0].frame_name.c_str(), "node_status");
    EXPECT_EQ(frames[1].frame_kind, frame::frame_kind_t::subscribe);
    EXPECT_STREQ(frames[1].frame_name.c_str(), "control");
}
// NOLINTEND(readability-function-cognitive-complexity)

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_ncf_frame_properties_parser, frame_properties)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string text{ "length = 4; min_period = 10 ms; max_period = 100 ms;" };
    frame_properties_t frame_properties;

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::frame_properties, x3::ascii::space, frame_properties);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(frame_properties.length, 4);
    ASSERT_TRUE(frame_properties.min_period);
    if (frame_properties.min_period)
    {
        EXPECT_EQ(frame_properties.min_period, 10);
    }
    ASSERT_TRUE(frame_properties.max_period);
    if (frame_properties.max_period)
    {
        EXPECT_EQ(frame_properties.max_period, 100);
    }
    EXPECT_FALSE(frame_properties.event_triggered_frame);
}
// NOLINTEND(readability-function-cognitive-complexity)