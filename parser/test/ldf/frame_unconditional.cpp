#include <string>

#include <gtest/gtest.h>

#include <lin/ldf/frame_unconditional.hpp>
#include <lin/ldf/parser/frame_unconditional.hpp>

/* 9.2.4.1 Unconditional frames */

TEST(test_lin_ldf_frame_unconditional_parser, unconditional_frame_signal)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "RightIntLightsSwitch, 8;" };
    frame::unconditional::signal_t signal{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::unconditional_frame_signal, x3::ascii::space, signal);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(signal.name.c_str(), "RightIntLightsSwitch");
    EXPECT_EQ(signal.offset, 8);
}

TEST(test_lin_ldf_frame_unconditional_parser, unconditional_frame)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "LSM_Frm2: 0x03, LSM, 1 {"
        "    LSMerror, 0;"
        "    IntTest, 1;"
        "}"
    };
    frame::unconditional_t frame{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::unconditional_frame, x3::ascii::space, frame);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(frame.name.c_str(), "LSM_Frm2");
    EXPECT_EQ(frame.id, 3);
    EXPECT_STREQ(frame.published_by.c_str(), "LSM");
    EXPECT_EQ(frame.size, 1);
    ASSERT_EQ(frame.signals.size(), 2);
    EXPECT_STREQ(frame.signals[0].name.c_str(), "LSMerror");
    EXPECT_EQ(frame.signals[0].offset, 0);
    EXPECT_STREQ(frame.signals[1].name.c_str(), "IntTest");
    EXPECT_EQ(frame.signals[1].offset, 1);
}

TEST(test_lin_ldf_frame_unconditional_parser, unconditional_frames)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "Frames {"
        "    CEM_Frm1: 0x01, CEM, 1 {"
        "        InternalLightsRequest, 0;"
        "    }"
        "    LSM_Frm1: 0x02, LSM, 2 {"
        "        LeftIntLightsSwitch, 8;"
        "    }"
        "}"
    };
    frame::unconditionals_t frames{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::unconditional_frames, x3::ascii::space, frames);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(frames.size(), 2);
    EXPECT_STREQ(frames[0].name.c_str(), "CEM_Frm1");
    EXPECT_EQ(frames[0].id, 1);
    EXPECT_STREQ(frames[0].published_by.c_str(), "CEM");
    EXPECT_EQ(frames[0].size, 1);
    ASSERT_EQ(frames[0].signals.size(), 1);
    EXPECT_STREQ(frames[0].signals[0].name.c_str(), "InternalLightsRequest");
    EXPECT_EQ(frames[0].signals[0].offset, 0);
    EXPECT_STREQ(frames[1].name.c_str(), "LSM_Frm1");
    EXPECT_EQ(frames[1].id, 2);
    EXPECT_STREQ(frames[1].published_by.c_str(), "LSM");
    EXPECT_EQ(frames[1].size, 2);
    ASSERT_EQ(frames[1].signals.size(), 1);
    EXPECT_STREQ(frames[1].signals[0].name.c_str(), "LeftIntLightsSwitch");
    EXPECT_EQ(frames[1].signals[0].offset, 8);
}
