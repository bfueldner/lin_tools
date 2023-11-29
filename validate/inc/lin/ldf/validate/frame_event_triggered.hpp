#pragma once

#include <lin/ldf/validate/check.hpp>

/* 9.2.4.3 Event triggered frames */

namespace lin::ldf::validate::frame::event_triggered {

class schedule_table_t:
    public common::validate::check_name_t<
        ldf::frame::event_triggered_t,
        &ldf::frame::event_triggered_t::schedule_table,
        0,
        ldf::schedule_tables_t,
        ldf::frame::unconditionals_t >
{
  public:
    explicit schedule_table_t(common::validate::logger_t &logger):
        common::validate::check_name_t<
            ldf::frame::event_triggered_t,
            &ldf::frame::event_triggered_t::schedule_table,
            0,
            ldf::schedule_tables_t,
            ldf::frame::unconditionals_t >{ logger, "schedule_table" }
    {
    }
};

class id_t:
    public common::validate::check_int_min_max_t<
        ldf::frame::event_triggered_t,
        &ldf::frame::event_triggered_t::id,
        0,
        59,
        ldf::schedule_tables_t,
        ldf::frame::unconditionals_t >
{
  public:
    explicit id_t(common::validate::logger_t &logger):
        common::validate::check_int_min_max_t<
            ldf::frame::event_triggered_t,
            &ldf::frame::event_triggered_t::id,
            0,
            59,
            ldf::schedule_tables_t,
            ldf::frame::unconditionals_t >{ logger, "id" }
    {
    }
};

class frames_t:
    public common::validate::check_names_t<
        ldf::frame::event_triggered_t,
        &ldf::frame::event_triggered_t::frames,
        1,
        false,
        ldf::schedule_tables_t,
        ldf::frame::unconditionals_t >
{
  public:
    explicit frames_t(common::validate::logger_t &logger):
        common::validate::check_names_t<
            ldf::frame::event_triggered_t,
            &ldf::frame::event_triggered_t::frames,
            1,
            false,
            ldf::schedule_tables_t,
            ldf::frame::unconditionals_t >{ logger, "frames" }
    {
    }
};

}    // namespace lin::ldf::validate::frame::event_triggered
