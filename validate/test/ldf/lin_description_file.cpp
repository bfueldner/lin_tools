#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>
#include <lin/ldf/frame_diagnostic.hpp>
#include <lin/ldf/frame_event_triggered.hpp>
#include <lin/ldf/frame_sporadic.hpp>
#include <lin/ldf/frame_unconditional.hpp>
#include <lin/ldf/lin_description_file.hpp>
#include <lin/ldf/node_attribute.hpp>
#include <lin/ldf/node_composition.hpp>
#include <lin/ldf/schedule_table.hpp>
#include <lin/ldf/signal_diagnostic.hpp>
#include <lin/ldf/signal_encoding.hpp>
#include <lin/ldf/signal_group.hpp>
#include <lin/ldf/signal_representation.hpp>
#include <lin/ldf/signal_standard.hpp>
#include <lin/ldf/validate/lin_description_file.hpp>

/* 9.2 LIN description file definition */

class test_lin_ldf_lin_description_file_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ldf_lin_description_file_validate, protocol_version_1)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .protocol_version = "1.3" };

    validate::lin_description_file::protocol_version_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "lin_protocol_version\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_lin_description_file_validate, protocol_version_2)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .protocol_version = "2.2" };

    validate::lin_description_file::protocol_version_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "lin_protocol_version\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_lin_description_file_validate, protocol_version_error_not_supported)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .protocol_version = "2.4" };

    validate::lin_description_file::protocol_version_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "lin_protocol_version: Protocol version not supported '2.4' (<= 2.2)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_lin_description_file_validate, language_version)
{
    using namespace lin::ldf;

    lin_description_file_t const ldf{ .language_version = "2.2" };

    validate::lin_description_file::language_version_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(ldf);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "lin_language_version\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_lin_description_file_validate, language_version_warning)
{
    using namespace lin::ldf;

    lin_description_file_t const ldf{ .language_version = "1.5" };

    validate::lin_description_file::language_version_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(ldf);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "lin_language_version: Language version supported, but deprecated '1.5'\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_lin_description_file_validate, language_version_error)
{
    using namespace lin::ldf;

    lin_description_file_t const ldf{ .language_version = "2.4" };

    validate::lin_description_file::language_version_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(ldf);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "lin_language_version: Language version not supported '2.4' (<= 2.2)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_lin_description_file_validate, bitrate)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .bitrate = bitrate_t{ 9.6 } };

    validate::lin_description_file::bitrate_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "lin_speed\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_lin_description_file_validate, bitrate_error_too_low)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .bitrate = bitrate_t{ 0.9 } };

    validate::lin_description_file::bitrate_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "lin_speed: Value too low '0.9 kbps' (1 kbps..20 kbps)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_lin_description_file_validate, bitrate_error_too_high)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .bitrate = bitrate_t{ 20.1 } };

    validate::lin_description_file::bitrate_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "lin_speed: Value too high '20.1 kbps' (1 kbps..20 kbps)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_lin_description_file_validate, channel_name)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .channel_name = "DB" };

    validate::lin_description_file::channel_name_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "channel_name\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_lin_description_file_validate, channel_name_warning_number)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .channel_name = "0DB" };

    validate::lin_description_file::channel_name_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "channel_name: Name starts with numeric character '0' (A-Z/a-z)\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_lin_description_file_validate, node_attribute_names)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .node_attributes{
        node::attribute_t{ .name = "abc" }, node::attribute_t{ .name = "def" } } };

    validate::lin_description_file::node_attribute_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "node_attribute_names\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_lin_description_file_validate, node_attribute_names_error_not_unique)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .node_attributes{
        node::attribute_t{ .name = "abc" },
        node::attribute_t{ .name = "abc" },
        node::attribute_t{ .name = "def" },
        node::attribute_t{ .name = "def" } } };

    validate::lin_description_file::node_attribute_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "node_attribute_names: Names not unique 'abc, def'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_lin_description_file_validate, node_composition_names)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .node_compositions{
        node::composition::configuration_t{ "abc" },
        node::composition::configuration_t{ "def" } } };

    validate::lin_description_file::node_composition_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "node_composition_names\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_lin_description_file_validate, node_composition_names_error_not_unique)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .node_compositions{
        node::composition::configuration_t{ "abc" },
        node::composition::configuration_t{ "abc" } } };

    validate::lin_description_file::node_composition_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "node_composition_names: Names not unique 'abc'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_lin_description_file_validate, standard_signal_names)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .standard_signals{
        signal::standard_t{ "abc" }, signal::standard_t{ "def" } } };

    validate::lin_description_file::standard_signal_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "standard_signal_names\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_lin_description_file_validate, standard_signal_names_error_not_unique)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .standard_signals{
        signal::standard_t{ "def" }, signal::standard_t{ "def" } } };

    validate::lin_description_file::standard_signal_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "standard_signal_names: Names not unique 'def'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_lin_description_file_validate, diagnostic_signal_names)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .diagnostic_signals{
        signal::diagnostic_t{ "MasterReqB0" },
        signal::diagnostic_t{ "MasterReqB1" },
        signal::diagnostic_t{ "MasterReqB2" },
        signal::diagnostic_t{ "MasterReqB3" },
        signal::diagnostic_t{ "MasterReqB4" },
        signal::diagnostic_t{ "MasterReqB5" },
        signal::diagnostic_t{ "MasterReqB6" },
        signal::diagnostic_t{ "MasterReqB7" },
        signal::diagnostic_t{ "SlaveRespB0" },
        signal::diagnostic_t{ "SlaveRespB1" },
        signal::diagnostic_t{ "SlaveRespB2" },
        signal::diagnostic_t{ "SlaveRespB3" },
        signal::diagnostic_t{ "SlaveRespB4" },
        signal::diagnostic_t{ "SlaveRespB5" },
        signal::diagnostic_t{ "SlaveRespB6" },
        signal::diagnostic_t{ "SlaveRespB7" } } };

    validate::lin_description_file::diagnostic_signal_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "diagnostic_signal_names\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_lin_description_file_validate, diagnostic_signal_names_error_not_unique)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .diagnostic_signals{
        signal::diagnostic_t{ "MasterReqB0" },
        signal::diagnostic_t{ "MasterReqB1" },
        signal::diagnostic_t{ "MasterReqB2" },
        signal::diagnostic_t{ "MasterReqB3" },
        signal::diagnostic_t{ "MasterReqB4" },
        signal::diagnostic_t{ "MasterReqB5" },
        signal::diagnostic_t{ "MasterReqB6" },
        signal::diagnostic_t{ "MasterReqB7" },
        signal::diagnostic_t{ "MasterReqB0" },
        signal::diagnostic_t{ "MasterReqB1" },
        signal::diagnostic_t{ "MasterReqB2" },
        signal::diagnostic_t{ "MasterReqB3" },
        signal::diagnostic_t{ "MasterReqB4" },
        signal::diagnostic_t{ "MasterReqB5" },
        signal::diagnostic_t{ "MasterReqB6" },
        signal::diagnostic_t{ "MasterReqB7" } } };

    validate::lin_description_file::diagnostic_signal_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "diagnostic_signal_names: Names not unique 'MasterReqB0, MasterReqB1, MasterReqB2, MasterReqB3, MasterReqB4, MasterReqB5, MasterReqB6, MasterReqB7'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_lin_description_file_validate, signal_group_names)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .signal_groups{
        signal::group_t{ "group1" }, signal::group_t{ "group2" } } };

    validate::lin_description_file::signal_group_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signal_group_names\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_lin_description_file_validate, signal_group_names_error_not_unique)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .signal_groups{
        signal::group_t{ "group" }, signal::group_t{ "group" } } };

    validate::lin_description_file::signal_group_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "signal_group_names: Names not unique 'group'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_lin_description_file_validate, unconditional_frame_names)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .unconditional_frames{
        frame::unconditional_t{ .name = "abc" }, frame::unconditional_t{ .name = "def" } } };

    validate::lin_description_file::unconditional_frame_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "unconditional_frame_names\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_lin_description_file_validate, unconditional_frame_names_error_not_unique)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .unconditional_frames{
        frame::unconditional_t{ .name = "abc" },
        frame::unconditional_t{ .name = "def" },
        frame::unconditional_t{ .name = "abc" },
        frame::unconditional_t{ .name = "def" } } };

    validate::lin_description_file::unconditional_frame_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "unconditional_frame_names: Names not unique 'abc, def'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}


TEST_F(test_lin_ldf_lin_description_file_validate, sporadic_frame_names)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .sporadic_frames{
        frame::sporadic_t{ .name = "abc" }, frame::sporadic_t{ .name = "def" } } };

    validate::lin_description_file::sporadic_frame_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "sporadic_frame_names\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_lin_description_file_validate, sporadic_frame_names_error_not_unique)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .sporadic_frames{
        frame::sporadic_t{ .name = "abc" },
        frame::sporadic_t{ .name = "def" },
        frame::sporadic_t{ .name = "abc" },
        frame::sporadic_t{ .name = "def" } } };

    validate::lin_description_file::sporadic_frame_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "sporadic_frame_names: Names not unique 'abc, def'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_lin_description_file_validate, event_triggered_frame_names)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .event_triggered_frames{
        frame::event_triggered_t{ .name = "abc" }, frame::event_triggered_t{ .name = "def" } } };

    validate::lin_description_file::event_triggered_frame_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "event_triggered_frame_names\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_lin_description_file_validate, event_triggered_frame_names_error_not_unique)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .event_triggered_frames{
        frame::event_triggered_t{ .name = "abc" },
        frame::event_triggered_t{ .name = "def" },
        frame::event_triggered_t{ .name = "abc" },
        frame::event_triggered_t{ .name = "def" } } };

    validate::lin_description_file::event_triggered_frame_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "event_triggered_frame_names: Names not unique 'abc, def'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_lin_description_file_validate, diagnostic_frame_names)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .diagnostic_frames{
        frame::diagnostic_t{ .name = "abc" }, frame::diagnostic_t{ .name = "def" } } };

    validate::lin_description_file::diagnostic_frame_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "diagnostic_frame_names\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_lin_description_file_validate, diagnostic_frame_names_error_not_unique)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .diagnostic_frames{
        frame::diagnostic_t{ .name = "abc" },
        frame::diagnostic_t{ .name = "def" },
        frame::diagnostic_t{ .name = "abc" },
        frame::diagnostic_t{ .name = "def" } } };

    validate::lin_description_file::diagnostic_frame_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "diagnostic_frame_names: Names not unique 'abc, def'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_lin_description_file_validate, schedule_table_names)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .schedule_tables{
        schedule_table_t{ .name = "abc" }, schedule_table_t{ .name = "def" } } };

    validate::lin_description_file::schedule_table_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "schedule_table_names\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_lin_description_file_validate, schedule_table_names_error_not_unique)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .schedule_tables{
        schedule_table_t{ .name = "abc" },
        schedule_table_t{ .name = "def" },
        schedule_table_t{ .name = "abc" },
        schedule_table_t{ .name = "def" } } };

    validate::lin_description_file::schedule_table_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "schedule_table_names: Names not unique 'abc, def'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_lin_description_file_validate, signal_encoding_names)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .signal_encodings{
        signal::encoding_t{ "Dig2Bit" },
        signal::encoding_t{ "ErrorEncoding" },
        signal::encoding_t{ "FaultStateEncoding" },
        signal::encoding_t{ "LightEncoding" } } };

    validate::lin_description_file::signal_encoding_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signal_encoding_names\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_lin_description_file_validate, signal_encoding_names_error_not_unique)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .signal_encodings{
        signal::encoding_t{ "Dig2Bit" },
        signal::encoding_t{ "ErrorEncoding" },
        signal::encoding_t{ "FaultStateEncoding" },
        signal::encoding_t{ "Dig2Bit" },
        signal::encoding_t{ "LightEncoding" } } };

    validate::lin_description_file::signal_encoding_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "signal_encoding_names: Names not unique 'Dig2Bit'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_lin_description_file_validate, signal_representation_names)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .signal_representations{
        signal::representation_t{ "Dig2Bit" },
        signal::representation_t{ "ErrorEncoding" },
        signal::representation_t{ "FaultStateEncoding" },
        signal::representation_t{ "LightEncoding" } } };

    validate::lin_description_file::signal_representation_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signal_representation_names\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_lin_description_file_validate, signal_representation_names_error_not_unique)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{ .signal_representations{
        signal::representation_t{ "Dig2Bit" },
        signal::representation_t{ "ErrorEncoding" },
        signal::representation_t{ "FaultStateEncoding" },
        signal::representation_t{ "LightEncoding" },
        signal::representation_t{ "ErrorEncoding" } } };

    validate::lin_description_file::signal_representation_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(lin_description_file);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "signal_representation_names: Names not unique 'ErrorEncoding'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

/* 9.2 LIN description file definition */

TEST_F(test_lin_ldf_lin_description_file_validate, complete)
{
    using namespace lin::ldf;

    lin_description_file_t const ldf{
        "2.2",
        "2.2",
        { 19.2 },
        "DB",
        { { "CEM", 5, 0.1 }, { "LSM", "RSM" } },
        {},
        { { "InternalLightsRequest", 2, 0, "CEM", { "LSM", "RSM" } },
          { "RightIntLightsSwitch", 8, 0, "RSM", { "CEM" } },
          { "LeftIntLightsSwitch", 8, 0, "LSM", { "CEM" } },
          { "LSMerror", 1, 0, "LSM", { "CEM" } },
          { "RSMerror", 1, 0, "RSM", { "CEM" } },
          { "IntError", 2, 0, "LSM", { "CEM" } } },
        {},
        {
            { "CEM_Frm1", 0x01, "CEM", 1, { { "InternalLightsRequest", 0 } } },
            { "LSM_Frm1", 0x02, "LSM", 2, { { "LeftIntLightsSwitch", 8 } } },
            { "LSM_Frm2", 0x03, "LSM", 1, { { "LSMerror", 0 }, { "IntError", 1 } } },
            { "RSM_Frm1", 0x04, "RSM", 2, { { "RightIntLightsSwitch", 8 } } },
            { "RSM_Frm2", 0x05, "RSM", 1, { { "RSMerror", 0 } } },
        },
        {},
        { { "Node_Status_Event", "Collision_resolver", 0x06, { "RSM_Frm1", "LSM_Frm1" } } },
        {},
        { {
              .name                = "RSM",
              .protocol_version    = "2.0",
              .configured_nad      = 0x20,
              .product_id          = node::attribute::product_id_t{ 0x4e4e, 0x4553, 1 },
              .response_error      = "RSMerror",
              .p2_min              = 150,
              .st_min              = 50,
              .configurable_frames = { { "Node_Status_Event", 0 },
                                       { "CEM_Frm1", 1 },
                                       { "RSM_Frm1", 2 },
                                       { "RSM_Frm2", 3 } },
          },
          {
              .name                = "LSM",
              .protocol_version    = "2.2",
              .configured_nad      = 0x21,
              .initial_nad         = 0x01,
              .product_id          = node::attribute::product_id_t{ 0x4a4f, 0x4841 },
              .response_error      = "LSMerror",
              .fault_state_signals = { "IntTest" },
              .p2_min              = 150,
              .st_min              = 50,
              .configurable_frames = { { "Node_Status_Event" },
                                       { "CEM_Frm1" },
                                       { "LSM_Frm1" },
                                       { "LSM_Frm2" } },
          } },
        { { "Configuration_Schedule",
            { { schedule_table::command::assign_nad_t{ "LSM" }, 15.0 },
              { schedule_table::command::assign_frame_id_range_t{ "LSM", 0 }, 15.0 },
              { schedule_table::command::assign_frame_id_t{ "RSM", "CEM_Frm1" }, 15.0 },
              { schedule_table::command::assign_frame_id_t{ "RSM", "RSM_Frm1" }, 15.0 },
              { schedule_table::command::assign_frame_id_t{ "RSM", "RSM_Frm2" }, 15.0 } } },
          { "Normal_Schedule",
            { { "CEM_Frm1", 15.0 },
              { "LSM_Frm2", 15.0 },
              { "RSM_Frm2", 15.0 },
              { "Node_Status_Event", 10.0 } } },
          { "MRF_schedule", { { schedule_table::command::master_req_t{}, 10.0 } } },
          { "SRF_schedule", { { schedule_table::command::slave_resp_t{}, 10.0 } } },
          { "Collision_resolver",
            { { "CEM_Frm1", 15.0 },
              { "LSM_Frm2", 15.0 },
              { "RSM_Frm2", 15.0 },
              { "RSM_Frm1", 10.0 },
              { "CEM_Frm1", 15.0 },
              { "LSM_Frm2", 15.0 },
              { "RSM_Frm2", 15.0 },
              { "LSM_Frm1", 10.0 } } } },
        {},
        { { "Dig2Bit",
            { signal::encoding::logical_value_t{ 0, "off" },
              signal::encoding::logical_value_t{ 1, "on" },
              signal::encoding::logical_value_t{ 2, "error" },
              signal::encoding::logical_value_t{ 3, "void" } } },
          { "ErrorEncoding",
            { signal::encoding::logical_value_t{ 0, "OK" },
              signal::encoding::logical_value_t{ 1, "error" } } },
          { "FaultStateEncoding",
            { signal::encoding::logical_value_t{ 0, "No test result" },
              signal::encoding::logical_value_t{ 1, "failed" },
              signal::encoding::logical_value_t{ 2, "passed" },
              signal::encoding::logical_value_t{ 3, "not used" } } },
          { "LightEncoding",
            { signal::encoding::logical_value_t{ 0, "Off" },
              signal::encoding::physical_range_t{ 1, 254, 1.0, 100.0, "lux" },
              signal::encoding::logical_value_t{ 255, "error" } } } },
        { { "Dig2Bit", { "InternalLightsRequest" } },
          { "ErrorEncoding", { "RSMerror", "LSMerror" } },
          { "FaultStateEncoding", { "IntError" } },
          { "LightEncoding", { "RightIntLightsSwitch", "LeftIntLightsSwitch" } } }
    };

    validate::lin_description_file_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(ldf);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "global.lin_language_version\n"
        "global.lin_protocol_version\n"
        "global.lin_speed\n"
        "global.channel_name\n"
        "global.node_attribute_names\n"
        "global.node_composition_names\n"
        "global.standard_signal_names\n"
        "global.diagnostic_signal_names\n"
        "global.signal_group_names\n"
        "global.unconditional_frame_names\n"
        "global.sporadic_frame_names\n"
        "global.event_triggered_frame_names\n"
        "global.diagnostic_frame_names\n"
        "global.schedule_table_names\n"
        "global.signal_encoding_names\n"
        "global.signal_representation_names\n"
        "nodes.master.time_base\n"
        "nodes.master.jitter\n"
        "nodes.node_names\n"
        "node_attribute[RSM].lin_protocol\n"
        "node_attribute[RSM].configured_nad\n"
        "node_attribute[RSM].product_id\n"
        "node_attribute[RSM].attributes\n"
        "node_attribute[RSM].configurable_frames\n"
        "node_attribute[LSM].lin_protocol\n"
        "node_attribute[LSM].configured_nad\n"
        "node_attribute[LSM].initial_nad\n"
        "node_attribute[LSM].product_id\n"
        "node_attribute[LSM].attributes\n"
        "node_attribute[LSM].configurable_frames\n"
        "standard_signal[InternalLightsRequest].size\n"
        "standard_signal[InternalLightsRequest].init_value\n"
        "standard_signal[InternalLightsRequest].published_by\n"
        "standard_signal[InternalLightsRequest].subscribed_by\n"
        "standard_signal[RightIntLightsSwitch].size\n"
        "standard_signal[RightIntLightsSwitch].init_value\n"
        "standard_signal[RightIntLightsSwitch].published_by\n"
        "standard_signal[RightIntLightsSwitch].subscribed_by\n"
        "standard_signal[LeftIntLightsSwitch].size\n"
        "standard_signal[LeftIntLightsSwitch].init_value\n"
        "standard_signal[LeftIntLightsSwitch].published_by\n"
        "standard_signal[LeftIntLightsSwitch].subscribed_by\n"
        "standard_signal[LSMerror].size\n"
        "standard_signal[LSMerror].init_value\n"
        "standard_signal[LSMerror].published_by\n"
        "standard_signal[LSMerror].subscribed_by\n"
        "standard_signal[RSMerror].size\n"
        "standard_signal[RSMerror].init_value\n"
        "standard_signal[RSMerror].published_by\n"
        "standard_signal[RSMerror].subscribed_by\n"
        "standard_signal[IntError].size\n"
        "standard_signal[IntError].init_value\n"
        "standard_signal[IntError].published_by\n"
        "standard_signal[IntError].subscribed_by\n"
        "unconditional_frame[CEM_Frm1].id\n"
        "unconditional_frame[CEM_Frm1].published_by\n"
        "unconditional_frame[CEM_Frm1].size\n"
        "unconditional_frame[CEM_Frm1].signal_published_by\n"
        "unconditional_frame[CEM_Frm1].signal_sizes\n"
        "unconditional_frame[CEM_Frm1].signal_offsets\n"
        "unconditional_frame[CEM_Frm1].signals\n"
        "unconditional_frame[CEM_Frm1].signal[InternalLightsRequest].name\n"
        "unconditional_frame[CEM_Frm1].signal[InternalLightsRequest].offset\n"
        "unconditional_frame[LSM_Frm1].id\n"
        "unconditional_frame[LSM_Frm1].published_by\n"
        "unconditional_frame[LSM_Frm1].size\n"
        "unconditional_frame[LSM_Frm1].signal_published_by\n"
        "unconditional_frame[LSM_Frm1].signal_sizes\n"
        "unconditional_frame[LSM_Frm1].signal_offsets\n"
        "unconditional_frame[LSM_Frm1].signals\n"
        "unconditional_frame[LSM_Frm1].signal[LeftIntLightsSwitch].name\n"
        "unconditional_frame[LSM_Frm1].signal[LeftIntLightsSwitch].offset\n"
        "unconditional_frame[LSM_Frm2].id\n"
        "unconditional_frame[LSM_Frm2].published_by\n"
        "unconditional_frame[LSM_Frm2].size\n"
        "unconditional_frame[LSM_Frm2].signal_published_by\n"
        "unconditional_frame[LSM_Frm2].signal_sizes\n"
        "unconditional_frame[LSM_Frm2].signal_offsets\n"
        "unconditional_frame[LSM_Frm2].signals\n"
        "unconditional_frame[LSM_Frm2].signal[LSMerror].name\n"
        "unconditional_frame[LSM_Frm2].signal[LSMerror].offset\n"
        "unconditional_frame[LSM_Frm2].signal[IntError].name\n"
        "unconditional_frame[LSM_Frm2].signal[IntError].offset\n"
        "unconditional_frame[RSM_Frm1].id\n"
        "unconditional_frame[RSM_Frm1].published_by\n"
        "unconditional_frame[RSM_Frm1].size\n"
        "unconditional_frame[RSM_Frm1].signal_published_by\n"
        "unconditional_frame[RSM_Frm1].signal_sizes\n"
        "unconditional_frame[RSM_Frm1].signal_offsets\n"
        "unconditional_frame[RSM_Frm1].signals\n"
        "unconditional_frame[RSM_Frm1].signal[RightIntLightsSwitch].name\n"
        "unconditional_frame[RSM_Frm1].signal[RightIntLightsSwitch].offset\n"
        "unconditional_frame[RSM_Frm2].id\n"
        "unconditional_frame[RSM_Frm2].published_by\n"
        "unconditional_frame[RSM_Frm2].size\n"
        "unconditional_frame[RSM_Frm2].signal_published_by\n"
        "unconditional_frame[RSM_Frm2].signal_sizes\n"
        "unconditional_frame[RSM_Frm2].signal_offsets\n"
        "unconditional_frame[RSM_Frm2].signals\n"
        "unconditional_frame[RSM_Frm2].signal[RSMerror].name\n"
        "unconditional_frame[RSM_Frm2].signal[RSMerror].offset\n"
        "event_triggered_frame[Node_Status_Event].schedule_table\n"
        "event_triggered_frame[Node_Status_Event].id\n"
        "event_triggered_frame[Node_Status_Event].frames\n"
        "schedul_table[Configuration_Schedule].entry[0].command_node\n"
        "schedul_table[Configuration_Schedule].entry[0].delay\n"
        "schedul_table[Configuration_Schedule].entry[1].command_node\n"
        "schedul_table[Configuration_Schedule].entry[1].command_values\n"
        "schedul_table[Configuration_Schedule].entry[1].delay\n"
        "schedul_table[Configuration_Schedule].entry[2].command_node\n"
        "schedul_table[Configuration_Schedule].entry[2].command_frame\n"
        "schedul_table[Configuration_Schedule].entry[2].delay\n"
        "schedul_table[Configuration_Schedule].entry[3].command_node\n"
        "schedul_table[Configuration_Schedule].entry[3].command_frame\n"
        "schedul_table[Configuration_Schedule].entry[3].delay\n"
        "schedul_table[Configuration_Schedule].entry[4].command_node\n"
        "schedul_table[Configuration_Schedule].entry[4].command_frame\n"
        "schedul_table[Configuration_Schedule].entry[4].delay\n"
        "schedul_table[Normal_Schedule].entry[0].command_frame\n"
        "schedul_table[Normal_Schedule].entry[0].delay\n"
        "schedul_table[Normal_Schedule].entry[1].command_frame\n"
        "schedul_table[Normal_Schedule].entry[1].delay\n"
        "schedul_table[Normal_Schedule].entry[2].command_frame\n"
        "schedul_table[Normal_Schedule].entry[2].delay\n"
        "schedul_table[Normal_Schedule].entry[3].command_frame\n"
        "schedul_table[Normal_Schedule].entry[3].delay\n"
        "schedul_table[MRF_schedule].entry[0].delay\n"
        "schedul_table[SRF_schedule].entry[0].delay\n"
        "schedul_table[Collision_resolver].entry[0].command_frame\n"
        "schedul_table[Collision_resolver].entry[0].delay\n"
        "schedul_table[Collision_resolver].entry[1].command_frame\n"
        "schedul_table[Collision_resolver].entry[1].delay\n"
        "schedul_table[Collision_resolver].entry[2].command_frame\n"
        "schedul_table[Collision_resolver].entry[2].delay\n"
        "schedul_table[Collision_resolver].entry[3].command_frame\n"
        "schedul_table[Collision_resolver].entry[3].delay\n"
        "schedul_table[Collision_resolver].entry[4].command_frame\n"
        "schedul_table[Collision_resolver].entry[4].delay\n"
        "schedul_table[Collision_resolver].entry[5].command_frame\n"
        "schedul_table[Collision_resolver].entry[5].delay\n"
        "schedul_table[Collision_resolver].entry[6].command_frame\n"
        "schedul_table[Collision_resolver].entry[6].delay\n"
        "schedul_table[Collision_resolver].entry[7].command_frame\n"
        "schedul_table[Collision_resolver].entry[7].delay\n"
        "signal_encoding[Dig2Bit].types\n"
        "signal_encoding[Dig2Bit].values\n"
        "signal_encoding[Dig2Bit].usage\n"
        "signal_encoding[Dig2Bit].size\n"
        "signal_encoding[Dig2Bit].value[0].value\n"
        "signal_encoding[Dig2Bit].value[0].text_info\n"
        "signal_encoding[Dig2Bit].value[1].value\n"
        "signal_encoding[Dig2Bit].value[1].text_info\n"
        "signal_encoding[Dig2Bit].value[2].value\n"
        "signal_encoding[Dig2Bit].value[2].text_info\n"
        "signal_encoding[Dig2Bit].value[3].value\n"
        "signal_encoding[Dig2Bit].value[3].text_info\n"
        "signal_encoding[ErrorEncoding].types\n"
        "signal_encoding[ErrorEncoding].values\n"
        "signal_encoding[ErrorEncoding].usage\n"
        "signal_encoding[ErrorEncoding].size\n"
        "signal_encoding[ErrorEncoding].value[0].value\n"
        "signal_encoding[ErrorEncoding].value[0].text_info\n"
        "signal_encoding[ErrorEncoding].value[1].value\n"
        "signal_encoding[ErrorEncoding].value[1].text_info\n"
        "signal_encoding[FaultStateEncoding].types\n"
        "signal_encoding[FaultStateEncoding].values\n"
        "signal_encoding[FaultStateEncoding].usage\n"
        "signal_encoding[FaultStateEncoding].size\n"
        "signal_encoding[FaultStateEncoding].value[0].value\n"
        "signal_encoding[FaultStateEncoding].value[0].text_info\n"
        "signal_encoding[FaultStateEncoding].value[1].value\n"
        "signal_encoding[FaultStateEncoding].value[1].text_info\n"
        "signal_encoding[FaultStateEncoding].value[2].value\n"
        "signal_encoding[FaultStateEncoding].value[2].text_info\n"
        "signal_encoding[FaultStateEncoding].value[3].value\n"
        "signal_encoding[FaultStateEncoding].value[3].text_info\n"
        "signal_encoding[LightEncoding].types\n"
        "signal_encoding[LightEncoding].values\n"
        "signal_encoding[LightEncoding].usage\n"
        "signal_encoding[LightEncoding].size\n"
        "signal_encoding[LightEncoding].value[0].value\n"
        "signal_encoding[LightEncoding].value[0].text_info\n"
        "signal_encoding[LightEncoding].value[1].value\n"
        "signal_encoding[LightEncoding].value[1].text_info\n"
        "signal_encoding[LightEncoding].value[2].value\n"
        "signal_encoding[LightEncoding].value[2].text_info\n"
        "signal_representation[Dig2Bit].encoding\n"
        "signal_representation[Dig2Bit].signals\n"
        "signal_representation[ErrorEncoding].encoding\n"
        "signal_representation[ErrorEncoding].signals\n"
        "signal_representation[FaultStateEncoding].encoding\n"
        "signal_representation[FaultStateEncoding].signals\n"
        "signal_representation[LightEncoding].encoding\n"
        "signal_representation[LightEncoding].signals\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}
