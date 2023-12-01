#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <lin/ldf/frame_event_triggered.hpp>
#include <lin/ldf/parser/frame_event_triggered.hpp>

/* 9.2.4.3 Event triggered frames */

TEST(test_lin_ldf_frame_parser, event_triggered_frame)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "Node_Status_Event : Collision_resolver, 0x06, RSM_Frm1, LSM_Frm1;" };
    frame::event_triggered_t frame{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::event_triggered_frame, x3::ascii::space, frame);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_STREQ(frame.name.c_str(), "Node_Status_Event");
    EXPECT_STREQ(frame.schedule_table.c_str(), "Collision_resolver");
    EXPECT_EQ(frame.id, 0x06);
    EXPECT_EQ(frame.frames.size(), 2);
    EXPECT_STREQ(frame.frames[0].c_str(), "RSM_Frm1");
    EXPECT_STREQ(frame.frames[1].c_str(), "LSM_Frm1");
}

TEST(test_lin_ldf_frame_event_triggered_parser, event_triggered_frames)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "Event_triggered_frames {"
        "    Node_Status_Event : Collision_resolver, 0x06, RSM_Frm1, LSM_Frm1;"
        "}"
    };
    frame::event_triggereds_t frames{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::event_triggered_frames, x3::ascii::space, frames);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_EQ(frames.size(), 1);
    EXPECT_STREQ(frames[0].name.c_str(), "Node_Status_Event");
    EXPECT_STREQ(frames[0].schedule_table.c_str(), "Collision_resolver");
    EXPECT_EQ(frames[0].id, 0x06);
    EXPECT_EQ(frames[0].frames.size(), 2);
    EXPECT_STREQ(frames[0].frames[0].c_str(), "RSM_Frm1");
    EXPECT_STREQ(frames[0].frames[1].c_str(), "LSM_Frm1");
}
