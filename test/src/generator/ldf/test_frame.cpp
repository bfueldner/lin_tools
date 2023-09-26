#include <sstream>

#include <gtest/gtest.h>

#include <lin/ldf/frame.hpp>
#include <lin/ldf/generator/frame.hpp>

/* 9.2.4.1 Unconditional frames */

TEST(test_lin_ldf_frame_generator, unconditional_frame_frame_entry)
{
    using namespace lin::ldf::frame::unconditional_frame;

    frame_entry_t const frame_entry{ "RightIntLightsSwitch", 8 };

    std::stringstream stream{};
    stream << frame_entry;
    EXPECT_EQ(stream.str(), "RightIntLightsSwitch, 8;\n");
}

TEST(test_lin_ldf_frame_generator, unconditional_frame)
{
    using namespace lin::ldf::frame;

    unconditional_frame_t const unconditional_frame{
        "LSM_Frm2", 0x03, "LSM", 1, { { "LSMerror", 0 }, { "IntTest", 1 } }
    };

    std::stringstream stream{};
    stream << unconditional_frame;
    EXPECT_EQ(
        stream.str(),
        "LSM_Frm2: 0x03, LSM, 1 {\n"
        "    LSMerror, 0;\n"
        "    IntTest, 1;\n"
        "}\n");
}

TEST(test_lin_ldf_frame_generator, unconditional_frames)
{
    using namespace lin::ldf::frame;

    unconditional_frames_t const unconditional_frames{
        { "CEM_Frm1", 0x01, "CEM", 1, { { "InternalLightsRequest", 0 } } },
        { "LSM_Frm1", 0x02, "LSM", 2, { { "LeftIntLightsSwitch", 8 } } }
    };

    std::stringstream stream{};
    stream << unconditional_frames;
    EXPECT_EQ(
        stream.str(),
        "Frames {\n"
        "    CEM_Frm1: 0x01, CEM, 1 {\n"
        "        InternalLightsRequest, 0;\n"
        "    }\n"
        "    LSM_Frm1: 0x02, LSM, 2 {\n"
        "        LeftIntLightsSwitch, 8;\n"
        "    }\n"
        "}\n");
}

/* 9.2.4.2 Sporadic frames */

TEST(test_lin_ldf_frame_generator, sporadic_frame)
{
    using namespace lin::ldf::frame;

    sporadic_frame_t const sporadic_frame{ "SPRD_Frm", { "LSM_Frm1" } };

    std::stringstream stream{};
    stream << sporadic_frame;
    EXPECT_EQ(stream.str(), "SPRD_Frm: LSM_Frm1;\n");
}

TEST(test_lin_ldf_frame_generator, sporadic_frames)
{
    using namespace lin::ldf::frame;

    sporadic_frames_t const sporadic_frames{ { "SPRD_Frm1", { "LSM_Frm1" } },
                                             { "SPRD_Frm2", { "RSM_Frm1", "RSM_Frm2" } } };

    std::stringstream stream{};
    stream << sporadic_frames;
    EXPECT_EQ(
        stream.str(),
        "Sporadic_frames {\n"
        "    SPRD_Frm1: LSM_Frm1;\n"
        "    SPRD_Frm2: RSM_Frm1, RSM_Frm2;\n"
        "}\n");
}

/* 9.2.4.3 Event triggered frames */

TEST(test_lin_ldf_frame_generator, event_triggered_frame)
{
    using namespace lin::ldf::frame;

    event_triggered_frame_t const event_triggered_frame{
        "Node_Status_Event", "Collision_resolver", 0x06, { "RSM_Frm1", "LSM_Frm1" }
    };

    std::stringstream stream{};
    stream << event_triggered_frame;
    EXPECT_EQ(stream.str(), "Node_Status_Event: Collision_resolver, 0x06, RSM_Frm1, LSM_Frm1;\n");
}

TEST(test_lin_ldf_frame_generator, event_triggered_frames)
{
    using namespace lin::ldf::frame;

    event_triggered_frames_t const event_triggered_frames{
        { "Node_Status_Event", "Collision_resolver", 0x06, { "RSM_Frm1", "LSM_Frm1" } }
    };

    std::stringstream stream{};
    stream << event_triggered_frames;
    EXPECT_EQ(
        stream.str(),
        "Event_triggered_frames {\n"
        "    Node_Status_Event: Collision_resolver, 0x06, RSM_Frm1, LSM_Frm1;\n"
        "}\n");
}

/* 9.2.4.4 Diagnostic frames */

TEST(test_lin_ldf_frame_generator, diagnostic_frame)
{
    using namespace lin::ldf::frame;

    diagnostic_frame_t const diagnostic_frame{ "MasterReq",
                                               60,
                                               { { "MasterReqB0", 0 },
                                                 { "MasterReqB1", 8 },
                                                 { "MasterReqB2", 16 },
                                                 { "MasterReqB3", 24 },
                                                 { "MasterReqB4", 32 },
                                                 { "MasterReqB5", 40 },
                                                 { "MasterReqB6", 48 },
                                                 { "MasterReqB7", 56 } } };

    std::stringstream stream{};
    stream << diagnostic_frame;
    EXPECT_EQ(
        stream.str(),
        "MasterReq: 0x3c {\n"
        "    MasterReqB0, 0;\n"
        "    MasterReqB1, 8;\n"
        "    MasterReqB2, 16;\n"
        "    MasterReqB3, 24;\n"
        "    MasterReqB4, 32;\n"
        "    MasterReqB5, 40;\n"
        "    MasterReqB6, 48;\n"
        "    MasterReqB7, 56;\n"
        "}\n");
}

TEST(test_lin_ldf_frame_generator, diagnostic_frames)
{
    using namespace lin::ldf::frame;

    diagnostic_frames_t const diagnostic_frames{ { "MasterReq",
                                                   60,
                                                   { { "MasterReqB0", 0 },
                                                     { "MasterReqB1", 8 },
                                                     { "MasterReqB2", 16 },
                                                     { "MasterReqB3", 24 },
                                                     { "MasterReqB4", 32 },
                                                     { "MasterReqB5", 40 },
                                                     { "MasterReqB6", 48 },
                                                     { "MasterReqB7", 56 } } },
                                                 { "SlaveResp",
                                                   61,
                                                   { { "SlaveRespB0", 0 },
                                                     { "SlaveRespB1", 8 },
                                                     { "SlaveRespB2", 16 },
                                                     { "SlaveRespB3", 24 },
                                                     { "SlaveRespB4", 32 },
                                                     { "SlaveRespB5", 40 },
                                                     { "SlaveRespB6", 48 },
                                                     { "SlaveRespB7", 56 } } } };

    std::stringstream stream{};
    stream << diagnostic_frames;
    EXPECT_EQ(
        stream.str(),
        "Diagnostic_frames {\n"
        "    MasterReq: 0x3c {\n"
        "        MasterReqB0, 0;\n"
        "        MasterReqB1, 8;\n"
        "        MasterReqB2, 16;\n"
        "        MasterReqB3, 24;\n"
        "        MasterReqB4, 32;\n"
        "        MasterReqB5, 40;\n"
        "        MasterReqB6, 48;\n"
        "        MasterReqB7, 56;\n"
        "    }\n"
        "    SlaveResp: 0x3d {\n"
        "        SlaveRespB0, 0;\n"
        "        SlaveRespB1, 8;\n"
        "        SlaveRespB2, 16;\n"
        "        SlaveRespB3, 24;\n"
        "        SlaveRespB4, 32;\n"
        "        SlaveRespB5, 40;\n"
        "        SlaveRespB6, 48;\n"
        "        SlaveRespB7, 56;\n"
        "    }\n"
        "}\n");
}
