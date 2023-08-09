#include <gtest/gtest.h>

#include <lin/lexical/ldf/frame.hpp>

/* 9.2.4.1 Unconditional frames */

TEST(test_lin_lexical_ldf_frame, unconditional_frame_frame_entry)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::frame::unconditional_frame;

    std::string text{ "RightIntLightsSwitch, 8;" };
    frame_entry_t frame_entry{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::frame_entry, x3::ascii::space, frame_entry);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(frame_entry.signal_name.c_str(), "RightIntLightsSwitch");
    EXPECT_EQ(frame_entry.signal_offset, 8);
}

TEST(test_lin_lexical_ldf_frame, unconditional_frame)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::frame;

    std::string text{
        "LSM_Frm2: 0x03, LSM, 1 {"
        "    LSMerror, 0;"
        "    IntTest, 1;"
        "}"
    };
    unconditional_frame_t unconditional_frame{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::unconditional_frame, x3::ascii::space, unconditional_frame);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(unconditional_frame.frame_name.c_str(), "LSM_Frm2");
    EXPECT_EQ(unconditional_frame.frame_id, 3);
    EXPECT_STREQ(unconditional_frame.published_by.c_str(), "LSM");
    EXPECT_EQ(unconditional_frame.frame_size, 1);
    ASSERT_EQ(unconditional_frame.frame_entries.size(), 2);
    EXPECT_STREQ(unconditional_frame.frame_entries[0].signal_name.c_str(), "LSMerror");
    EXPECT_EQ(unconditional_frame.frame_entries[0].signal_offset, 0);
    EXPECT_STREQ(unconditional_frame.frame_entries[1].signal_name.c_str(), "IntTest");
    EXPECT_EQ(unconditional_frame.frame_entries[1].signal_offset, 1);
}

TEST(test_lin_lexical_ldf_frame, unconditional_frames)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::frame;

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
    unconditional_frames_t unconditional_frames{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::unconditional_frames, x3::ascii::space, unconditional_frames);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(unconditional_frames.size(), 2);
    EXPECT_STREQ(unconditional_frames[0].frame_name.c_str(), "CEM_Frm1");
    EXPECT_EQ(unconditional_frames[0].frame_id, 1);
    EXPECT_STREQ(unconditional_frames[0].published_by.c_str(), "CEM");
    EXPECT_EQ(unconditional_frames[0].frame_size, 1);
    ASSERT_EQ(unconditional_frames[0].frame_entries.size(), 1);
    EXPECT_STREQ(
        unconditional_frames[0].frame_entries[0].signal_name.c_str(), "InternalLightsRequest");
    EXPECT_EQ(unconditional_frames[0].frame_entries[0].signal_offset, 0);
    EXPECT_STREQ(unconditional_frames[1].frame_name.c_str(), "LSM_Frm1");
    EXPECT_EQ(unconditional_frames[1].frame_id, 2);
    EXPECT_STREQ(unconditional_frames[1].published_by.c_str(), "LSM");
    EXPECT_EQ(unconditional_frames[1].frame_size, 2);
    ASSERT_EQ(unconditional_frames[1].frame_entries.size(), 1);
    EXPECT_STREQ(
        unconditional_frames[1].frame_entries[0].signal_name.c_str(), "LeftIntLightsSwitch");
    EXPECT_EQ(unconditional_frames[1].frame_entries[0].signal_offset, 8);
}
