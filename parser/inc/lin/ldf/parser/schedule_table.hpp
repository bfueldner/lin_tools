#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>

#include <lin/ldf/schedule_table.hpp>

/* 9.2.5 Schedule table definition */

namespace lin::ldf {

namespace schedule_table {

namespace command::parser {

//namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

x3::rule< class master_req, master_req_t > const master_req = "master_req";
x3::rule< class slave_resp, slave_resp_t > const slave_resp = "slave_resp";
x3::rule< class assign_nad, assign_nad_t > const assign_nad = "assign_nad";
x3::rule< class conditional_change_nad, conditional_change_nad_t > const conditional_change_nad =
    "conditional_change_nad";
x3::rule< class data_dump, data_dump_t > const data_dump = "data_dump";
x3::rule< class save_configuration, save_configuration_t > const save_configuration =
    "save_configuration";
x3::rule< class assign_frame_id_range, assign_frame_id_range_t > const assign_frame_id_range =
    "assign_frame_id_range";
x3::rule< class free_format, free_format_t > const free_format             = "free_format";
x3::rule< class assign_frame_id, assign_frame_id_t > const assign_frame_id = "assign_frame_id";

auto const node_name   = identifier;
auto const nad         = integer;
auto const id          = integer;
auto const byte        = integer;
auto const mask        = integer;
auto const inv         = integer;
auto const new_nad     = integer;
auto const d1          = integer;
auto const d2          = integer;
auto const d3          = integer;
auto const d4          = integer;
auto const d5          = integer;
auto const d6          = integer;
auto const d7          = integer;
auto const d8          = integer;
auto const frame_name  = identifier;
auto const frame_index = integer;
auto const frame_pid   = integer;

auto const master_req_def             = x3::omit[x3::lit("MasterReq")];
auto const slave_resp_def             = x3::omit[x3::lit("SlaveResp")];
auto const assign_nad_def             = x3::lit("AssignNAD") > '{' > node_name > '}' > x3::attr(0);
auto const conditional_change_nad_def = x3::lit("ConditionalChangeNAD") > '{' > nad > ',' > id >
                                        ',' > byte > ',' > mask > ',' > inv > ',' > new_nad > '}';
auto const data_dump_def = x3::lit("DataDump") > '{' > node_name > ',' > d1 > ',' > d2 > ',' > d3 >
                           ',' > d4 > ',' > d5 > '}';
auto const save_configuration_def = x3::lit("SaveConfiguration") > '{' > node_name > '}' >
                                    x3::attr(0);
auto const assign_frame_id_range_def = x3::lit("AssignFrameIdRange") > '{' > node_name > ',' >
                                       frame_index > *(',' > frame_pid) > '}';
auto const free_format_def = x3::lit("FreeFormat") > '{' > d1 > ',' > d2 > ',' > d3 > ',' > d4 >
                             ',' > d5 > ',' > d6 > ',' > d7 > ',' > d8 > '}';
auto const assign_frame_id_def = x3::lit("AssignFrameId") > '{' > node_name > ',' > frame_name >
                                 '}';

BOOST_SPIRIT_DEFINE(
    master_req,
    slave_resp,
    assign_nad,
    conditional_change_nad,
    data_dump,
    save_configuration,
    assign_frame_id_range,
    free_format,
    assign_frame_id);

}    // namespace command::parser

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;
using namespace command::parser;

x3::rule< class command, command_t > const command             = "command";
x3::rule< class table_entry, table_entry_t > const table_entry = "table_entry";

auto const frame_time = real_or_integer;

auto const command_def = master_req | slave_resp | assign_nad | conditional_change_nad | data_dump |
                         save_configuration | assign_frame_id_range | free_format |
                         assign_frame_id | x3::no_skip[frame_name];
auto const table_entry_def = command > x3::lit("delay") > frame_time > "ms" > ';';

BOOST_SPIRIT_DEFINE(command, table_entry);

}    // namespace parser

}    // namespace schedule_table

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;
using namespace schedule_table::parser;

x3::rule< class schedule_table, schedule_table_t > const schedule_table    = "schedule_table";
x3::rule< class schedule_tables, schedule_tables_t > const schedule_tables = "schedule_tables";

auto const schedule_table_name = identifier;

auto const schedule_table_def  = schedule_table_name > '{' > *table_entry > '}';
auto const schedule_tables_def = x3::lit("Schedule_tables") > '{' > *schedule_table > '}';

BOOST_SPIRIT_DEFINE(schedule_table, schedule_tables);

}    // namespace parser

}    // namespace lin::ldf

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::schedule_table::command::assign_nad_t, node_name, _)

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::schedule_table::command::conditional_change_nad_t,
    nad,
    id,
    byte,
    mask,
    inv,
    new_nad)

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::schedule_table::command::data_dump_t,
    node_name,
    d1,
    d2,
    d3,
    d4,
    d5)

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::schedule_table::command::save_configuration_t, node_name, _)

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::schedule_table::command::assign_frame_id_range_t,
    node_name,
    frame_index,
    frame_pids)

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

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::schedule_table::command::assign_frame_id_t,
    node_name,
    frame_name)

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::schedule_table::table_entry_t, command, frame_time)

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::schedule_table_t, schedule_table_name, table_entries);
