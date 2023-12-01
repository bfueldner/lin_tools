#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>
#include <lin/ncf/diagnostic.hpp>
#include <lin/ncf/frame.hpp>
#include <lin/ncf/free_text.hpp>
#include <lin/ncf/general.hpp>
#include <lin/ncf/node.hpp>
#include <lin/ncf/node_capability_file.hpp>
#include <lin/ncf/signal.hpp>
#include <lin/ncf/signal_encoding.hpp>
#include <lin/ncf/status_management.hpp>
#include <lin/ncf/validate/node_capability_file.hpp>

/* 8.2 Node capability file definition */

class test_lin_ncf_node_capability_file_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

/* 8.2.1 Global definition */

TEST_F(test_lin_ncf_node_capability_file_validate, language_version)
{
    using namespace lin::ncf;

    node_capability_file_t const ncf{ .language_version = "2.2" };

    validate::node_capability_file::language_version_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(ncf);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "language_version\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_node_capability_file_validate, language_version_warning)
{
    using namespace lin::ncf;

    node_capability_file_t const ncf{ .language_version = "1.5" };

    validate::node_capability_file::language_version_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(ncf);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "language_version: Language version supported, but deprecated '1.5'\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_node_capability_file_validate, language_version_error)
{
    using namespace lin::ncf;

    node_capability_file_t const ncf{ .language_version = "2.4" };

    validate::node_capability_file::language_version_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(ncf);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "language_version: Language version not supported '2.4' (<= 2.2)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_node_capability_file_validate, node_names)
{
    using namespace lin::ncf;

    node_capability_file_t const ncf{ .nodes = { node_t{ .name = "abc" },
                                                 node_t{ .name = "def" } } };

    validate::node_capability_file::node_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(ncf);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "node_names\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_node_capability_file_validate, node_names_error_not_unique)
{
    using namespace lin::ncf;

    node_capability_file_t const ncf{ .nodes = { node_t{ .name = "abc" },
                                                 node_t{ .name = "abc" } } };

    validate::node_capability_file::node_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(ncf);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "node_names: Names not unique 'abc'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

/* 8.2 Node capability file definition */

TEST_F(test_lin_ncf_node_capability_file_validate, complete)
{
    using namespace lin::ncf;

    node_capability_file_t const ncf{
        .language_version = "2.2",
        .nodes            = nodes_t{ node_t{
                       .name = "step_motor",
                       .general =
                general_t{
                               .protocol_version = "2.2",
                               .supplier         = 0x05,
                               .function         = 0x20,
                               .variant          = 1,
                               .bitrate = general::bitrate::automatic_t{ general::bitrate::kbps_t{ 10 },
                                                              general::bitrate::kbps_t{ 20 } },
                               .sends_wake_up_signal = true },
                       .diagnostic = diagnostic_t{ .nad              = diagnostic::nad::range_t{ 1, 3 },
                                                   .diagnostic_class = 2,
                                                   .p2_min           = 100,
                                                   .st_min           = 40,
                                                   .support_sids     = { 0xb0, 0xb2, 0xb7 } },
                       .frames =
                frames_t{ frame_t{ .kind       = frame::kind_t::publish,
                                              .name       = "node_status",
                                              .size       = 4,
                                              .min_period = 10,
                                              .max_period = 100,
                                              .signals    = { signal_t{ "state", 0, 8, 0 },
                                                              signal_t{ "error_bit", 0, 1, 8 },
                                                              signal_t{ "fault_state", 0, 2, 9, "fault_enc" },
                                                              signal_t{ "angle",
                                                          signal::init_value::array_t{ 0x22, 0x11 },
                                                          16,
                                                          16 } } },
                          frame_t{ .kind       = frame::kind_t::subscribe,
                                              .name       = "control",
                                              .size       = 1,
                                              .max_period = 100,
                                              .signals    = { signal_t{ "command", 0, 8, 0, "position" } } } },
                       .signal_encodings =
                signal::encodings_t{
                    signal::encoding_t{
                                   .name   = "position",
                                   .values = { signal::encoding::physical_range_t{
                            0, 199, 1.8, 0.0, "deg" } } },
                    signal::encoding_t{
                                   .name   = "fault_enc",
                                   .values = { signal::encoding::logical_value_t{ 0, "no result" },
                                               signal::encoding::logical_value_t{ 1, "failed" },
                                               signal::encoding::logical_value_t{ 2, "passed" } } } },
                       .status_management = status_management_t{ .response_error      = "error_bit",
                                                                 .fault_state_signals = { "fault_state" } },
                       .free_text = free_text_t{ "step_motor signal values outside 0 - 199 are ignored" } } }

    };

    validate::node_capability_file_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(ncf);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "global.language_version\n"
        "global.node_names\n"
        "node[step_motor].frame_names\n"
        "node[step_motor].signal_encoding_names\n"
        "node[step_motor].general.protocol_version\n"
        "node[step_motor].general.supplier\n"
        "node[step_motor].general.function\n"
        "node[step_motor].general.variant\n"
        "node[step_motor].general.bitrate\n"
        "node[step_motor].diagnostic.nad\n"
        "node[step_motor].diagnostic.diagnostic_class\n"
        "node[step_motor].diagnostic.p2_min\n"
        "node[step_motor].diagnostic.st_min\n"
        "node[step_motor].diagnostic.support_sid\n"
        "node[step_motor].frame[node_status].length\n"
        "node[step_motor].frame[node_status].min_period\n"
        "node[step_motor].frame[node_status].max_period\n"
        "node[step_motor].frame[node_status].min_period/max_period\n"
        "node[step_motor].frame[node_status].signal_names\n"
        "node[step_motor].frame[node_status].signal_sizes\n"
        "node[step_motor].frame[node_status].signal_offsets\n"
        "node[step_motor].frame[node_status].signal_size_offset\n"
        "node[step_motor].frame[node_status].signal[state].init_value\n"
        "node[step_motor].frame[node_status].signal[state].size\n"
        "node[step_motor].frame[node_status].signal[state].offset\n"
        "node[step_motor].frame[node_status].signal[error_bit].init_value\n"
        "node[step_motor].frame[node_status].signal[error_bit].size\n"
        "node[step_motor].frame[node_status].signal[error_bit].offset\n"
        "node[step_motor].frame[node_status].signal[fault_state].init_value\n"
        "node[step_motor].frame[node_status].signal[fault_state].size\n"
        "node[step_motor].frame[node_status].signal[fault_state].offset\n"
        "node[step_motor].frame[node_status].signal[angle].init_value\n"
        "node[step_motor].frame[node_status].signal[angle].size\n"
        "node[step_motor].frame[node_status].signal[angle].offset\n"
        "node[step_motor].frame[control].length\n"
        "node[step_motor].frame[control].max_period\n"
        "node[step_motor].frame[control].signal_names\n"
        "node[step_motor].frame[control].signal_sizes\n"
        "node[step_motor].frame[control].signal_offsets\n"
        "node[step_motor].frame[control].signal_size_offset\n"
        "node[step_motor].frame[control].signal[command].init_value\n"
        "node[step_motor].frame[control].signal[command].size\n"
        "node[step_motor].frame[control].signal[command].offset\n"
        "node[step_motor].signal_encodings.usage\n"
        "node[step_motor].status_management.response_error\n"
        "node[step_motor].status_management.fault_state_signals\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}
