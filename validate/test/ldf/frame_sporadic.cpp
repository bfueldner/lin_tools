#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>
#include <lin/ldf/frame_sporadic.hpp>
#include <lin/ldf/frame_unconditional.hpp>
#include <lin/ldf/validate/frame_sporadic.hpp>

/* 9.2.4.2 Sporadic frames */

class test_lin_ldf_frame_sporadic_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ldf_frame_sporadic_validate, frames)
{
    using namespace lin::ldf;

    frame::unconditionals_t const unconditional_frames{
        frame::unconditional_t{ .name = "RSM_Frm1" }, frame::unconditional_t{ .name = "LSM_Frm1" }
    };
    frame::sporadic_t const sporadic_frame{ .frames = { "RSM_Frm1", "LSM_Frm1" } };

    validate::frame::sporadic::frames_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(unconditional_frames, sporadic_frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "frames\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_sporadic_validate, frames_error_not_defined)
{
    using namespace lin::ldf;

    frame::unconditionals_t const sporadic_frames{ frame::unconditional_t{ .name = "RSM_Frm1" } };
    frame::sporadic_t const event_triggered_frame{ .frames = { "RSM_Frm1", "LSM_Frm1" } };

    validate::frame::sporadic::frames_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(sporadic_frames, event_triggered_frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "frames: Not defined 'LSM_Frm1'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}
