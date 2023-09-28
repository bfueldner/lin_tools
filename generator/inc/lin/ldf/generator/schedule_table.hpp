#pragma once

#include <iostream>

#include <lin/ldf/schedule_table.hpp>

/* 9.2.5 Schedule table definition */

namespace lin::ldf {

namespace schedule_table {

namespace command {

std::ostream &operator<<(std::ostream &out, master_req_t const & /* unused */);
std::ostream &operator<<(std::ostream &out, slave_resp_t const & /* unused */);
std::ostream &operator<<(std::ostream &out, assign_nad_t const &assign_nad);
std::ostream &operator<<(std::ostream &out, conditional_change_nad_t const &conditional_change_nad);
std::ostream &operator<<(std::ostream &out, data_dump_t const &data_dump);
std::ostream &operator<<(std::ostream &out, save_configuration_t const &save_configuration);
std::ostream &operator<<(std::ostream &out, assign_frame_id_range_t const &assign_frame_id_range);
std::ostream &operator<<(std::ostream &out, free_format_t const &free_format);
std::ostream &operator<<(std::ostream &out, assign_frame_id_t const &assign_frame_id);

}    // namespace command

std::ostream &operator<<(std::ostream &out, command_t const &command);
std::ostream &operator<<(std::ostream &out, table_entry_t const &table_entry);

}    // namespace schedule_table

std::ostream &operator<<(std::ostream &out, schedule_table_t const &schedule_table);
std::ostream &operator<<(std::ostream &out, schedule_tables_t const &schedule_tables);

}    // namespace lin::ldf
