#pragma once

#include <lin/common/validate/check.hpp>
#include <lin/ldf/schedule_table.hpp>
#include <lin/ldf/validate/check.hpp>

namespace lin::ldf::validate::schedule_table::entry {

class command_node_t: public ldf::validate::check::schedule_table_entry_t
{
  public:
    explicit command_node_t(common::validate::logger_t &logger):
        ldf::validate::check::schedule_table_entry_t{ logger, "command_node" }
    {
    }

    void run(
        const ldf::nodes_t &nodes,
        const ldf::frame::unconditionals_t & /*unused*/,
        const ldf::frame::sporadics_t & /*unused*/,
        const ldf::frame::event_triggereds_t & /*unused*/,
        const ldf::schedule_table::entry_t &entry) const final;
};

class command_frame_t: public ldf::validate::check::schedule_table_entry_t
{
  public:
    explicit command_frame_t(common::validate::logger_t &logger):
        ldf::validate::check::schedule_table_entry_t{ logger, "command_frame" }
    {
    }

    void run(
        const ldf::nodes_t & /*unused*/,
        const ldf::frame::unconditionals_t &unconditional_frames,
        const ldf::frame::sporadics_t &sporadic_frames,
        const ldf::frame::event_triggereds_t &event_triggered_frames,
        const ldf::schedule_table::entry_t &entry) const final;
};

class command_values_t: public ldf::validate::check::schedule_table_entry_t
{
  public:
    using name_value_t = std::pair< std::string, int >;

    explicit command_values_t(common::validate::logger_t &logger):
        ldf::validate::check::schedule_table_entry_t{ logger, "command_values" }
    {
    }

    void run(
        const ldf::nodes_t & /*unused*/,
        const ldf::frame::unconditionals_t & /*unused*/,
        const ldf::frame::sporadics_t & /*unused*/,
        const ldf::frame::event_triggereds_t & /*unused*/,
        const ldf::schedule_table::entry_t &entry) const final;

    void run(const ldf::schedule_table::command::master_req_t & /*unused*/) const {}
    void run(const ldf::schedule_table::command::slave_resp_t & /*unused*/) const {}
    void run(const ldf::schedule_table::command::assign_nad_t & /*unused*/) const {}
    void run(
        const ldf::schedule_table::command::conditional_change_nad_t &conditional_change_nad) const;
    void run(const ldf::schedule_table::command::data_dump_t &data_dump) const;
    void run(const ldf::schedule_table::command::save_configuration_t & /*unused*/) const {}
    void run(
        const ldf::schedule_table::command::assign_frame_id_range_t &assign_frame_id_range) const;
    void run(const ldf::schedule_table::command::free_format_t &free_format) const;
    void run(const ldf::schedule_table::command::assign_frame_id_t & /*unused*/) const {}
    void run(const ldf::schedule_table::command::identifier_t & /*unused*/) const {}

    void check(const std::string &command, const std::vector< name_value_t > &name_values) const;
};

class delay_t:
    public common::validate::check_min_equal_t<
        ldf::schedule_table::entry_t,
        ldf::schedule_table::entry::delay_t,
        &ldf::schedule_table::entry_t::delay,
        0,
        ldf::nodes_t,
        ldf::frame::unconditionals_t,
        ldf::frame::sporadics_t,
        ldf::frame::event_triggereds_t >
{
  public:
    explicit delay_t(common::validate::logger_t &logger):
        common::validate::check_min_equal_t<
            ldf::schedule_table::entry_t,
            ldf::schedule_table::entry::delay_t,
            &ldf::schedule_table::entry_t::delay,
            0,
            ldf::nodes_t,
            ldf::frame::unconditionals_t,
            ldf::frame::sporadics_t,
            ldf::frame::event_triggereds_t >{ logger, "delay" }
    {
    }
};

}    // namespace lin::ldf::validate::schedule_table::entry
