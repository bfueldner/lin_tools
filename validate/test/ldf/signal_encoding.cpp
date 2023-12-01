#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>
#include <lin/ldf/signal_encoding.hpp>
#include <lin/ldf/signal_representation.hpp>
#include <lin/ldf/signal_standard.hpp>
#include <lin/ldf/validate/signal_encoding.hpp>

/* 9.2.6.1 Signal encoding type definition */

class test_lin_ldf_signal_encoding_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ldf_signal_encoding_validate, usage)
{
    using namespace lin::ldf;

    signal::standards_t const signals{};
    signal::representations_t const representations{ signal::representation_t{ .name = "Dig2Bit" },
                                                     signal::representation_t{
                                                         .name = "LightEncoding" } };
    signal::encoding_t const encoding{ .name = "Dig2Bit" };

    validate::signal::encoding::usage_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, representations, encoding);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "usage\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_encoding_validate, usage_warning_not_used)
{
    using namespace lin::ldf;

    signal::standards_t const signals{};
    signal::representations_t const representations{ signal::representation_t{ .name = "Dig2Bit" },
                                                     signal::representation_t{
                                                         .name = "LightEncoding" } };
    signal::encoding_t const encoding{ .name = "ErrorEncoding" };

    validate::signal::encoding::usage_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, representations, encoding);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "usage: Not used\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_encoding_validate, size)
{
    using namespace lin::ldf;

    signal::standards_t const signals{ signal::standard_t{ .name = "InternalLightsRequest",
                                                           .size = 2 } };
    signal::representations_t const representations{
        signal::representation_t{ .name = "Dig2Bit", .signals = { "InternalLightsRequest" } },
        signal::representation_t{ .name = "LightEncoding" }
    };
    signal::encoding_t const encoding{
        .name   = "Dig2Bit",
        .values = { signal::encoding::logical_value_t{ .value = 0, .text_info = "off" },
                    signal::encoding::logical_value_t{ .value = 1, .text_info = "on" },
                    signal::encoding::logical_value_t{ .value = 2, .text_info = "error" },
                    signal::encoding::logical_value_t{ .value = 3, .text_info = "void" } }
    };

    validate::signal::encoding::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, representations, encoding);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "size\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_encoding_validate, size_warning_unused_undefined_end)
{
    using namespace lin::ldf;

    signal::standards_t const signals{ signal::standard_t{ .name = "InternalLightsRequest",
                                                           .size = 3 } };
    signal::representations_t const representations{
        signal::representation_t{ .name = "Dig2Bit", .signals = { "InternalLightsRequest" } },
        signal::representation_t{ .name = "LightEncoding" }
    };
    signal::encoding_t const encoding{
        .name   = "Dig2Bit",
        .values = { signal::encoding::logical_value_t{ .value = 0, .text_info = "off" },
                    signal::encoding::logical_value_t{ .value = 1, .text_info = "on" },
                    signal::encoding::logical_value_t{ .value = 2, .text_info = "error" },
                    signal::encoding::logical_value_t{ .value = 3, .text_info = "void" } }
    };

    validate::signal::encoding::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, representations, encoding);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "size: Encoding smaller than signal 'InternalLightsRequest'\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_encoding_validate, size_error_too_high)
{
    using namespace lin::ldf;

    signal::standards_t const signals{ signal::standard_t{ .name = "InternalLightsRequest",
                                                           .size = 1 } };
    signal::representations_t const representations{
        signal::representation_t{ .name = "Dig2Bit", .signals = { "InternalLightsRequest" } },
        signal::representation_t{ .name = "LightEncoding" }
    };
    signal::encoding_t const encoding{
        .name   = "Dig2Bit",
        .values = { signal::encoding::logical_value_t{ .value = 0, .text_info = "off" },
                    signal::encoding::logical_value_t{ .value = 1, .text_info = "on" },
                    signal::encoding::logical_value_t{ .value = 2, .text_info = "error" },
                    signal::encoding::logical_value_t{ .value = 3, .text_info = "void" } }
    };

    validate::signal::encoding::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, representations, encoding);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "size: Encoding bigger than signal 'InternalLightsRequest'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}
