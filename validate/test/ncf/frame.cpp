#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>
#include <lin/ncf/frame.hpp>
#include <lin/ncf/signal.hpp>
#include <lin/ncf/validate/frame.hpp>

/* 8.2.5 Frame definition */

class test_lin_ncf_frame_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ncf_frame_validate, length)
{
    using namespace lin::ncf;

    frame_t const frame{ .size = 1 };

    validate::frame::length_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "length\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_frame_validate, length_error_too_low)
{
    using namespace lin::ncf;

    frame_t const frame{ .size = 0 };

    validate::frame::length_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "length: Value too low '0' (1..8)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_frame_validate, length_error_too_high)
{
    using namespace lin::ncf;

    frame_t const frame{ .size = 9 };

    validate::frame::length_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "length: Value too high '9' (1..8)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_frame_validate, min_period)
{
    using namespace lin::ncf;

    frame_t const frame{ .min_period = 10 };

    validate::frame::min_period_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "min_period\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_frame_validate, min_period_error_too_low)
{
    using namespace lin::ncf;

    frame_t const frame{ .min_period = -1 };

    validate::frame::min_period_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "min_period: Value too low '-1' (>= 0)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_frame_validate, max_period)
{
    using namespace lin::ncf;

    frame_t const frame{ .max_period = 10 };

    validate::frame::max_period_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "max_period\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_frame_validate, max_period_error_too_low)
{
    using namespace lin::ncf;

    frame_t const frame{ .max_period = -1 };

    validate::frame::max_period_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "max_period: Value too low '-1' (>= 0)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_frame_validate, min_period_max_period)
{
    using namespace lin::ncf;

    frame_t const frame{ .min_period = 100, .max_period = 200 };

    validate::frame::min_period_max_period_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "min_period/max_period\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_frame_validate, min_period_max_period_no_min_period)
{
    using namespace lin::ncf;

    frame_t const frame{ .max_period = 100 };

    validate::frame::min_period_max_period_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_frame_validate, min_period_max_period_no_max_period)
{
    using namespace lin::ncf;

    frame_t const frame{ .min_period = 100 };

    validate::frame::min_period_max_period_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_frame_validate, min_period_max_period_error_range)
{
    using namespace lin::ncf;

    frame_t const frame{ .min_period = 200, .max_period = 100 };

    validate::frame::min_period_max_period_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "min_period/max_period: Invalid range '200..100' (min_period <= max_period)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_frame_validate, signal_names)
{
    using namespace lin::ncf;

    frame_t const frame{ .signals{ signal_t{ .name = "abc" }, signal_t{ .name = "def" } } };

    validate::frame::signal_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signal_names\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_frame_validate, signal_names_error_not_unique)
{
    using namespace lin::ncf;

    frame_t const frame{ .signals{ signal_t{ .name = "abc" },
                                   signal_t{ .name = "def" },
                                   signal_t{ .name = "def" },
                                   signal_t{ .name = "abc" } } };

    validate::frame::signal_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "signal_names: Names not unique 'abc, def'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_frame_validate, signal_sizes)
{
    using namespace lin::ncf;

    frame_t const frame{ .size = 2,
                         .signals{ signal_t{ .name = "abc", .size = 2, .offset = 0 },
                                   signal_t{ .name = "def", .size = 6, .offset = 2 },
                                   signal_t{ .name = "ghi", .size = 8, .offset = 8 } } };

    validate::frame::signal_sizes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signal_sizes\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_frame_validate, signal_sizes_warning_empty)
{
    using namespace lin::ncf;

    frame_t const frame{};

    validate::frame::signal_sizes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signal_sizes: Empty\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_frame_validate, signal_sizes_warning_unused_space)
{
    using namespace lin::ncf;

    frame_t const frame{ .size = 3,
                         .signals{ signal_t{ .name = "abc", .size = 2, .offset = 0 },
                                   signal_t{ .name = "def", .size = 6, .offset = 2 },
                                   signal_t{ .name = "ghi", .size = 8, .offset = 8 } } };

    validate::frame::signal_sizes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "signal_sizes: Signals with unused space '8 bit' (24 bit)\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_frame_validate, signal_sizes_error_signals_too_big)
{
    using namespace lin::ncf;

    frame_t const frame{ .size = 2,
                         .signals{ signal_t{ .name = "abc", .size = 2, .offset = 0 },
                                   signal_t{ .name = "def", .size = 6, .offset = 2 },
                                   signal_t{ .name = "ghi", .size = 10, .offset = 8 } } };

    validate::frame::signal_sizes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "signal_sizes: Signals greater than frame '2 bit' (16 bit)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_frame_validate, signal_offsets)
{
    using namespace lin::ncf;

    frame_t const frame{ .size = 2,
                         .signals{ signal_t{ .name = "abc", .size = 2, .offset = 0 },
                                   signal_t{ .name = "def", .size = 6, .offset = 2 },
                                   signal_t{ .name = "ghi", .size = 8, .offset = 8 } } };

    validate::frame::signal_offsets_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signal_offsets\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_frame_validate, signal_offsets_warning_empty)
{
    using namespace lin::ncf;

    frame_t const frame{};

    validate::frame::signal_offsets_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signal_offsets: Empty\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_frame_validate, signal_offsets_warning_not_sorted)
{
    using namespace lin::ncf;

    frame_t const frame{ .size = 2,
                         .signals{ signal_t{ .name = "def", .size = 6, .offset = 2 },
                                   signal_t{ .name = "abc", .size = 2, .offset = 0 },
                                   signal_t{ .name = "ghi", .size = 8, .offset = 8 } } };

    validate::frame::signal_offsets_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signal_offsets: Not sorted\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_frame_validate, signal_size_offset)
{
    using namespace lin::ncf;

    frame_t const frame{ .signals{ signal_t{ .name = "abc", .size = 2, .offset = 0 },
                                   signal_t{ .name = "def", .size = 6, .offset = 2 },
                                   signal_t{ .name = "ghi", .size = 8, .offset = 8 } } };

    validate::frame::signal_size_offset_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signal_size_offset\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_frame_validate, signal_size_offset_error_overlap)
{
    using namespace lin::ncf;

    frame_t const frame{ .signals{ signal_t{ .name = "abc", .size = 3, .offset = 0 },
                                   signal_t{ .name = "def", .size = 6, .offset = 2 },
                                   signal_t{ .name = "ghi", .size = 8, .offset = 8 } } };

    validate::frame::signal_size_offset_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signal_size_offset: Signal overlap 'def'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}
