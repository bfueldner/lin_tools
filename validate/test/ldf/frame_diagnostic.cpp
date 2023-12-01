#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>
#include <lin/ldf/frame_diagnostic.hpp>
#include <lin/ldf/signal_diagnostic.hpp>
#include <lin/ldf/validate/frame_diagnostic.hpp>

/* 9.2.4.4 Diagnostic frames */

class test_lin_ldf_frame_diagnostic_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ldf_frame_diagnostic_validate, id_master_request)
{
    using namespace lin::ldf;

    frame::diagnostic_t const frame{ .id = 0x3C };

    validate::frame::diagnostic::id_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "id\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_diagnostic_validate, id_slave_response)
{
    using namespace lin::ldf;

    frame::diagnostic_t const frame{ .id = 0x3D };

    validate::frame::diagnostic::id_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "id\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_diagnostic_validate, id_error_too_low)
{
    using namespace lin::ldf;

    frame::diagnostic_t const frame{ .id = 0x3B };

    validate::frame::diagnostic::id_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "id: Value too low '59' (60..61)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_frame_diagnostic_validate, id_error_too_high)
{
    using namespace lin::ldf;

    frame::diagnostic_t const frame{ .id = 0x3E };

    validate::frame::diagnostic::id_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "id: Value too high '62' (60..61)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_frame_diagnostic_validate, signals)
{
    using namespace lin::ldf;

    frame::diagnostic_t const frame{ .signals = { frame::diagnostic::signal_t{ .offset = 0 },
                                                  frame::diagnostic::signal_t{ .offset = 8 } } };

    validate::frame::diagnostic::signals_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signals\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_diagnostic_validate, signals_warning_empty)
{
    using namespace lin::ldf;

    frame::diagnostic_t const frame{};

    validate::frame::diagnostic::signals_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signals: Empty\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_diagnostic_validate, signals_warning_not_sorted)
{
    using namespace lin::ldf;

    frame::diagnostic_t const frame{ .signals = { frame::diagnostic::signal_t{ .offset = 8 },
                                                  frame::diagnostic::signal_t{ .offset = 0 } } };

    validate::frame::diagnostic::signals_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frame);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signals: Not sorted\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_diagnostic_validate, signal_name)
{
    using namespace lin::ldf;

    signal::diagnostics_t const signals{ signal::diagnostic_t{ .name = "MasterReqB0" },
                                         signal::diagnostic_t{ .name = "MasterReqB1" },
                                         signal::diagnostic_t{ .name = "MasterReqB2" },
                                         signal::diagnostic_t{ .name = "MasterReqB3" } };
    frame::diagnostic::signal_t const signal{ .name = "MasterReqB0" };

    validate::frame::diagnostic::signal::name_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "name\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_diagnostic_validate, signal_name_error_not_defined)
{
    using namespace lin::ldf;

    signal::diagnostics_t const signals{ signal::diagnostic_t{ .name = "MasterReqB0" },
                                         signal::diagnostic_t{ .name = "MasterReqB1" },
                                         signal::diagnostic_t{ .name = "MasterReqB2" },
                                         signal::diagnostic_t{ .name = "MasterReqB3" } };
    frame::diagnostic::signal_t const signal{ .name = "SlaveRespB0" };

    validate::frame::diagnostic::signal::name_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "name: Not defined 'SlaveRespB0'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_frame_diagnostic_validate, signal_offset)
{
    using namespace lin::ldf;

    signal::diagnostics_t const signals{};
    frame::diagnostic::signal_t const signal{ .offset = 8 };

    validate::frame::diagnostic::signal::offset_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "offset\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_frame_diagnostic_validate, signal_offset_error_too_low)
{
    using namespace lin::ldf;

    signal::diagnostics_t const signals{};
    frame::diagnostic::signal_t const signal{ .offset = -1 };

    validate::frame::diagnostic::signal::offset_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "offset: Value too low '-1' (0..63)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_frame_diagnostic_validate, signal_offset_error_too_high)
{
    using namespace lin::ldf;

    signal::diagnostics_t const signals{};
    frame::diagnostic::signal_t const signal{ .offset = 64 };

    validate::frame::diagnostic::signal::offset_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "offset: Value too high '64' (0..63)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_frame_diagnostic_validate, signal_offset_error_not_aligned)
{
    using namespace lin::ldf;

    signal::diagnostics_t const signals{};
    frame::diagnostic::signal_t const signal{ .offset = 63 };

    validate::frame::diagnostic::signal::offset_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(signals, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "offset: Value not byte aligned '63' (56)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}
