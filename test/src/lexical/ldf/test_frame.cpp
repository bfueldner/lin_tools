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

/* 9.2.4.2 Sporadic frames */

TEST(test_lin_lexical_ldf_frame, sporadic_frame)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::frame;

    std::string text{ "SPRD_Frm: LSM_Frm1;" };
    sporadic_frame_t sporadic_frame;

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::sporadic_frame, x3::ascii::space, sporadic_frame);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(sporadic_frame.sporadic_frame_name.c_str(), "SPRD_Frm");
    ASSERT_EQ(sporadic_frame.frame_names.size(), 1);
    EXPECT_STREQ(sporadic_frame.frame_names[0].c_str(), "LSM_Frm1");
}

TEST(test_lin_lexical_ldf_frame, sporadic_frames)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::frame;

    std::string text{
        "Sporadic_frames {"
        "    SPRD_Frm1: LSM_Frm1;"
        "    SPRD_Frm2: RSM_Frm1, RSM_Frm2;"
        "}"
    };
    sporadic_frames_t sporadic_frames;

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::sporadic_frames, x3::ascii::space, sporadic_frames);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(sporadic_frames.size(), 2);
    EXPECT_STREQ(sporadic_frames[0].sporadic_frame_name.c_str(), "SPRD_Frm1");
    ASSERT_EQ(sporadic_frames[0].frame_names.size(), 1);
    EXPECT_EQ(sporadic_frames[0].frame_names, (std::vector< std::string >{ "LSM_Frm1" }));
    EXPECT_STREQ(sporadic_frames[1].sporadic_frame_name.c_str(), "SPRD_Frm2");
    EXPECT_EQ(
        sporadic_frames[1].frame_names, (std::vector< std::string >{ "RSM_Frm1", "RSM_Frm2" }));
}

/* 9.2.4.3 Event triggered frames */

TEST(test_lin_lexical_ldf_frame, event_triggered_frame)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::frame;

    std::string text{ "Node_Status_Event : Collision_resolver, 0x06, RSM_Frm1, LSM_Frm1;" };
    event_triggered_frame_t event_triggered_frame;

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::event_triggered_frame,
        x3::ascii::space,
        event_triggered_frame);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_STREQ(event_triggered_frame.event_trig_frm_name.c_str(), "Node_Status_Event");
    EXPECT_STREQ(
        event_triggered_frame.collision_resolving_schedule_table.c_str(), "Collision_resolver");
    EXPECT_EQ(event_triggered_frame.frame_id, 0x06);
    EXPECT_EQ(event_triggered_frame.frame_names.size(), 2);
    EXPECT_STREQ(event_triggered_frame.frame_names[0].c_str(), "RSM_Frm1");
    EXPECT_STREQ(event_triggered_frame.frame_names[1].c_str(), "LSM_Frm1");
}

TEST(test_lin_lexical_ldf_frame, event_triggered_frames)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::frame;

    std::string text{
        "Event_triggered_frames {"
        "    Node_Status_Event : Collision_resolver, 0x06, RSM_Frm1, LSM_Frm1;"
        "}"
    };
    event_triggered_frames_t event_triggered_frames;

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::event_triggered_frames,
        x3::ascii::space,
        event_triggered_frames);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_EQ(event_triggered_frames.size(), 1);
    EXPECT_STREQ(event_triggered_frames[0].event_trig_frm_name.c_str(), "Node_Status_Event");
    EXPECT_STREQ(
        event_triggered_frames[0].collision_resolving_schedule_table.c_str(), "Collision_resolver");
    EXPECT_EQ(event_triggered_frames[0].frame_id, 0x06);
    EXPECT_EQ(event_triggered_frames[0].frame_names.size(), 2);
    EXPECT_STREQ(event_triggered_frames[0].frame_names[0].c_str(), "RSM_Frm1");
    EXPECT_STREQ(event_triggered_frames[0].frame_names[1].c_str(), "LSM_Frm1");
}

/* 9.2.4.4 Diagnostic frames */

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_lexical_ldf_frame, diagnostic_frame)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::frame;

    std::string text{
        "MasterReq: 60 {"
        "    MasterReqB0, 0;"
        "    MasterReqB1, 8;"
        "    MasterReqB2, 16;"
        "    MasterReqB3, 24;"
        "    MasterReqB4, 32;"
        "    MasterReqB5, 40;"
        "    MasterReqB6, 48;"
        "    MasterReqB7, 56;"
        "}"
    };
    diagnostic_frame_t diagnostic_frame;

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::diagnostic_frame, x3::ascii::space, diagnostic_frame);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_STREQ(diagnostic_frame.frame_name.c_str(), "MasterReq");
    EXPECT_EQ(diagnostic_frame.frame_id, 60);
    EXPECT_EQ(diagnostic_frame.frame_entries.size(), 8);

    int index = 0;
    for (auto const &frame_signal : diagnostic_frame.frame_entries)
    {
        std::string const name = "MasterReqB" + std::to_string(index);

        EXPECT_STREQ(frame_signal.signal_name.c_str(), name.c_str());
        EXPECT_EQ(frame_signal.signal_offset, index * 8);
        index++;
    }
}
// NOLINTEND(readability-function-cognitive-complexity)

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_lexical_ldf_frame, diagnostic_frames)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::frame;

    std::string text{
        "Diagnostic_frames {"
        "    MasterReq: 60 {"
        "        MasterReqB0, 0;"
        "        MasterReqB1, 8;"
        "        MasterReqB2, 16;"
        "        MasterReqB3, 24;"
        "        MasterReqB4, 32;"
        "        MasterReqB5, 40;"
        "        MasterReqB6, 48;"
        "        MasterReqB7, 56;"
        "    }"
        "    SlaveResp: 61 {"
        "         SlaveRespB0, 0;"
        "         SlaveRespB1, 8;"
        "         SlaveRespB2, 16;"
        "         SlaveRespB3, 24;"
        "         SlaveRespB4, 32;"
        "         SlaveRespB5, 40;"
        "         SlaveRespB6, 48;"
        "         SlaveRespB7, 56;"
        "    }"
        "}"
    };
    diagnostic_frames_t diagnostic_frames;

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::diagnostic_frames, x3::ascii::space, diagnostic_frames);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_EQ(diagnostic_frames.size(), 2);

    EXPECT_STREQ(diagnostic_frames[0].frame_name.c_str(), "MasterReq");
    EXPECT_EQ(diagnostic_frames[0].frame_id, 60);
    EXPECT_EQ(diagnostic_frames[0].frame_entries.size(), 8);

    int index = 0;
    for (auto const &frame_signal : diagnostic_frames[0].frame_entries)
    {
        std::string const name = "MasterReqB" + std::to_string(index);

        EXPECT_STREQ(frame_signal.signal_name.c_str(), name.c_str());
        EXPECT_EQ(frame_signal.signal_offset, index * 8);
        index++;
    }

    EXPECT_STREQ(diagnostic_frames[1].frame_name.c_str(), "SlaveResp");
    EXPECT_EQ(diagnostic_frames[1].frame_id, 61);
    EXPECT_EQ(diagnostic_frames[1].frame_entries.size(), 8);

    index = 0;
    for (auto const &frame_signal : diagnostic_frames[1].frame_entries)
    {
        std::string const name = "SlaveRespB" + std::to_string(index);

        EXPECT_STREQ(frame_signal.signal_name.c_str(), name.c_str());
        EXPECT_EQ(frame_signal.signal_offset, index * 8);
        index++;
    }
}
// NOLINTEND(readability-function-cognitive-complexity)
