#include <sstream>

#include <gtest/gtest.h>

#include <lin/ldf/frame_event_triggered.hpp>
#include <lin/ldf/generator/frame_event_triggered.hpp>

/* 9.2.4.3 Event triggered frames */

TEST(test_lin_ldf_frame_generator, event_triggered_frame)
{
    using namespace lin::ldf::frame;

    event_triggered_t const event_triggered_frame{
        "Node_Status_Event", "Collision_resolver", 0x06, { "RSM_Frm1", "LSM_Frm1" }
    };

    std::stringstream stream{};
    stream << event_triggered_frame;
    EXPECT_EQ(stream.str(), "Node_Status_Event: Collision_resolver, 0x06, RSM_Frm1, LSM_Frm1;\n");
}

TEST(test_lin_ldf_frame_generator, event_triggered_frames)
{
    using namespace lin::ldf::frame;

    event_triggereds_t const event_triggered_frames{
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
