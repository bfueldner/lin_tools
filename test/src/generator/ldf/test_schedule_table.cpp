#include <sstream>

#include <gtest/gtest.h>

#include <lin/ldf/schedule_table.hpp>

#include <lin/ldf/generator/schedule_table.hpp>

/* 9.2.5 Schedule table definition*/

TEST(test_lin_ldf_schedule_table_generator, frame_name)
{
    using namespace lin::ldf::schedule_table;

    command_t const command{ "CEM_Frm1" };

    std::stringstream stream{};
    stream << command;
    EXPECT_EQ(stream.str(), "CEM_Frm1");
}

TEST(test_lin_ldf_schedule_table_generator, command_master_req)
{
    using namespace lin::ldf::schedule_table;

    command_t const command{ command::master_req_t{} };

    std::stringstream stream{};
    stream << command;
    EXPECT_EQ(stream.str(), "MasterReq");
}

TEST(test_lin_ldf_schedule_table_generator, command_slave_resp)
{
    using namespace lin::ldf::schedule_table;

    command_t const command{ command::slave_resp_t{} };

    std::stringstream stream{};
    stream << command;
    EXPECT_EQ(stream.str(), "SlaveResp");
}

TEST(test_lin_ldf_schedule_table_generator, command_assign_nad)
{
    using namespace lin::ldf::schedule_table;

    command_t const command{ command::assign_nad_t{ "LSM" } };

    std::stringstream stream{};
    stream << command;
    EXPECT_EQ(stream.str(), "AssignNAD { LSM }");
}

TEST(test_lin_ldf_schedule_table_generator, command_conditional_change_nad)
{
    using namespace lin::ldf::schedule_table;

    command_t const command{ command::conditional_change_nad_t{
        0x7F, 0x01, 0x03, 0x01, 0xFF, 0x01 } };

    std::stringstream stream{};
    stream << command;
    EXPECT_EQ(stream.str(), "ConditionalChangeNAD { 0x7f, 0x01, 0x03, 0x01, 0xff, 0x01 }");
}

TEST(test_lin_ldf_schedule_table_generator, command_data_dump)
{
    using namespace lin::ldf::schedule_table;

    command_t const command{ command::data_dump_t{ "LSM", 1, 2, 3, 4, 5 } };

    std::stringstream stream{};
    stream << command;
    EXPECT_EQ(stream.str(), "DataDump { LSM, 0x01, 0x02, 0x03, 0x04, 0x05 }");
}

TEST(test_lin_ldf_schedule_table_generator, command_save_configuration)
{
    using namespace lin::ldf::schedule_table;

    command_t const command{ command::save_configuration_t{ "LSM" } };

    std::stringstream stream{};
    stream << command;
    EXPECT_EQ(stream.str(), "SaveConfiguration { LSM }");
}

TEST(test_lin_ldf_schedule_table_generator, command_assign_frame_id_range)
{
    using namespace lin::ldf::schedule_table;

    command_t const command{ command::assign_frame_id_range_t{ "LSM", 0, { 1, 2 } } };

    std::stringstream stream{};
    stream << command;
    EXPECT_EQ(stream.str(), "AssignFrameIdRange { LSM, 0, 0x01, 0x02 }");
}

TEST(test_lin_ldf_schedule_table_generator, command_free_format)
{
    using namespace lin::ldf::schedule_table;

    command_t const command{ command::free_format_t{
        0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80 } };

    std::stringstream stream{};
    stream << command;
    EXPECT_EQ(stream.str(), "FreeFormat { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80 }");
}

TEST(test_lin_ldf_schedule_table_generator, command_assign_frame_id)
{
    using namespace lin::ldf::schedule_table;

    command_t const command{ command::assign_frame_id_t{ "RSM", "CEM_Frm1" } };

    std::stringstream stream{};
    stream << command;
    EXPECT_EQ(stream.str(), "AssignFrameId { RSM, CEM_Frm1 }");
}

TEST(test_lin_ldf_schedule_table_generator, table_entry_assign_nad)
{
    using namespace lin::ldf::schedule_table;

    table_entry_t const table_entry{ command::assign_nad_t{ "LSM" }, 15.0 };

    std::stringstream stream{};
    stream << table_entry;
    EXPECT_EQ(stream.str(), "AssignNAD { LSM } delay 15 ms;\n");
}

TEST(test_lin_ldf_schedule_table_generator, table_entry_identifier)
{
    using namespace lin::ldf::schedule_table;

    table_entry_t const table_entry{ "CEM_Frm1", 15 };

    std::stringstream stream{};
    stream << table_entry;
    EXPECT_EQ(stream.str(), "CEM_Frm1 delay 15 ms;\n");
}

TEST(test_lin_ldf_schedule_table_generator, schedule_table)
{
    using namespace lin::ldf;

    schedule_table_t const schedule_table{
        "Configuration_Schedule",
        { { schedule_table::command::assign_nad_t{ "LSM" }, 15.0 },
          { schedule_table::command::assign_frame_id_range_t{ "LSM", 0 }, 15.0 },
          { schedule_table::command::assign_frame_id_t{ "RSM", "CEM_Frm1" }, 15.0 } }
    };

    std::stringstream stream{};
    stream << schedule_table;
    EXPECT_EQ(
        stream.str(),
        "Configuration_Schedule {\n"
        "    AssignNAD { LSM } delay 15 ms;\n"
        "    AssignFrameIdRange { LSM, 0 } delay 15 ms;\n"
        "    AssignFrameId { RSM, CEM_Frm1 } delay 15 ms;\n"
        "}\n");
}

TEST(test_lin_ldf_schedule_table_generator, schedule_tables)
{
    using namespace lin::ldf;

    schedule_tables_t const schedule_tables{
        { "MRF_schedule", { { schedule_table::command::master_req_t{}, 10.0 } } },
        { "SRF_schedule", { { schedule_table::command::slave_resp_t{}, 10.0 } } }
    };

    std::stringstream stream{};
    stream << schedule_tables;
    EXPECT_EQ(
        stream.str(),
        "Schedule_tables {\n"
        "    MRF_schedule {\n"
        "        MasterReq delay 10 ms;\n"
        "    }\n"
        "    SRF_schedule {\n"
        "        SlaveResp delay 10 ms;\n"
        "    }\n"
        "}\n");
}
