#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>
#include <lin/ncf/frame.hpp>
#include <lin/ncf/signal.hpp>
#include <lin/ncf/signal_encoding.hpp>
#include <lin/ncf/validate/signal_encoding.hpp>

/* 8.2.5.3 Signal encoding type definition */

class test_lin_ncf_signal_encoding_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ncf_signal_encoding_validate, usage)
{
    using namespace lin::ncf;

    frames_t const frames{ frame_t{ .signals = { signal_t{ .encoding = "speed" },
                                                 signal_t{},
                                                 signal_t{ .encoding = "status" } } },
                           frame_t{ .signals = { signal_t{ .encoding = "speed" } } } };
    signal::encodings_t const encodings{ signal::encoding_t{ .name = "status" },
                                         signal::encoding_t{ .name = "speed" } };

    validate::signal_encoding::usage_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frames, encodings);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "usage\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_signal_encoding_validate, usage_error_missing)
{
    using namespace lin::ncf;

    frames_t const frames{ frame_t{ .signals = { signal_t{ .encoding = "speed" },
                                                 signal_t{},
                                                 signal_t{ .encoding = "status" } } },
                           frame_t{ .signals = { signal_t{ .encoding = "speed" } } } };
    signal::encodings_t const encodings{ signal::encoding_t{ .name = "status" } };

    validate::signal_encoding::usage_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frames, encodings);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "usage: Not defined 'speed'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_signal_encoding_validate, usage_warning_unused)
{
    using namespace lin::ncf;

    frames_t const frames{ frame_t{ .signals = { signal_t{ .encoding = "speed" } } } };
    signal::encodings_t const encodings{ signal::encoding_t{ .name = "status" },
                                         signal::encoding_t{ .name = "speed" } };

    validate::signal_encoding::usage_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frames, encodings);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "usage: Not used 'status'\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}
