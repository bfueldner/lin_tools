#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>
#include <lin/ncf/frame.hpp>
#include <lin/ncf/signal.hpp>
#include <lin/ncf/status_management.hpp>
#include <lin/ncf/validate/status_management.hpp>

/* 8.2.6 Status management */

class test_lin_ncf_status_management_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ncf_status_management_validate, response_error)
{
    using namespace lin::ncf;

    frames_t const frames{ frame_t{ .kind    = frame::kind_t::publish,
                                    .signals = { signal_t{ .name = "abc" } } } };
    status_management_t const status_management{ .response_error = "abc" };

    validate::status_management::response_error_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frames, status_management);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "response_error\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_status_management_validate, response_error_error_signal_not_found)
{
    using namespace lin::ncf;

    frames_t const frames{ frame_t{ .kind    = frame::kind_t::subscribe,
                                    .signals = { signal_t{ .name = "abc" } } } };
    status_management_t const status_management{ .response_error = "abc" };

    validate::status_management::response_error_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frames, status_management);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "response_error: Not defined 'abc'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_status_management_validate, fault_state_signals)
{
    using namespace lin::ncf;

    frames_t const frames{
        frame_t{ .kind = frame::kind_t::publish, .signals = { signal_t{ .name = "abc" } } },
        frame_t{ .kind = frame::kind_t::subscribe, .signals = { signal_t{ .name = "ghi" } } },
        frame_t{ .kind = frame::kind_t::publish, .signals = { signal_t{ .name = "def" } } }
    };
    status_management_t const status_management{ .fault_state_signals = { "abc", "def" } };

    validate::status_management::fault_state_signals_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frames, status_management);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "fault_state_signals\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_status_management_validate, fault_state_signals_error_not_found)
{
    using namespace lin::ncf;

    frames_t const frames{};
    status_management_t const status_management{ .fault_state_signals = { "abc", "def" } };

    validate::status_management::fault_state_signals_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frames, status_management);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "fault_state_signals: Not defined 'abc, def'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_status_management_validate, fault_state_signals_error_duplicate_entry)
{
    using namespace lin::ncf;

    frames_t const frames{
        frame_t{ .kind = frame::kind_t::publish, .signals = { signal_t{ .name = "abc" } } },
        frame_t{ .kind = frame::kind_t::publish, .signals = { signal_t{ .name = "def" } } }
    };
    status_management_t const status_management{ .fault_state_signals = { "abc", "abc" } };

    validate::status_management::fault_state_signals_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(frames, status_management);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "fault_state_signals: Duplicate entry 'abc'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}
