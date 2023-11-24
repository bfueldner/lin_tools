#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>
#include <lin/ldf/frame_event_triggered.hpp>
#include <lin/ldf/frame_sporadic.hpp>
#include <lin/ldf/frame_unconditional.hpp>
#include <lin/ldf/nodes.hpp>
#include <lin/ldf/schedule_table.hpp>
#include <lin/ldf/validate/schedule_table.hpp>

/* 9.2.5 Schedule table definition */

class test_lin_ldf_schedule_table_entry_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_node_assign_nad)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .master{ .name = "CEM" }, .slaves = { "LSM", "RSM" } };
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command = schedule_table::command::assign_nad_t{
                                             .node = "LSM" } };

    validate::schedule_table::entry::command_node_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "command_node\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_node_data_dump)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .master{ .name = "CEM" }, .slaves = { "LSM", "RSM" } };
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command = schedule_table::command::data_dump_t{
                                             .node = "CEM" } };

    validate::schedule_table::entry::command_node_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "command_node\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_node_save_configuration)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .master{ .name = "CEM" }, .slaves = { "LSM", "RSM" } };
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command = schedule_table::command::save_configuration_t{
                                             .node = "RSM" } };

    validate::schedule_table::entry::command_node_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "command_node\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_node_assign_frame_id_range)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .master{ .name = "CEM" }, .slaves = { "LSM", "RSM" } };
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{
        .command = schedule_table::command::assign_frame_id_range_t{ .node = "LSM" }
    };

    validate::schedule_table::entry::command_node_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "command_node\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_node_assign_frame_id)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .master{ .name = "CEM" }, .slaves = { "LSM", "RSM" } };
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command = schedule_table::command::assign_frame_id_t{
                                             .node = "LSM" } };

    validate::schedule_table::entry::command_node_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "command_node\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_node_free_format)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command = schedule_table::command::free_format_t{} };

    validate::schedule_table::entry::command_node_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_node_assign_nad_error_not_defined)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command = schedule_table::command::assign_nad_t{
                                             .node = "LSM" } };

    validate::schedule_table::entry::command_node_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "command_node: Not defined 'LSM'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_node_data_dump_error_not_defined)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command = schedule_table::command::data_dump_t{
                                             .node = "CEM" } };

    validate::schedule_table::entry::command_node_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "command_node: Not defined 'CEM'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(
    test_lin_ldf_schedule_table_entry_validate,
    command_node_save_configuration_error_not_defined)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command = schedule_table::command::save_configuration_t{
                                             .node = "RSM" } };

    validate::schedule_table::entry::command_node_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "command_node: Not defined 'RSM'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(
    test_lin_ldf_schedule_table_entry_validate,
    command_node_assign_frame_id_range_error_not_defined)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{
        .command = schedule_table::command::assign_frame_id_range_t{ .node = "LSM" }
    };

    validate::schedule_table::entry::command_node_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "command_node: Not defined 'LSM'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_node_assign_frame_id_error_not_defined)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command = schedule_table::command::assign_frame_id_t{
                                             .node = "LSM" } };

    validate::schedule_table::entry::command_node_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "command_node: Not defined 'LSM'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_frame_regular)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{ frame::unconditional_t{
        .name = "RSM_Frm2" } };
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command =
                                             schedule_table::command::identifier_t{ "RSM_Frm2" } };

    validate::schedule_table::entry::command_frame_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "command_frame\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_frame_assign_frame_id)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{ frame::unconditional_t{
        .name = "CEM_Frm1" } };
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command = schedule_table::command::assign_frame_id_t{
                                             .frame = "CEM_Frm1" } };

    validate::schedule_table::entry::command_frame_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "command_frame\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_frame_regular_error_not_defined)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command = "CEM_Frm1" };

    validate::schedule_table::entry::command_frame_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "command_frame: Not defined 'CEM_Frm1'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_frame_assign_frame_id_error_not_defined)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command = schedule_table::command::assign_frame_id_t{
                                             .frame = "RSM_Frm1" } };

    validate::schedule_table::entry::command_frame_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "command_frame: Not defined 'RSM_Frm1'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_values_frame_name)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command =
                                             schedule_table::command::identifier_t{ "RSM_Frm1" } };

    validate::schedule_table::entry::command_values_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_values_master_req)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command = schedule_table::command::master_req_t{} };

    validate::schedule_table::entry::command_values_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_values_slave_resp)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command = schedule_table::command::slave_resp_t{} };

    validate::schedule_table::entry::command_values_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_values_assign_nad)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command = schedule_table::command::assign_nad_t{
                                             .node = "RSM" } };

    validate::schedule_table::entry::command_values_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_values_conditional_change_nad)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{
        .command =
            schedule_table::command::conditional_change_nad_t{
                .nad = 0x00, .id = 0x01, .byte = 0x02, .mask = 0x03, .inv = 0x04, .new_nad = 0x05 }
    };

    validate::schedule_table::entry::command_values_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "command_values\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_values_data_dump)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{
        .command =
            schedule_table::command::data_dump_t{
                .node = "LSM", .d1 = 0x10, .d2 = 0x20, .d3 = 0x30, .d4 = 0x40, .d5 = 0x50 }
    };

    validate::schedule_table::entry::command_values_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "command_values\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_values_save_configuration)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command = schedule_table::command::save_configuration_t{
                                             .node = "LSM" } };

    validate::schedule_table::entry::command_values_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_values_assign_frame_id_range)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{
        .command =
            schedule_table::command::assign_frame_id_range_t{
                .node = "LSM", .index = 0x00, .pids = { 0xAA, 0xBB, 0xCC, 0xDD } }
    };

    validate::schedule_table::entry::command_values_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "command_values\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_values_free_format)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command =
                                             schedule_table::command::free_format_t{ .d1 = 0x10,
                                                                                     .d2 = 0x20,
                                                                                     .d3 = 0x30,
                                                                                     .d4 = 0x40,
                                                                                     .d5 = 0x50,
                                                                                     .d6 = 0x60,
                                                                                     .d7 = 0x70,
                                                                                     .d8 = 0x80 } };

    validate::schedule_table::entry::command_values_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "command_values\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_values_assign_frame_id)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command = schedule_table::command::assign_frame_id_t{
                                             .node = "CEM", .frame = "CEM_Frm1" } };

    validate::schedule_table::entry::command_values_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, command_values_free_format_error_out_of_range)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command =
                                             schedule_table::command::free_format_t{ .d1 = 0x10,
                                                                                     .d2 = 0x20,
                                                                                     .d3 = 0x130,
                                                                                     .d4 = 0x40,
                                                                                     .d5 = 0x50,
                                                                                     .d6 = 0x60,
                                                                                     .d7 = 0x170,
                                                                                     .d8 = 0x80 } };

    validate::schedule_table::entry::command_values_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "command_values: FreeFormat member out of range 'D3, D7' (0..255)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, delay)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command = {}, .delay = 0 };

    validate::schedule_table::entry::delay_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "delay\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_schedule_table_entry_validate, delay_error_too_low)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    frame::unconditionals_t const unconditional_frames{};
    frame::sporadics_t const sporadic_frames{};
    frame::event_triggereds_t const event_triggered_frames{};
    schedule_table::entry_t const entry{ .command = {}, .delay = -1 };

    validate::schedule_table::entry::delay_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, unconditional_frames, sporadic_frames, event_triggered_frames, entry);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "delay: Value too low '-1' (>= 0)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}
