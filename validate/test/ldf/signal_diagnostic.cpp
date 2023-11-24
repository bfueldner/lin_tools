#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>
#include <lin/ldf/signal_diagnostic.hpp>
#include <lin/ldf/validate/signal_diagnostic.hpp>

/* 9.2.3.2 Diagnostic signals */

class test_lin_ldf_signal_diagnostic_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ldf_signal_diagnostic_validate, signal_size)
{
    using namespace lin::ldf;

    signal::diagnostic_t const signal{ .size = 8, .init_value = 0 };

    validate::signal::diagnostic::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "size\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_diagnostic_validate, signal_size_error_value)
{
    using namespace lin::ldf;

    signal::diagnostic_t const signal{ .size = 7, .init_value = 0 };

    validate::signal::diagnostic::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "size: Size must be fixed to 8 '7'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_signal_diagnostic_validate, init_value)
{
    using namespace lin::ldf;

    signal::diagnostic_t const signal{ .size = 8, .init_value = 0 };

    validate::signal::diagnostic::init_value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "init_value\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_diagnostic_validate, init_value_error_value)
{
    using namespace lin::ldf;

    signal::diagnostic_t const signal{ .size = 8, .init_value = 0xF };

    validate::signal::diagnostic::init_value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signal);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "init_value: Scalar init value must be zero '15'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_signal_diagnostic_validate, init_value_error_array)
{
    using namespace lin::ldf;

    signal::diagnostic_t const signal{ .size       = 8,
                                       .init_value = signal::diagnostic::init_value::array_t{} };

    validate::signal::diagnostic::init_value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "init_value: Array init value not allowed\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}
