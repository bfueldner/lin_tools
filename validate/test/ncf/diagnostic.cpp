#include <gtest/gtest.h>

#include <lin/ncf/diagnostic.hpp>

#include <lin/common/validate/logger.hpp>
#include <lin/ncf/validate/diagnostic.hpp>

/* 8.2.4 Diagnostic definition */

class test_lin_ncf_diagnostic_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ncf_diagnostic_validate, nad_range)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ diagnostic::nad::range_t{ 1, 2 } };

    validate::diagnostic::nad_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "nad\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_diagnostic_validate, nad_range_error_too_low)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ diagnostic::nad::range_t{ 0, 1 } };

    validate::diagnostic::nad_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "nad: Minimum value too low '0' (1..125)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_diagnostic_validate, nad_range_error_equal)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ diagnostic::nad::range_t{ 1, 1 } };

    validate::diagnostic::nad_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "nad: Range invalid '1..1' (1..125 < 1..125)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_diagnostic_validate, nad_range_error_inverse)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ diagnostic::nad::range_t{ 100, 10 } };

    validate::diagnostic::nad_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "nad: Range invalid '100..10' (1..125 < 1..125)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_diagnostic_validate, nad_range_error_too_high)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ diagnostic::nad::range_t{ 1, 126 } };

    validate::diagnostic::nad_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "nad: Maximum value too high '126' (1..125)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_diagnostic_validate, nad_sequence)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ diagnostic::nad::sequence_t{ 1, 2, 3 } };

    validate::diagnostic::nad_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "nad\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_diagnostic_validate, nad_sequence_warning_order)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ diagnostic::nad::sequence_t{ 3, 2, 1 } };

    validate::diagnostic::nad_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "nad: Member order '3, 2, 1' (1, 2, 3)\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_diagnostic_validate, nad_sequence_error_too_low)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ diagnostic::nad::sequence_t{ 0, 1, 2 } };

    validate::diagnostic::nad_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "nad: Member out of range '0' (1..125)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_diagnostic_validate, nad_sequence_error_too_high)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ diagnostic::nad::sequence_t{ 124, 125, 126 } };

    validate::diagnostic::nad_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "nad: Member out of range '126' (1..125)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_diagnostic_validate, nad_sequence_error_equal)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ diagnostic::nad::sequence_t{ 5, 5 } };

    validate::diagnostic::nad_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "nad: Member equal '5'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_diagnostic_validate, diagnostic_class)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ .diagnostic_class = 1 };

    validate::diagnostic::diagnostic_class_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "diagnostic_class\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_diagnostic_validate, diagnostic_class_error_too_low)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ .diagnostic_class = 0 };

    validate::diagnostic::diagnostic_class_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "diagnostic_class: Value too low '0' (1..3)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_diagnostic_validate, diagnostic_class_error_too_high)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ .diagnostic_class = 4 };

    validate::diagnostic::diagnostic_class_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "diagnostic_class: Value too high '4' (1..3)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_diagnostic_validate, p2_min)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ .p2_min = 1000 };

    validate::diagnostic::p2_min_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "p2_min\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_diagnostic_validate, p2_min_error_too_low)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ .p2_min = -1 };

    validate::diagnostic::p2_min_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "p2_min: Value too low '-1' (>= 0)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_diagnostic_validate, st_min)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ .st_min = 1000 };

    validate::diagnostic::st_min_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "st_min\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_diagnostic_validate, st_min_error_too_low)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ .st_min = -1 };

    validate::diagnostic::st_min_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "st_min: Value too low '-1' (>= 0)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_diagnostic_validate, n_as_timeout)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ .n_as_timeout = 1000 };

    validate::diagnostic::n_as_timeout_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "n_as_timeout\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_diagnostic_validate, n_as_timeout_error_too_low)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ .n_as_timeout = -1 };

    validate::diagnostic::n_as_timeout_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "n_as_timeout: Value too low '-1' (>= 0)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_diagnostic_validate, n_cr_timeout)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ .n_cr_timeout = 1000 };

    validate::diagnostic::n_cr_timeout_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "n_cr_timeout\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_diagnostic_validate, n_cr_timeout_error_too_low)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ .n_cr_timeout = -1 };

    validate::diagnostic::n_cr_timeout_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "n_cr_timeout: Value too low '-1' (>= 0)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_diagnostic_validate, support_sid)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ diagnostic::nad::sequence_t{ 1, 2, 3 } };

    validate::diagnostic::support_sid_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "support_sid\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_diagnostic_validate, support_sid_warning_order)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ .support_sids = { 3, 1, 2 } };

    validate::diagnostic::support_sid_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "support_sid: Member order '3, 1, 2' (1, 2, 3)\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_diagnostic_validate, support_sid_error_too_low)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ .support_sids = { -1, 0, 1 } };

    validate::diagnostic::support_sid_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "support_sid: Member out of range '-1' (0..255)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_diagnostic_validate, support_sid_error_too_high)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ .support_sids = { 254, 255, 256, 257 } };

    validate::diagnostic::support_sid_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "support_sid: Member out of range '256, 257' (0..255)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_diagnostic_validate, support_sid_error_equal)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ .support_sids = { 5, 5 } };

    validate::diagnostic::support_sid_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "support_sid: Member equal '5'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_diagnostic_validate, max_message_length)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ .max_message_length = 64 };

    validate::diagnostic::max_message_length_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "max_message_length\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_diagnostic_validate, max_message_length_error_too_low)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{ .max_message_length = 0 };

    validate::diagnostic::max_message_length_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(diagnostic);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "max_message_length: Value too low '0' (>= 1)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}
