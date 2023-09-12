#pragma once

#include <variant>
#include <vector>

#include <lin/type/common/bnf.hpp>

/* 9.2.5 Schedule table definition */

namespace lin::type::ldf {

namespace schedule_table {

namespace command {

struct master_req_t
{
};

struct slave_resp_t
{
};

struct assign_nad_t
{
    common::bnf::identifier_t node_name{};
    common::bnf::integer_t _{}; /* Workaround for https://github.com/boostorg/spirit/issues/716 */
};

struct conditional_change_nad_t
{
    common::bnf::integer_t nad{};
    common::bnf::integer_t id{};
    common::bnf::integer_t byte{};
    common::bnf::integer_t mask{};
    common::bnf::integer_t inv{};
    common::bnf::integer_t new_nad{};
};

struct data_dump_t
{
    common::bnf::identifier_t node_name{};
    common::bnf::integer_t d1{};
    common::bnf::integer_t d2{};
    common::bnf::integer_t d3{};
    common::bnf::integer_t d4{};
    common::bnf::integer_t d5{};
};

struct save_configuration_t
{
    common::bnf::identifier_t node_name{};
    common::bnf::integer_t _{}; /* Workaround for https://github.com/boostorg/spirit/issues/716 */
};

struct assign_frame_id_range_t
{
    common::bnf::identifier_t node_name{};
    common::bnf::integer_t frame_index{};
    std::vector< common::bnf::integer_t > frame_pids{};
};

struct free_format_t
{
    common::bnf::integer_t d1{};
    common::bnf::integer_t d2{};
    common::bnf::integer_t d3{};
    common::bnf::integer_t d4{};
    common::bnf::integer_t d5{};
    common::bnf::integer_t d6{};
    common::bnf::integer_t d7{};
    common::bnf::integer_t d8{};
};

struct assign_frame_id_t
{
    common::bnf::identifier_t node_name{};
    common::bnf::identifier_t frame_name{};
};

using identifier_t = common::bnf::identifier_t;

}    // namespace command

using command_t = std::variant<
    command::identifier_t,
    command::master_req_t,
    command::slave_resp_t,
    command::assign_nad_t,
    command::conditional_change_nad_t,
    command::data_dump_t,
    command::save_configuration_t,
    command::assign_frame_id_range_t,
    command::free_format_t,
    command::assign_frame_id_t >;

namespace table_entry {

using frame_time_t = common::bnf::real_or_integer_t;

}    // namespace table_entry

struct table_entry_t
{
    schedule_table::command_t command{};
    table_entry::frame_time_t frame_time{};
};

using schedule_table_name_t = common::bnf::identifier_t;

}    // namespace schedule_table

struct schedule_table_t
{
    schedule_table::schedule_table_name_t schedule_table_name;
    std::vector< schedule_table::table_entry_t > table_entries;
};

using schedule_tables_t = std::vector< schedule_table_t >;

}    // namespace lin::type::ldf
