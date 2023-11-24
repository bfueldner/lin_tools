#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>
#include <lin/ncf/signal.hpp>
#include <lin/ncf/validate/signal.hpp>

/* 8.2.5.2 Signal definition */

class test_lin_ncf_signal_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ncf_signal_validate, init_value_scalar)
{
    using namespace lin::ncf;

    signal_t const signal{ .init_value = signal::init_value::scalar_t{ 1 }, .size = 4 };

    validate::signal::init_value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "init_value\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_signal_validate, init_value_scalar_error_too_low)
{
    using namespace lin::ncf;

    signal_t const signal{ .init_value = signal::init_value::scalar_t{ -1 }, .size = 4 };

    validate::signal::init_value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signal);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "init_value: Scalar value too low '-1' (0..15)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_signal_validate, init_value_scalar_error_too_high)
{
    using namespace lin::ncf;

    signal_t const signal{ .init_value = signal::init_value::scalar_t{ 16 }, .size = 4 };

    validate::signal::init_value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signal);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "init_value: Scalar value too high '16' (0..15)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_signal_validate, init_value_array)
{
    using namespace lin::ncf;

    signal_t const signal{ .init_value = signal::init_value::array_t{ 2, 0 }, .size = 16 };

    validate::signal::init_value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "init_value\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_signal_validate, init_value_array_error_size)
{
    using namespace lin::ncf;

    signal_t const signal{ .init_value = signal::init_value::array_t{ 2, 0 }, .size = 4 };

    validate::signal::init_value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signal);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "init_value: Number of array values mismatch signal size '2, 0' (2)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_signal_validate, size_scalar)
{
    using namespace lin::ncf;

    signal_t const signal{ .init_value = signal::init_value::scalar_t{ 1 }, .size = 4 };

    validate::signal::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "size\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_signal_validate, size_array)
{
    using namespace lin::ncf;

    signal_t const signal{ .init_value = signal::init_value::array_t{ 0, 0 }, .size = 16 };

    validate::signal::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "size\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_signal_validate, size_error_too_low)
{
    using namespace lin::ncf;

    signal_t const signal{ .size = 0 };

    validate::signal::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "size: Value too low '0' (1..64)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_signal_validate, size_error_not_aligned)
{
    using namespace lin::ncf;

    signal_t const signal{ .init_value = signal::init_value::array_t{ 0 }, .size = 7 };

    validate::signal::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "size: Value not byte aligned '7' (8)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_signal_validate, size_error_too_high)
{
    using namespace lin::ncf;

    signal_t const signal{ .size = 65 };

    validate::signal::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "size: Value too high '65' (1..64)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_signal_validate, offset_scalar)
{
    using namespace lin::ncf;

    signal_t const signal{ .init_value = signal::init_value::scalar_t{ 0 }, .offset = 0 };

    validate::signal::offset_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "offset\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_signal_validate, offset_array)
{
    using namespace lin::ncf;

    signal_t const signal{ .init_value = signal::init_value::array_t{ 0, 0 }, .offset = 16 };

    validate::signal::offset_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "offset\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_signal_validate, offset_error_too_low)
{
    using namespace lin::ncf;

    signal_t const signal{ .offset = -1 };

    validate::signal::offset_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "offset: Value too low '-1' (0..63)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_signal_validate, offset_error_not_aligned)
{
    using namespace lin::ncf;

    signal_t const signal{ .init_value = signal::init_value::array_t{ 0 }, .offset = 9 };

    validate::signal::offset_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "offset: Value not byte aligned '9' (8)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_signal_validate, offset_error_too_high)
{
    using namespace lin::ncf;

    signal_t const signal{ .offset = 64 };

    validate::signal::offset_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "offset: Value too high '64' (0..63)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}
