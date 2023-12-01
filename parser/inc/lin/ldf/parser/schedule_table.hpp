#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/ldf/schedule_table.hpp>

/* 9.2.5 Schedule table definition */

namespace lin::ldf::parser {

using namespace common::parser;

x3::rule< class schedule_table_command_master_req, schedule_table::command::master_req_t > const
    schedule_table_command_master_req = "schedule_table_command_master_req";
x3::rule< class schedule_table_command_slave_resp, schedule_table::command::slave_resp_t > const
    schedule_table_command_slave_resp = "schedule_table_command_slave_resp";
x3::rule< class schedule_table_command_assign_nad, schedule_table::command::assign_nad_t > const
    schedule_table_command_assign_nad = "schedule_table_command_assign_nad";
x3::rule<
    class schedule_table_command_conditional_change_nad,
    schedule_table::command::conditional_change_nad_t > const
    schedule_table_command_conditional_change_nad = "schedule_table_command_conditional_change_nad";
x3::rule< class schedule_table_command_data_dump, schedule_table::command::data_dump_t > const
    schedule_table_command_data_dump = "schedule_table_command_data_dump";
x3::rule<
    class schedule_table_command_save_configuration,
    schedule_table::command::save_configuration_t > const
    schedule_table_command_save_configuration = "schedule_table_command_save_configuration";
x3::rule<
    class schedule_table_command_assign_frame_id_range,
    schedule_table::command::assign_frame_id_range_t > const
    schedule_table_command_assign_frame_id_range = "schedule_table_command_assign_frame_id_range";
x3::rule< class schedule_table_command_free_format, schedule_table::command::free_format_t > const
    schedule_table_command_free_format = "schedule_table_command_free_format";
x3::rule<
    class schedule_table_command_assign_frame_id,
    schedule_table::command::assign_frame_id_t > const schedule_table_command_assign_frame_id =
    "schedule_table_command_assign_frame_id";
x3::rule< class schedule_table_command, schedule_table::command_t > const schedule_table_command =
    "schedule_table_command";
x3::rule< class schedule_table_entry, schedule_table::entry_t > const schedule_table_entry =
    "schedule_table_entry";
x3::rule< class schedule_table, schedule_table_t > const schedule_table    = "schedule_table";
x3::rule< class schedule_tables, schedule_tables_t > const schedule_tables = "schedule_tables";

auto const schedule_table_command_node_name   = identifier;
auto const schedule_table_command_nad         = integer;
auto const schedule_table_command_id          = integer;
auto const schedule_table_command_byte        = integer;
auto const schedule_table_command_mask        = integer;
auto const schedule_table_command_inv         = integer;
auto const schedule_table_command_new_nad     = integer;
auto const schedule_table_command_d1          = integer;
auto const schedule_table_command_d2          = integer;
auto const schedule_table_command_d3          = integer;
auto const schedule_table_command_d4          = integer;
auto const schedule_table_command_d5          = integer;
auto const schedule_table_command_d6          = integer;
auto const schedule_table_command_d7          = integer;
auto const schedule_table_command_d8          = integer;
auto const schedule_table_command_frame_name  = identifier;
auto const schedule_table_command_frame_index = integer;
auto const schedule_table_command_frame_pid   = integer;
auto const schedule_table_command_delay       = real_or_integer;

auto const schedule_table_command_master_req_def = x3::omit[x3::lit("MasterReq")];
auto const schedule_table_command_slave_resp_def = x3::omit[x3::lit("SlaveResp")];
auto const schedule_table_command_assign_nad_def = x3::lit("AssignNAD") > '{' >
                                                   schedule_table_command_node_name > '}' >
                                                   x3::attr(0);
auto const schedule_table_command_conditional_change_nad_def =
    x3::lit("ConditionalChangeNAD") > '{' > schedule_table_command_nad > ',' >
    schedule_table_command_id > ',' > schedule_table_command_byte > ',' >
    schedule_table_command_mask > ',' > schedule_table_command_inv > ',' >
    schedule_table_command_new_nad > '}';
auto const schedule_table_command_data_dump_def =
    x3::lit("DataDump") > '{' > schedule_table_command_node_name > ',' > schedule_table_command_d1 >
    ',' > schedule_table_command_d2 > ',' > schedule_table_command_d3 > ',' >
    schedule_table_command_d4 > ',' > schedule_table_command_d5 > '}';
auto const schedule_table_command_save_configuration_def = x3::lit("SaveConfiguration") > '{' >
                                                           schedule_table_command_node_name > '}' >
                                                           x3::attr(0);
auto const schedule_table_command_assign_frame_id_range_def =
    x3::lit("AssignFrameIdRange") > '{' > schedule_table_command_node_name > ',' >
    schedule_table_command_frame_index > *(',' > schedule_table_command_frame_pid) > '}';
auto const schedule_table_command_free_format_def =
    x3::lit("FreeFormat") > '{' > schedule_table_command_d1 > ',' > schedule_table_command_d2 >
    ',' > schedule_table_command_d3 > ',' > schedule_table_command_d4 > ',' >
    schedule_table_command_d5 > ',' > schedule_table_command_d6 > ',' > schedule_table_command_d7 >
    ',' > schedule_table_command_d8 > '}';
auto const schedule_table_command_assign_frame_id_def = x3::lit("AssignFrameId") > '{' >
                                                        schedule_table_command_node_name > ',' >
                                                        schedule_table_command_frame_name > '}';

auto const schedule_table_command_def =
    schedule_table_command_master_req | schedule_table_command_slave_resp |
    schedule_table_command_assign_nad | schedule_table_command_conditional_change_nad |
    schedule_table_command_data_dump | schedule_table_command_save_configuration |
    schedule_table_command_assign_frame_id_range | schedule_table_command_free_format |
    schedule_table_command_assign_frame_id | x3::no_skip[schedule_table_command_frame_name];
auto const schedule_table_entry_def = schedule_table_command >
                                      x3::lit("delay") > schedule_table_command_delay > "ms" > ';';

auto const schedule_table_name = identifier;

auto const schedule_table_def  = schedule_table_name > '{' > *schedule_table_entry > '}';
auto const schedule_tables_def = x3::lit("Schedule_tables") > '{' > *schedule_table > '}';

BOOST_SPIRIT_DEFINE(
    schedule_table_command_master_req,
    schedule_table_command_slave_resp,
    schedule_table_command_assign_nad,
    schedule_table_command_conditional_change_nad,
    schedule_table_command_data_dump,
    schedule_table_command_save_configuration,
    schedule_table_command_assign_frame_id_range,
    schedule_table_command_free_format,
    schedule_table_command_assign_frame_id)

BOOST_SPIRIT_DEFINE(schedule_table_command, schedule_table_entry)
BOOST_SPIRIT_DEFINE(schedule_table, schedule_tables)

}    // namespace lin::ldf::parser

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::schedule_table::command::assign_nad_t, node, _)

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::schedule_table::command::conditional_change_nad_t,
    nad,
    id,
    byte,
    mask,
    inv,
    new_nad)

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::schedule_table::command::data_dump_t, node, d1, d2, d3, d4, d5)

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::schedule_table::command::save_configuration_t, node, _)

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::schedule_table::command::assign_frame_id_range_t,
    node,
    index,
    pids)

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::schedule_table::command::free_format_t,
    d1,
    d2,
    d3,
    d4,
    d5,
    d6,
    d7,
    d8)

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::schedule_table::command::assign_frame_id_t, node, frame)

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::schedule_table::entry_t, command, delay)

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::schedule_table_t, name, entries);
