#include <string>
#include <type_traits>
#include <variant>
#include <vector>

#include <lin/ldf/frame_event_triggered.hpp>
#include <lin/ldf/frame_sporadic.hpp>
#include <lin/ldf/frame_unconditional.hpp>
#include <lin/ldf/nodes.hpp>
#include <lin/ldf/schedule_table.hpp>
#include <lin/ldf/validate/schedule_table.hpp>

namespace lin::ldf::validate::schedule_table::entry {

void command_node_t::run(
    const ldf::nodes_t &nodes,
    const frame::unconditionals_t & /*unused*/,
    const frame::sporadics_t & /*unused*/,
    const frame::event_triggereds_t & /*unused*/,
    const ldf::schedule_table::entry_t &entry) const
{
    auto node = [](auto &&arg) {
        using T = std::decay_t< decltype(arg) >;

        if constexpr (
            std::is_same_v< T, lin::ldf::schedule_table::command::assign_nad_t > ||
            std::is_same_v< T, lin::ldf::schedule_table::command::data_dump_t > ||
            std::is_same_v< T, lin::ldf::schedule_table::command::save_configuration_t > ||
            std::is_same_v< T, lin::ldf::schedule_table::command::assign_frame_id_range_t > ||
            std::is_same_v< T, lin::ldf::schedule_table::command::assign_frame_id_t >)
        {
            return arg.node;
        }

        return std::string{};
    };

    auto command_node = std::visit(node, entry.command);
    if (command_node.empty())
    {
        return;
    }

    auto found = nodes.master.name == command_node;
    if (!found)
    {
        for (auto const &slave : nodes.slaves)
        {
            if (slave == command_node)
            {
                found = true;
                break;
            }
        }
    }

    if (!found)
    {
        _log_error("Not defined", command_node);
        return;
    }

    _log_ok();
}

void command_frame_t::run(
    const ldf::nodes_t & /*unused*/,
    const frame::unconditionals_t &unconditional_frames,
    const frame::sporadics_t &sporadic_frames,
    const frame::event_triggereds_t &event_triggered_frames,
    const ldf::schedule_table::entry_t &entry) const
{
    auto frame = [](auto &&arg) {
        using T = std::decay_t< decltype(arg) >;

        if constexpr (std::is_same_v< T, lin::ldf::schedule_table::command::assign_frame_id_t >)
        {
            return arg.frame;
        }
        else if constexpr (std::is_same_v< T, lin::ldf::schedule_table::command::identifier_t >)
        {
            return arg;
        }
        return std::string{};
    };

    auto command_frame = std::visit(frame, entry.command);

    if (command_frame.empty())
    {
        return;
    }

    auto found{ false };

    for (auto const &frame : unconditional_frames)
    {
        if (frame.name == command_frame)
        {
            found = true;
            break;
        }
    }

    if (!found)
    {
        for (auto const &frame : sporadic_frames)
        {
            if (frame.name == command_frame)
            {
                found = true;
                break;
            }
        }
    }

    if (!found)
    {
        for (auto const &frame : event_triggered_frames)
        {
            if (frame.name == command_frame)
            {
                found = true;
                break;
            }
        }
    }

    if (!found)
    {
        _log_error("Not defined", command_frame);
        return;
    }

    _log_ok();
}

void command_values_t::run(
    const ldf::nodes_t & /*unused*/,
    const frame::unconditionals_t & /*unused*/,
    const frame::sporadics_t & /*unused*/,
    const frame::event_triggereds_t & /*unused*/,
    const ldf::schedule_table::entry_t &entry) const
{
    std::visit([this](auto &&arg) { run(arg); }, entry.command);
}

void command_values_t::run(
    const ldf::schedule_table::command::conditional_change_nad_t &conditional_change_nad) const
{
    const std::vector< name_value_t > name_values{
        { "NAD", conditional_change_nad.nad },   { "id", conditional_change_nad.id },
        { "byte", conditional_change_nad.byte }, { "mask", conditional_change_nad.mask },
        { "inv", conditional_change_nad.inv },   { "new_NAD", conditional_change_nad.new_nad }
    };

    check("ConditionalChangeNAD", name_values);
}

void command_values_t::run(const ldf::schedule_table::command::data_dump_t &data_dump) const
{
    const std::vector< name_value_t > name_values{ { "D1", data_dump.d1 },
                                                   { "D2", data_dump.d2 },
                                                   { "D3", data_dump.d3 },
                                                   { "D4", data_dump.d4 },
                                                   { "D5", data_dump.d5 } };

    check("DataDump", name_values);
}

void command_values_t::run(
    const ldf::schedule_table::command::assign_frame_id_range_t &assign_frame_id_range) const
{
    std::vector< name_value_t > name_values{ { "frame_index", assign_frame_id_range.index } };
    for (auto const &pid : assign_frame_id_range.pids)
    {
        name_values.emplace_back("frame_PID", pid);
    }

    check("AssignFrameIdRange", name_values);
}

void command_values_t::run(const ldf::schedule_table::command::free_format_t &free_format) const
{
    const std::vector< name_value_t > name_values{
        { "D1", free_format.d1 }, { "D2", free_format.d2 }, { "D3", free_format.d3 },
        { "D4", free_format.d4 }, { "D5", free_format.d5 }, { "D6", free_format.d6 },
        { "D7", free_format.d7 }, { "D8", free_format.d8 }
    };

    check("FreeFormat", name_values);
}

void command_values_t::check(
    const std::string &command,
    const std::vector< name_value_t > &name_values) const
{
    std::vector< std::string > names{};

    for (auto const &name_value : name_values)
    {
        if ((name_value.second < 0) || (name_value.second > 255))
        {
            names.push_back(name_value.first);
        }
    }

    if (!names.empty())
    {
        _log_error(command + " member out of range", _to_string(names), "0..255");
        return;
    }

    _log_ok();
}

}    // namespace lin::ldf::validate::schedule_table::entry
