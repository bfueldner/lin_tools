#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>
#include <lin/ldf/frame_event_triggered.hpp>
#include <lin/ldf/frame_unconditional.hpp>
#include <lin/ldf/schedule_table.hpp>
#include <lin/ldf/validate/frame_event_triggered.hpp>

/* 9.2.4.3 Event triggered frames */

class test_lin_ldf_frame_event_triggered_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ldf_frame_event_triggered_validate, schedule_table)
{
    using namespace lin::ldf;

    schedule_tables_t const schedule_tables{ schedule_table_t{ .name = "Collision_resolver" } };
    frame::unconditionals_t const unconditional_frames{};
    frame::event_triggered_t const event_triggered_frame{ .schedule_table = "Collision_resolver" };

    validate::frame::event_triggered::schedule_table_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(schedule_tables, unconditional_frames, event_triggered_frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "schedule_table\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_event_triggered_validate, schedule_table_error_not_defined)
{
    using namespace lin::ldf;

    schedule_tables_t const schedule_tables{ schedule_table_t{} };
    frame::unconditionals_t const unconditional_frames{};
    frame::event_triggered_t const event_triggered_frame{ .schedule_table = "Collision_resolver" };

    validate::frame::event_triggered::schedule_table_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(schedule_tables, unconditional_frames, event_triggered_frame);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "schedule_table: Not defined 'Collision_resolver'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_frame_event_triggered_validate, id)
{
    using namespace lin::ldf;

    schedule_tables_t const schedule_tables{};
    frame::unconditionals_t const unconditional_frames{};
    frame::event_triggered_t const event_triggered_frame{ .id = 0x10 };

    validate::frame::event_triggered::id_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(schedule_tables, unconditional_frames, event_triggered_frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "id\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_event_triggered_validate, id_error_too_low)
{
    using namespace lin::ldf;

    schedule_tables_t const schedule_tables{};
    frame::unconditionals_t const unconditional_frames{};
    frame::event_triggered_t const event_triggered_frame{ .id = -1 };

    validate::frame::event_triggered::id_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(schedule_tables, unconditional_frames, event_triggered_frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "id: Value too low '-1' (0..59)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_frame_event_triggered_validate, id_error_too_high)
{
    using namespace lin::ldf;

    schedule_tables_t const schedule_tables{};
    frame::unconditionals_t const unconditional_frames{};
    frame::event_triggered_t const event_triggered_frame{ .id = 60 };

    validate::frame::event_triggered::id_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(schedule_tables, unconditional_frames, event_triggered_frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "id: Value too high '60' (0..59)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_frame_event_triggered_validate, frames)
{
    using namespace lin::ldf;

    schedule_tables_t const schedule_tables{};
    frame::unconditionals_t const unconditional_frames{
        frame::unconditional_t{ .name = "RSM_Frm1" }, frame::unconditional_t{ .name = "LSM_Frm1" }
    };
    frame::event_triggered_t const event_triggered_frame{ .frames = { "RSM_Frm1", "LSM_Frm1" } };

    validate::frame::event_triggered::frames_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(schedule_tables, unconditional_frames, event_triggered_frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "frames\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_event_triggered_validate, frames_error_not_defined)
{
    using namespace lin::ldf;

    schedule_tables_t const schedule_tables{};
    frame::unconditionals_t const unconditional_frames{ frame::unconditional_t{
        .name = "RSM_Frm1" } };
    frame::event_triggered_t const event_triggered_frame{ .frames = { "RSM_Frm1", "LSM_Frm1" } };

    validate::frame::event_triggered::frames_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(schedule_tables, unconditional_frames, event_triggered_frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "frames: Not defined 'LSM_Frm1'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}
