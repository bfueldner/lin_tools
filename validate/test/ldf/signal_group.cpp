#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>
#include <lin/ldf/signal_group.hpp>
#include <lin/ldf/signal_standard.hpp>
#include <lin/ldf/validate/signal_group.hpp>

/* 9.2.3.3 Signal groups */

class test_lin_ldf_signal_group_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ldf_signal_group_validate, size)
{
    using namespace lin::ldf;

    signal::standards_t const signals{};
    signal::group_t const group{ .size = 4 };

    validate::signal::group::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, group);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "size\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_group_validate, size_error_too_low)
{
    using namespace lin::ldf;

    signal::standards_t const signals{};
    signal::group_t const group{ .size = 0 };

    validate::signal::group::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, group);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "size: Value too low '0' (1..64)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_signal_group_validate, size_error_too_high)
{
    using namespace lin::ldf;

    signal::standards_t const signals{};
    signal::group_t const group{ .size = 65 };

    validate::signal::group::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, group);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "size: Value too high '65' (1..64)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_signal_group_validate, signal_sizes)
{
    using namespace lin::ldf;

    signal::standards_t const signals{ signal::standard_t{ .name = "SignalA", .size = 2 },
                                       signal::standard_t{ .name = "SignalB", .size = 4 },
                                       signal::standard_t{ .name = "SignalC", .size = 2 } };
    signal::group_t const group{ .size    = 1,
                                 .signals = {
                                     signal::group::signal_t{ .name = "SignalA", .offset = 0 },
                                     signal::group::signal_t{ .name = "SignalC", .offset = 6 },
                                     signal::group::signal_t{ .name = "SignalB", .offset = 2 } } };

    validate::signal::group::signal_sizes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, group);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signal_sizes\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_group_validate, signal_sizes_empty)
{
    using namespace lin::ldf;

    signal::standards_t const signals{};
    signal::group_t const group{};

    validate::signal::group::signal_sizes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, group);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_group_validate, signal_sizes_warning_space)
{
    using namespace lin::ldf;

    signal::standards_t const signals{ signal::standard_t{ .name = "SignalA", .size = 2 },
                                       signal::standard_t{ .name = "SignalB", .size = 4 },
                                       signal::standard_t{ .name = "SignalC", .size = 2 } };
    signal::group_t const group{ .size    = 2,
                                 .signals = {
                                     signal::group::signal_t{ .name = "SignalC", .offset = 6 },
                                     signal::group::signal_t{ .name = "SignalB", .offset = 2 },
                                     signal::group::signal_t{ .name = "SignalA", .offset = 0 }

                                 } };

    validate::signal::group::signal_sizes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, group);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "signal_sizes: Signals with unused space '8 bit' (16 bit)\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_group_validate, signal_sizes_error_size)
{
    using namespace lin::ldf;

    signal::standards_t const signals{ signal::standard_t{ .name = "SignalA", .size = 2 },
                                       signal::standard_t{ .name = "SignalB", .size = 4 },
                                       signal::standard_t{ .name = "SignalC", .size = 3 } };
    signal::group_t const group{ .size    = 1,
                                 .signals = {
                                     signal::group::signal_t{ .name = "SignalA", .offset = 0 },
                                     signal::group::signal_t{ .name = "SignalB", .offset = 2 },
                                     signal::group::signal_t{ .name = "SignalC", .offset = 6 } } };

    validate::signal::group::signal_sizes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, group);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "signal_sizes: Signals greater than frame '1 bit' (8 bit)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_signal_group_validate, signal_offsets)
{
    using namespace lin::ldf;

    signal::standards_t const signals{ signal::standard_t{ .name = "SignalA", .size = 2 },
                                       signal::standard_t{ .name = "SignalB", .size = 4 },
                                       signal::standard_t{ .name = "SignalC", .size = 2 } };
    signal::group_t const group{ .size    = 1,
                                 .signals = {
                                     signal::group::signal_t{ .name = "SignalA", .offset = 0 },
                                     signal::group::signal_t{ .name = "SignalC", .offset = 6 },
                                     signal::group::signal_t{ .name = "SignalB", .offset = 2 } } };

    validate::signal::group::signal_offsets_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, group);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signal_offsets\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_group_validate, signal_offsets_empty)
{
    using namespace lin::ldf;

    signal::standards_t const signals{};
    signal::group_t const group{};

    validate::signal::group::signal_offsets_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, group);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_group_validate, signal_offsets_error_overlap)
{
    using namespace lin::ldf;

    signal::standards_t const signals{ signal::standard_t{ .name = "SignalA", .size = 2 },
                                       signal::standard_t{ .name = "SignalB", .size = 5 },
                                       signal::standard_t{ .name = "SignalC", .size = 2 },
                                       signal::standard_t{ .name = "SignalD", .size = 1 } };
    signal::group_t const group{ .size    = 1,
                                 .signals = {
                                     signal::group::signal_t{ .name = "SignalD", .offset = 7 },
                                     signal::group::signal_t{ .name = "SignalA", .offset = 0 },
                                     signal::group::signal_t{ .name = "SignalC", .offset = 6 },
                                     signal::group::signal_t{ .name = "SignalB", .offset = 2 } } };

    validate::signal::group::signal_offsets_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, group);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "signal_offsets: Signal overlap 'SignalC, SignalD'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_signal_group_validate, signals)
{
    using namespace lin::ldf;

    signal::standards_t const signals{};
    signal::group_t const group{ .signals = { signal::group::signal_t{ .offset = 0 },
                                              signal::group::signal_t{ .offset = 1 } } };

    validate::signal::group::signals_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, group);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signals\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_group_validate, signals_warning_empty)
{
    using namespace lin::ldf;

    signal::standards_t const signals{};
    signal::group_t const group{ .signals = {} };

    validate::signal::group::signals_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, group);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signals: Empty\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_group_validate, signals_warning_not_sorted)
{
    using namespace lin::ldf;

    signal::standards_t const signals{};
    signal::group_t const group{ .signals = { signal::group::signal_t{ .offset = 1 },
                                              signal::group::signal_t{ .offset = 0 } } };

    validate::signal::group::signals_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, group);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signals: Not sorted\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_group_validate, signal_name)
{
    using namespace lin::ldf;

    signal::standards_t const signals{ signal::standard_t{ .name = "LSMerror" },
                                       signal::standard_t{ .name = "RSMerror" } };
    signal::group::signal_t const group{ .name = "LSMerror" };

    validate::signal::group::signal::name_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, group);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "name\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_group_validate, signal_name_error_not_defined)
{
    using namespace lin::ldf;

    signal::standards_t const signals{ signal::standard_t{ .name = "RSMerror" } };
    signal::group::signal_t const group{ .name = "LSMerror" };

    validate::signal::group::signal::name_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, group);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "name: Not defined 'LSMerror'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_signal_group_validate, signal_offset)
{
    using namespace lin::ldf;

    signal::standards_t const signals{};
    signal::group::signal_t const group{ .offset = 0 };

    validate::signal::group::signal::offset_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, group);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "offset\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_group_validate, signal_offset_error_too_low)
{
    using namespace lin::ldf;

    signal::standards_t const signals{};
    signal::group::signal_t const group{ .offset = -1 };

    validate::signal::group::signal::offset_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, group);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "offset: Value too low '-1' (0..63)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_signal_group_validate, signal_offset_error_too_high)
{
    using namespace lin::ldf;

    signal::standards_t const signals{};
    signal::group::signal_t const group{ .offset = 64 };

    validate::signal::group::signal::offset_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, group);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "offset: Value too high '64' (0..63)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}
