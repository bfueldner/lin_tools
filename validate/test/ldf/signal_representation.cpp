#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>
#include <lin/ldf/signal_encoding.hpp>
#include <lin/ldf/signal_representation.hpp>
#include <lin/ldf/signal_standard.hpp>
#include <lin/ldf/validate/signal_representation.hpp>

/* 9.2.6.2 Signal representation definition */

class test_lin_ldf_signal_representation_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ldf_signal_representation_validate, encoding)
{
    using namespace lin::ldf;

    signal::encodings_t const encodings{ signal::encoding_t{ .name = "Dig2Bit" } };
    signal::standards_t const signals{};
    signal::representation_t const representation{ .name = "Dig2Bit" };

    validate::signal::representation::encoding_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(encodings, signals, representation);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "encoding\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_representation_validate, encoding_error_not_defined)
{
    using namespace lin::ldf;

    signal::encodings_t const encodings{ signal::encoding_t{ .name = "Dig2Bit" } };
    signal::standards_t const signals{};
    signal::representation_t const representation{ .name = "ErrorEncoding" };

    validate::signal::representation::encoding_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(encodings, signals, representation);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "encoding: Not defined 'ErrorEncoding'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_signal_representation_validate, signals)
{
    using namespace lin::ldf;

    signal::encodings_t const encodings{};
    signal::standards_t const signals{ signal::standard_t{ .name = "LSMerror" },
                                       signal::standard_t{ .name = "RSMerror" } };
    signal::representation_t const representation{ .name    = "ErrorEncoding",
                                                   .signals = { "RSMerror", "LSMerror" } };

    validate::signal::representation::signals_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(encodings, signals, representation);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signals\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_representation_validate, signals_warning_empty)
{
    using namespace lin::ldf;

    signal::encodings_t const encodings{};
    signal::standards_t const signals{};
    signal::representation_t const representation{ .name = "LightEncoding", .signals = {} };

    validate::signal::representation::signals_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(encodings, signals, representation);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signals: Empty\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_representation_validate, signals_error_not_defined)
{
    using namespace lin::ldf;

    signal::encodings_t const encodings{};
    signal::standards_t const signals{ signal::standard_t{ .name = "LSMerror" },
                                       signal::standard_t{ .name = "RSMerror" } };
    signal::representation_t const representation{
        .name = "LightEncoding", .signals = { "RightIntLightsSwitch", "LefttIntLightsSwitch" }
    };

    validate::signal::representation::signals_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(encodings, signals, representation);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "signals: Not defined 'RightIntLightsSwitch, LefttIntLightsSwitch'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_signal_representation_validate, signals_error_duplicate_entry)
{
    using namespace lin::ldf;

    signal::encodings_t const encodings{};
    signal::standards_t const signals{ signal::standard_t{ .name = "LSMerror" },
                                       signal::standard_t{ .name = "RSMerror" } };
    signal::representation_t const representation{
        .name = "ErrorEncoding", .signals = { "RSMerror", "LSMerror", "RSMerror" }
    };

    validate::signal::representation::signals_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(encodings, signals, representation);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signals: Duplicate entry 'RSMerror'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}
