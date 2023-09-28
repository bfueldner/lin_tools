#include <string>
#include <variant>

#include <gtest/gtest.h>

#include <lin/ldf/schedule_table.hpp>

#include <lin/ldf/parser/schedule_table.hpp>

/* 9.2.5 Schedule table definition*/

TEST(test_lin_ldf_schedule_table_parser, frame_name)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf::schedule_table;

    std::string text{ "CEM_Frm1" };
    command_t command{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::command, x3::ascii::space, command);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *frame_name = std::get_if< std::string >(&command);
    ASSERT_NE(frame_name, nullptr);
    EXPECT_STREQ(frame_name->c_str(), "CEM_Frm1");
}

TEST(test_lin_ldf_schedule_table_parser, command_master_req)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf::schedule_table;

    std::string text{ "MasterReq" };
    command_t command{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::command, x3::ascii::space, command);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *master_req = std::get_if< command::master_req_t >(&command);
    ASSERT_NE(master_req, nullptr);
}

TEST(test_lin_ldf_schedule_table_parser, command_slave_resp)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf::schedule_table;

    std::string text{ "SlaveResp" };
    command_t command{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::command, x3::ascii::space, command);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *slave_resp = std::get_if< command::slave_resp_t >(&command);
    ASSERT_NE(slave_resp, nullptr);
}

TEST(test_lin_ldf_schedule_table_parser, command_assign_nad)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf::schedule_table;

    std::string text{ "AssignNAD { LSM }" };
    command_t command{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::command, x3::ascii::space, command);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *assign_nad = std::get_if< command::assign_nad_t >(&command);
    ASSERT_NE(assign_nad, nullptr);
    EXPECT_STREQ(assign_nad->node_name.c_str(), "LSM");
}

TEST(test_lin_ldf_schedule_table_parser, command_conditional_change_nad)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf::schedule_table;

    std::string text{ "ConditionalChangeNAD { 0x7F, 0x01, 0x03, 0x01, 0xFF, 0x01 }" };
    command_t command{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::command, x3::ascii::space, command);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *conditional_change_nad = std::get_if< command::conditional_change_nad_t >(&command);
    ASSERT_NE(conditional_change_nad, nullptr);
    EXPECT_EQ(conditional_change_nad->nad, 0x7F);
    EXPECT_EQ(conditional_change_nad->id, 0x01);
    EXPECT_EQ(conditional_change_nad->byte, 0x03);
    EXPECT_EQ(conditional_change_nad->mask, 0x01);
    EXPECT_EQ(conditional_change_nad->inv, 0xFF);
    EXPECT_EQ(conditional_change_nad->new_nad, 0x01);
}

TEST(test_lin_ldf_schedule_table_parser, command_data_dump)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf::schedule_table;

    std::string text{ "DataDump { LSM, 1, 2, 3, 4, 5 }" };
    command_t command{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::command, x3::ascii::space, command);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *data_dump = std::get_if< command::data_dump_t >(&command);
    ASSERT_NE(data_dump, nullptr);
    EXPECT_STREQ(data_dump->node_name.c_str(), "LSM");
    EXPECT_EQ(data_dump->d1, 1);
    EXPECT_EQ(data_dump->d2, 2);
    EXPECT_EQ(data_dump->d3, 3);
    EXPECT_EQ(data_dump->d4, 4);
    EXPECT_EQ(data_dump->d5, 5);
}

TEST(test_lin_ldf_schedule_table_parser, command_save_configuration)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf::schedule_table;

    std::string text{ "SaveConfiguration {LSM}" };
    command_t command{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::command, x3::ascii::space, command);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *save_configuration = std::get_if< command::save_configuration_t >(&command);
    ASSERT_NE(save_configuration, nullptr);
    EXPECT_STREQ(save_configuration->node_name.c_str(), "LSM");
}

TEST(test_lin_ldf_schedule_table_parser, command_assign_frame_id_range)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf::schedule_table;

    std::string text{ "AssignFrameIdRange {LSM, 0, 1, 2}" };
    command_t command{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::command, x3::ascii::space, command);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *assign_frame_id_range = std::get_if< command::assign_frame_id_range_t >(&command);
    ASSERT_NE(assign_frame_id_range, nullptr);
    EXPECT_STREQ(assign_frame_id_range->node_name.c_str(), "LSM");
    EXPECT_EQ(assign_frame_id_range->frame_index, 0);
    EXPECT_EQ(assign_frame_id_range->frame_pids.size(), 2);
    EXPECT_EQ(assign_frame_id_range->frame_pids[0], 1);
    EXPECT_EQ(assign_frame_id_range->frame_pids[1], 2);
}

TEST(test_lin_ldf_schedule_table_parser, command_free_format)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf::schedule_table;

    std::string text{ "FreeFormat { 0x10, 0x20, 0x30, 0x40, 0x50, 0x60, 0x70, 0x80 }" };
    command_t command{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::command, x3::ascii::space, command);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *free_format = std::get_if< command::free_format_t >(&command);
    ASSERT_NE(free_format, nullptr);
    EXPECT_EQ(free_format->d1, 0x10);
    EXPECT_EQ(free_format->d2, 0x20);
    EXPECT_EQ(free_format->d3, 0x30);
    EXPECT_EQ(free_format->d4, 0x40);
    EXPECT_EQ(free_format->d5, 0x50);
    EXPECT_EQ(free_format->d6, 0x60);
    EXPECT_EQ(free_format->d7, 0x70);
    EXPECT_EQ(free_format->d8, 0x80);
}

TEST(test_lin_ldf_schedule_table_parser, command_assign_frame_id)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf::schedule_table;

    std::string text{ "AssignFrameId {RSM, CEM_Frm1}" };
    command_t command{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::command, x3::ascii::space, command);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *assign_frame_id = std::get_if< command::assign_frame_id_t >(&command);
    ASSERT_NE(assign_frame_id, nullptr);
    EXPECT_STREQ(assign_frame_id->node_name.c_str(), "RSM");
    EXPECT_STREQ(assign_frame_id->frame_name.c_str(), "CEM_Frm1");
}

TEST(test_lin_ldf_schedule_table_parser, table_entry_assign_nad)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf::schedule_table;

    std::string text{ "AssignNAD {LSM} delay 15 ms;" };
    table_entry_t table_entry{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::table_entry, x3::ascii::space, table_entry);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *assign_nad = std::get_if< command::assign_nad_t >(&(table_entry.command));
    ASSERT_NE(assign_nad, nullptr);
    EXPECT_STREQ(assign_nad->node_name.c_str(), "LSM");
    EXPECT_EQ(table_entry.frame_time, 15.0);
}

TEST(test_lin_ldf_schedule_table_parser, table_entry_identifier)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf::schedule_table;

    std::string text{ "CEM_Frm1 delay 15 ms;" };
    table_entry_t table_entry{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::table_entry, x3::ascii::space, table_entry);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *identifier = std::get_if< command::identifier_t >(&(table_entry.command));
    ASSERT_NE(identifier, nullptr);
    EXPECT_STREQ(identifier->c_str(), "CEM_Frm1");
    EXPECT_EQ(table_entry.frame_time, 15.0);
}

TEST(test_lin_ldf_schedule_table_parser, schedule_table)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "Configuration_Schedule {"
        "    AssignNAD {LSM} delay 15 ms;"
        "    AssignFrameIdRange {LSM, 0} delay 15 ms;"
        "    AssignFrameId {RSM, CEM_Frm1} delay 15 ms;"
        "}"
    };
    schedule_table_t schedule_table;

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::schedule_table, x3::ascii::space, schedule_table);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(schedule_table.schedule_table_name.c_str(), "Configuration_Schedule");
    ASSERT_EQ(schedule_table.table_entries.size(), 3);

    auto *assign_nad = std::get_if< schedule_table::command::assign_nad_t >(
        &(schedule_table.table_entries[0].command));
    ASSERT_NE(assign_nad, nullptr);
    EXPECT_STREQ(assign_nad->node_name.c_str(), "LSM");
    EXPECT_EQ(schedule_table.table_entries[0].frame_time, 15.0);

    auto *assign_frame_id_range = std::get_if< schedule_table::command::assign_frame_id_range_t >(
        &(schedule_table.table_entries[1].command));
    ASSERT_NE(assign_frame_id_range, nullptr);
    EXPECT_STREQ(assign_frame_id_range->node_name.c_str(), "LSM");
    EXPECT_EQ(assign_frame_id_range->frame_index, 0);
    EXPECT_EQ(assign_frame_id_range->frame_pids.size(), 0);
    EXPECT_EQ(schedule_table.table_entries[1].frame_time, 15.0);

    auto *assign_frame_id = std::get_if< schedule_table::command::assign_frame_id_t >(
        &(schedule_table.table_entries[2].command));
    ASSERT_NE(assign_frame_id, nullptr);
    EXPECT_STREQ(assign_frame_id->node_name.c_str(), "RSM");
    EXPECT_STREQ(assign_frame_id->frame_name.c_str(), "CEM_Frm1");
    EXPECT_EQ(schedule_table.table_entries[2].frame_time, 15.0);
}

TEST(test_lin_ldf_schedule_table_parser, schedule_tables)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "Schedule_tables {"
        "    MRF_schedule {"
        "        MasterReq delay 10 ms;"
        "    }"
        "    SRF_schedule {"
        "        SlaveResp delay 10 ms;"
        "    }"
        "}"
    };
    schedule_tables_t schedule_tables;

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::schedule_tables, x3::ascii::space, schedule_tables);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(schedule_tables.size(), 2);

    EXPECT_STREQ(schedule_tables[0].schedule_table_name.c_str(), "MRF_schedule");
    ASSERT_EQ(schedule_tables[0].table_entries.size(), 1);
    auto *master_req = std::get_if< schedule_table::command::master_req_t >(
        &(schedule_tables[0].table_entries[0].command));
    EXPECT_NE(master_req, nullptr);
    EXPECT_EQ(schedule_tables[0].table_entries[0].frame_time, 10.0);

    EXPECT_STREQ(schedule_tables[1].schedule_table_name.c_str(), "SRF_schedule");
    ASSERT_EQ(schedule_tables[1].table_entries.size(), 1);
    auto *slave_resp = std::get_if< schedule_table::command::slave_resp_t >(
        &(schedule_tables[1].table_entries[0].command));
    EXPECT_NE(slave_resp, nullptr);
    EXPECT_EQ(schedule_tables[1].table_entries[0].frame_time, 10.0);
}
