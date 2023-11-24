#include <gtest/gtest.h>

#include <lin/common/signal_encoding.hpp>
#include <lin/common/validate/logger.hpp>
#include <lin/common/validate/signal_encoding.hpp>

/* Common signal encoding type definition */

class test_lin_common_signal_encoding_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_common_signal_encoding_validate, types_logical_physical_value)
{
    using namespace lin::common;

    signal::encoding_t const encoding{
        .values = { signal::encoding::logical_value_t{ .value = 0 },
                    signal::encoding::physical_range_t{ .min = 1, .max = 127 },
                    signal::encoding::logical_value_t{ .value = 128 },
                    signal::encoding::physical_range_t{ .min = 129, .max = 254 },
                    signal::encoding::logical_value_t{ .value = 255 } }
    };

    validate::signal::encoding::types_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(encoding);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "types\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_common_signal_encoding_validate, types_ascii_value)
{
    using namespace lin::common;

    signal::encoding_t const encoding{ .values = { signal::encoding::ascii_value_t{} } };

    validate::signal::encoding::types_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(encoding);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "types\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_common_signal_encoding_validate, types_bcd_value)
{
    using namespace lin::common;

    signal::encoding_t const encoding{ .values = { signal::encoding::bcd_value_t{} } };

    validate::signal::encoding::types_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(encoding);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "types\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_common_signal_encoding_validate, types_ascii_value_error_mixed)
{
    using namespace lin::common;

    signal::encoding_t const encoding{ .values = { signal::encoding::ascii_value_t{},
                                                   signal::encoding::bcd_value_t{} } };

    validate::signal::encoding::types_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(encoding);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "types: ASCII encoding can not be mixed with other encodings\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_common_signal_encoding_validate, types_bcd_value_error_mixed)
{
    using namespace lin::common;

    signal::encoding_t const encoding{ .values = { signal::encoding::bcd_value_t{},
                                                   signal::encoding::logical_value_t{},
                                                   signal::encoding::physical_range_t{} } };

    validate::signal::encoding::types_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(encoding);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "types: BCD encoding can not be mixed with other encodings\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_common_signal_encoding_validate, values)
{
    using namespace lin::common;

    signal::encoding_t const encoding{
        .name   = "Dig2Bit",
        .values = { signal::encoding::logical_value_t{ .value = 0 },
                    signal::encoding::physical_range_t{ .min = 1, .max = 127 },
                    signal::encoding::logical_value_t{ .value = 128 },
                    signal::encoding::physical_range_t{ .min = 129, .max = 254 },
                    signal::encoding::logical_value_t{ .value = 255 } }
    };

    validate::signal::encoding::values_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(encoding);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "values\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_common_signal_encoding_validate, values_warning_empty)
{
    using namespace lin::common;

    signal::encoding_t const encoding{};

    validate::signal::encoding::values_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(encoding);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "values: Empty\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_common_signal_encoding_validate, values_warning_undefined_begin)
{
    using namespace lin::common;

    signal::encoding_t const encoding{ .values = {
                                           signal::encoding::logical_value_t{ .value = 3 },
                                           signal::encoding::logical_value_t{ .value = 2 },
                                           signal::encoding::logical_value_t{ .value = 1 } } };

    validate::signal::encoding::values_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(encoding);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "values: Not all values defined\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_common_signal_encoding_validate, values_warning_undefined_middle)
{
    using namespace lin::common;

    signal::encoding_t const encoding{ .values = {
                                           signal::encoding::logical_value_t{ .value = 0 },
                                           signal::encoding::logical_value_t{ .value = 2 } } };

    validate::signal::encoding::values_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(encoding);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "values: Not all values defined\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_common_signal_encoding_validate, values_warning_not_sorted)
{
    using namespace lin::common;

    signal::encoding_t const encoding{ .values = {
                                           signal::encoding::logical_value_t{ .value = 2 },
                                           signal::encoding::logical_value_t{ .value = 1 },
                                           signal::encoding::logical_value_t{ .value = 0 } } };

    validate::signal::encoding::values_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(encoding);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "values: Not sorted\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_common_signal_encoding_validate, values_error_logic_value_overlap)
{
    using namespace lin::common;

    signal::encoding_t const encoding{
        .values = { signal::encoding::logical_value_t{ .value = 0 },
                    signal::encoding::logical_value_t{ .value = 127 },
                    signal::encoding::physical_range_t{ .min = 1, .max = 127 } }
    };

    validate::signal::encoding::values_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(encoding);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "values: Value or range overlap '127'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_common_signal_encoding_validate, values_error_physical_range_overlap)
{
    using namespace lin::common;

    signal::encoding_t const encoding{
        .values = { signal::encoding::logical_value_t{ .value = 1 },
                    signal::encoding::physical_range_t{ .min = 1, .max = 127 },
                    signal::encoding::logical_value_t{ .value = 0 } }
    };

    validate::signal::encoding::values_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(encoding);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "values: Value or range overlap '1'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}


TEST_F(test_lin_common_signal_encoding_validate, value_logical_value)
{
    using namespace lin::common;

    signal::encoding::value_t const value{ signal::encoding::logical_value_t{ .value = 0 } };

    validate::signal::encoding::value::value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(value);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "value\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_common_signal_encoding_validate, value_logical_value_error_too_low)
{
    using namespace lin::common;

    signal::encoding::value_t const value{ signal::encoding::logical_value_t{ .value = -1 } };

    validate::signal::encoding::value::value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(value);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "value: Value too low '-1' (>= 0)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_common_signal_encoding_validate, value_physical_range)
{
    using namespace lin::common;

    signal::encoding::value_t const value{ signal::encoding::physical_range_t{ .min = 0,
                                                                               .max = 255 } };

    validate::signal::encoding::value::value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(value);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "value\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_common_signal_encoding_validate, value_physical_range_error_too_low)
{
    using namespace lin::common;

    signal::encoding::value_t const value{ signal::encoding::physical_range_t{ .min = -1 } };

    validate::signal::encoding::value::value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(value);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "value: Minimum value too low '-1' (>= 0)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_common_signal_encoding_validate, value_physical_range_error_equel)
{
    using namespace lin::common;

    signal::encoding::value_t const value{ signal::encoding::physical_range_t{ .min = 1,
                                                                               .max = 1 } };

    validate::signal::encoding::value::value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(value);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "value: Range invalid '1..1'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_common_signal_encoding_validate, value_physical_range_error_inverse)
{
    using namespace lin::common;

    signal::encoding::value_t const value{ signal::encoding::physical_range_t{ .min = 10,
                                                                               .max = 1 } };

    validate::signal::encoding::value::value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(value);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "value: Range invalid '10..1'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_common_signal_encoding_validate, value_ascii_value)
{
    using namespace lin::common;

    signal::encoding::value_t const value{ signal::encoding::ascii_value_t{} };

    validate::signal::encoding::value::value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(value);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "value\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_common_signal_encoding_validate, value_bcd_value)
{
    using namespace lin::common;

    signal::encoding::value_t const value{ signal::encoding::bcd_value_t{} };

    validate::signal::encoding::value::value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(value);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "value\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}


TEST_F(test_lin_common_signal_encoding_validate, value_text_info_logical_value)
{
    using namespace lin::common;

    signal::encoding::value_t const value{ signal::encoding::logical_value_t{
        .text_info = "text" } };

    validate::signal::encoding::value::text_info_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(value);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "text_info\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_common_signal_encoding_validate, value_text_info_physical_range)
{
    using namespace lin::common;

    signal::encoding::value_t const value{ signal::encoding::physical_range_t{
        .text_info = "text" } };

    validate::signal::encoding::value::text_info_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(value);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "text_info\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_common_signal_encoding_validate, value_text_info_ascii_value)
{
    using namespace lin::common;

    signal::encoding::value_t const value{ signal::encoding::ascii_value_t{} };

    validate::signal::encoding::value::text_info_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(value);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "text_info\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_common_signal_encoding_validate, value_text_info_bcd_value)
{
    using namespace lin::common;

    signal::encoding::value_t const value{ signal::encoding::bcd_value_t{} };

    validate::signal::encoding::value::text_info_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(value);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "text_info\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_common_signal_encoding_validate, value_text_info_logical_value_warning_empty)
{
    using namespace lin::common;

    signal::encoding::value_t const value{ signal::encoding::logical_value_t{} };

    validate::signal::encoding::value::text_info_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(value);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "text_info: Empty\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_common_signal_encoding_validate, value_text_info_physical_range_warning_empty)
{
    using namespace lin::common;

    signal::encoding::value_t const value{ signal::encoding::physical_range_t{} };

    validate::signal::encoding::value::text_info_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(value);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "text_info: Empty\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}
