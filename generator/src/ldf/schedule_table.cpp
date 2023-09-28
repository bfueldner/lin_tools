#include <iomanip>
#include <ios>
#include <ostream>
#include <variant>

#include <lin/ldf/schedule_table.hpp>

#include <lin/common/generator/indention.hpp>
#include <lin/ldf/generator/schedule_table.hpp>

/* 9.2.5 Schedule table definition */

namespace lin::ldf {

namespace schedule_table {

namespace command {

std::ostream &operator<<(std::ostream &out, master_req_t const & /*unused*/)
{
    out << "MasterReq";
    return out;
}

std::ostream &operator<<(std::ostream &out, slave_resp_t const & /*unused*/)
{
    out << "SlaveResp";
    return out;
}

std::ostream &operator<<(std::ostream &out, assign_nad_t const &assign_nad)
{
    out << "AssignNAD { " << assign_nad.node_name << " }";
    return out;
}

std::ostream &operator<<(std::ostream &out, conditional_change_nad_t const &conditional_change_nad)
{
    out << "ConditionalChangeNAD { " << std::hex << std::setfill('0') << "0x" << std::setw(2)
        << conditional_change_nad.nad << ", 0x" << std::setw(2) << conditional_change_nad.id
        << ", 0x" << std::setw(2) << conditional_change_nad.byte << ", 0x" << std::setw(2)
        << conditional_change_nad.mask << ", 0x" << std::setw(2) << conditional_change_nad.inv
        << ", 0x" << std::setw(2) << conditional_change_nad.new_nad << std::dec << " }";
    return out;
}

std::ostream &operator<<(std::ostream &out, data_dump_t const &data_dump)
{
    out << "DataDump { " << data_dump.node_name << ", " << std::hex << std::setfill('0') << "0x"
        << std::setw(2) << data_dump.d1 << ", 0x" << std::setw(2) << data_dump.d2 << ", 0x"
        << std::setw(2) << data_dump.d3 << ", 0x" << std::setw(2) << data_dump.d4 << ", 0x"
        << std::setw(2) << data_dump.d5 << std::dec << " }";
    return out;
}

std::ostream &operator<<(std::ostream &out, save_configuration_t const &save_configuration)
{
    out << "SaveConfiguration { " << save_configuration.node_name << " }";
    return out;
}

std::ostream &operator<<(std::ostream &out, assign_frame_id_range_t const &assign_frame_id_range)
{
    out << "AssignFrameIdRange { " << assign_frame_id_range.node_name << ", "
        << assign_frame_id_range.frame_index << std::hex << std::setfill('0');
    for (auto const &frame_pid : assign_frame_id_range.frame_pids)
    {
        out << ", 0x" << std::setw(2) << frame_pid;
    }
    out << std::dec << " }";
    return out;
}

std::ostream &operator<<(std::ostream &out, free_format_t const &free_format)
{
    out << "FreeFormat { " << std::hex << std::setfill('0') << "0x" << std::setw(2)
        << free_format.d1 << ", 0x" << std::setw(2) << free_format.d2 << ", 0x" << std::setw(2)
        << free_format.d3 << ", 0x" << std::setw(2) << free_format.d4 << ", 0x" << std::setw(2)
        << free_format.d5 << ", 0x" << std::setw(2) << free_format.d6 << ", 0x" << std::setw(2)
        << free_format.d7 << ", 0x" << std::setw(2) << free_format.d8 << std::dec << " }";
    return out;
}

std::ostream &operator<<(std::ostream &out, assign_frame_id_t const &assign_frame_id)
{
    out << "AssignFrameId { " << assign_frame_id.node_name << ", " << assign_frame_id.frame_name
        << " }";
    return out;
}

}    // namespace command

std::ostream &operator<<(std::ostream &out, command_t const &command)
{
    using namespace command;

    std::visit([&out](auto &&arg) { out << arg; }, command);
    return out;
}

std::ostream &operator<<(std::ostream &out, table_entry_t const &table_entry)
{
    out << common::indention_t::indent << table_entry.command << " delay " << table_entry.frame_time
        << " ms;\n";
    return out;
}

}    // namespace schedule_table

std::ostream &operator<<(std::ostream &out, schedule_table_t const &schedule_table)
{
    out << common::indention_t::indent << common::indention_t::push
        << schedule_table.schedule_table_name << " {\n";
    for (auto const &table_entry : schedule_table.table_entries)
    {
        out << table_entry;
    }
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, schedule_tables_t const &schedule_tables)
{
    out << common::indention_t::push << "Schedule_tables {\n";
    for (auto const &schedule_table : schedule_tables)
    {
        out << schedule_table;
    }
    out << common::indention_t::pop << "}\n";
    return out;
}

}    // namespace lin::ldf
