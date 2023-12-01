#include <gtest/gtest.h>

#include <lin/ncf/general.hpp>

#include <lin/common/validate/logger.hpp>
#include <lin/ncf/validate/general.hpp>

/* 8.2.3 General definition */

class test_lin_ncf_general_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ncf_general_validate, protocol_version_1)
{
    using namespace lin::ncf;

    general_t const general{ .protocol_version = "1.3" };

    validate::general::protocol_version_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "protocol_version\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_general_validate, protocol_version_2)
{
    using namespace lin::ncf;

    general_t const general{ .protocol_version = "2.2" };

    validate::general::protocol_version_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "protocol_version\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_general_validate, protocol_version_error_not_supported)
{
    using namespace lin::ncf;

    general_t const general{ .protocol_version = "2.4" };

    validate::general::protocol_version_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "protocol_version: Protocol version not supported '2.4' (<= 2.2)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_general_validate, supplier)
{
    using namespace lin::ncf;

    general_t const general{ .supplier = 0x1234 };

    validate::general::supplier_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "supplier\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_general_validate, supplier_error_too_low)
{
    using namespace lin::ncf;

    general_t const general{ .supplier = -1 };

    validate::general::supplier_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "supplier: Value too low '-1' (0..65535)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_general_validate, supplier_error_too_high)
{
    using namespace lin::ncf;

    general_t const general{ .supplier = 0x10000 };

    validate::general::supplier_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "supplier: Value too high '65536' (0..65535)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_general_validate, function)
{
    using namespace lin::ncf;

    general_t const general{ .function = 0x1234 };

    validate::general::function_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "function\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_general_validate, function_error_too_low)
{
    using namespace lin::ncf;

    general_t const general{ .function = -1 };

    validate::general::function_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "function: Value too low '-1' (0..65535)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_general_validate, function_error_too_high)
{
    using namespace lin::ncf;

    general_t const general{ .function = 0x10000 };

    validate::general::function_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "function: Value too high '65536' (0..65535)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_general_validate, variant)
{
    using namespace lin::ncf;

    general_t const general{ .variant = 127 };

    validate::general::variant_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "variant\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_general_validate, variant_error_too_low)
{
    using namespace lin::ncf;

    general_t const general{ .variant = -1 };

    validate::general::variant_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "variant: Value too low '-1' (0..255)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_general_validate, variant_error_too_high)
{
    using namespace lin::ncf;

    general_t const general{ .variant = 0x100 };

    validate::general::variant_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "variant: Value too high '256' (0..255)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_general_validate, bitrate_automatic)
{
    using namespace lin::ncf;

    general_t const general{ .bitrate = general::bitrate::automatic_t{
                                 .min = general::bitrate::kbps_t{ 4.8 },
                                 .max = general::bitrate::kbps_t{ 19.2 } } };

    validate::general::bitrate_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "bitrate\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_general_validate, bitrate_automatic_error_too_low)
{
    using namespace lin::ncf;

    general_t const general{ .bitrate = general::bitrate::automatic_t{
                                 .min = general::bitrate::kbps_t{ 0.6 },
                                 .max = general::bitrate::kbps_t{ 19.2 } } };

    validate::general::bitrate_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "bitrate: Minimum value too low '0.6 kbps' (1 kbps..20 kbps)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_general_validate, bitrate_automatic_error_too_high)
{
    using namespace lin::ncf;

    general_t const general{ .bitrate = general::bitrate::automatic_t{
                                 .min = general::bitrate::kbps_t{ 4.8 },
                                 .max = general::bitrate::kbps_t{ 38.4 } } };

    validate::general::bitrate_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "bitrate: Maximum value too high '38.4 kbps' (1 kbps..20 kbps)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_general_validate, bitrate_automatic_error_range)
{
    using namespace lin::ncf;

    general_t const general{ .bitrate = general::bitrate::automatic_t{
                                 .min = general::bitrate::kbps_t{ 19.2 },
                                 .max = general::bitrate::kbps_t{ 4.8 } } };

    validate::general::bitrate_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "bitrate: Range invalid '19.2 kbps..4.8 kbps' (1 kbps..20 kbps < 1 kbps..20 kbps)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_general_validate, bitrate_select)
{
    using namespace lin::ncf;

    general_t const general{ .bitrate =
                                 general::bitrate::select_t{ general::bitrate::kbps_t{ 4.8 },
                                                             general::bitrate::kbps_t{ 9.6 },
                                                             general::bitrate::kbps_t{ 19.2 } } };

    validate::general::bitrate_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "bitrate\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_general_validate, bitrate_select_warning_order)
{
    using namespace lin::ncf;

    general_t const general{ .bitrate =
                                 general::bitrate::select_t{ general::bitrate::kbps_t{ 19.2 },
                                                             general::bitrate::kbps_t{ 4.8 },
                                                             general::bitrate::kbps_t{ 9.6 } } };

    validate::general::bitrate_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "bitrate: Member order '19.2 kbps, 4.8 kbps, 9.6 kbps' (4.8 kbps, 9.6 kbps, 19.2 kbps)\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_general_validate, bitrate_select_error_too_low)
{
    using namespace lin::ncf;

    general_t const general{ .bitrate =
                                 general::bitrate::select_t{ general::bitrate::kbps_t{ 0.6 },
                                                             general::bitrate::kbps_t{ 1.2 },
                                                             general::bitrate::kbps_t{ 2.4 } } };

    validate::general::bitrate_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "bitrate: Member out of range '0.6 kbps' (1 kbps..20 kbps)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_general_validate, bitrate_select_error_too_high)
{
    using namespace lin::ncf;

    general_t const general{ .bitrate =
                                 general::bitrate::select_t{ general::bitrate::kbps_t{ 9.6 },
                                                             general::bitrate::kbps_t{ 19.2 },
                                                             general::bitrate::kbps_t{ 38.4 } } };

    validate::general::bitrate_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "bitrate: Member out of range '38.4 kbps' (1 kbps..20 kbps)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_general_validate, bitrate_select_error_equal)
{
    using namespace lin::ncf;

    general_t const general{ .bitrate =
                                 general::bitrate::select_t{ general::bitrate::kbps_t{ 4.8 },
                                                             general::bitrate::kbps_t{ 9.6 },
                                                             general::bitrate::kbps_t{ 9.6 },
                                                             general::bitrate::kbps_t{ 19.2 } } };

    validate::general::bitrate_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "bitrate: Member equal '9.6 kbps'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_general_validate, bitrate_fixed)
{
    using namespace lin::ncf;

    general_t const general{ .bitrate = general::bitrate::fixed_t{ 9.6 } };

    validate::general::bitrate_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "bitrate\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_general_validate, bitrate_fixed_error_too_low)
{
    using namespace lin::ncf;

    general_t const general{ .bitrate = general::bitrate::fixed_t{ 0.9 } };

    validate::general::bitrate_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "bitrate: Value too low '0.9 kbps' (1 kbps..20 kbps)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_general_validate, bitrate_fixed_error_too_high)
{
    using namespace lin::ncf;

    general_t const general{ .bitrate = general::bitrate::fixed_t{ 20.1 } };

    validate::general::bitrate_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(general);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "bitrate: Value too high '20.1 kbps' (1 kbps..20 kbps)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}
