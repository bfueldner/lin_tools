#pragma once

#include <lin/ldf/validate/check.hpp>

/* 9.2.4.1 Unconditional frames */

namespace lin::ldf::validate::frame::unconditional {

class id_t:
    public common::validate::check_int_min_max_t<
        ldf::frame::unconditional_t,
        &ldf::frame::unconditional_t::id,
        0,
        59,
        ldf::nodes_t,
        ldf::signal::standards_t >
{
  public:
    explicit id_t(common::validate::logger_t &logger):
        common::validate::check_int_min_max_t<
            ldf::frame::unconditional_t,
            &ldf::frame::unconditional_t::id,
            0,
            59,
            ldf::nodes_t,
            ldf::signal::standards_t >{ logger, "id" }
    {
    }
};

class published_by_t:
    public check_node_name_t<
        ldf::frame::unconditional_t,
        &ldf::frame::unconditional_t::published_by,
        ldf::nodes_t,
        ldf::signal::standards_t >
{
  public:
    explicit published_by_t(common::validate::logger_t &logger):
        check_node_name_t<
            ldf::frame::unconditional_t,
            &ldf::frame::unconditional_t::published_by,
            ldf::nodes_t,
            ldf::signal::standards_t >{ logger, "published_by" }
    {
    }
};

class size_t:
    public common::validate::check_int_min_max_t<
        ldf::frame::unconditional_t,
        &ldf::frame::unconditional_t::size,
        1,
        64,
        ldf::nodes_t,
        ldf::signal::standards_t >
{
  public:
    explicit size_t(common::validate::logger_t &logger):
        common::validate::check_int_min_max_t<
            ldf::frame::unconditional_t,
            &ldf::frame::unconditional_t::size,
            1,
            64,
            ldf::nodes_t,
            ldf::signal::standards_t >{ logger, "size" }
    {
    }
};

class signal_published_by_t: public check::unconditional_frame_t
{
  public:
    explicit signal_published_by_t(common::validate::logger_t &logger):
        check::unconditional_frame_t{ logger, "signal_published_by" }
    {
    }

    void run(
        const ldf::nodes_t & /*unused*/,
        const ldf::signal::standards_t &standard_signals,
        const ldf::frame::unconditional_t &frame) const final;
};

class signal_sizes_t: public check::unconditional_frame_t
{
  public:
    explicit signal_sizes_t(common::validate::logger_t &logger):
        check::unconditional_frame_t{ logger, "signal_sizes" }
    {
    }

    void run(
        const ldf::nodes_t & /*unused*/,
        const ldf::signal::standards_t &signals,
        const ldf::frame::unconditional_t &frame) const final;
};

class signal_offsets_t: public check::unconditional_frame_t
{
  public:
    explicit signal_offsets_t(common::validate::logger_t &logger):
        check::unconditional_frame_t{ logger, "signal_offsets" }
    {
    }

    void run(
        const ldf::nodes_t & /*unused*/,
        const ldf::signal::standards_t &signals,
        const ldf::frame::unconditional_t &frame) const final;
};

class signals_t:
    public check_offsets_t<
        ldf::frame::unconditional_t,
        ldf::frame::unconditional::signal_t,
        &ldf::frame::unconditional_t::signals,
        ldf::nodes_t,
        ldf::signal::standards_t >
{
  public:
    explicit signals_t(common::validate::logger_t &logger):
        check_offsets_t<
            ldf::frame::unconditional_t,
            ldf::frame::unconditional::signal_t,
            &ldf::frame::unconditional_t::signals,
            ldf::nodes_t,
            ldf::signal::standards_t >{ logger, "signals" }
    {
    }
};

namespace signal {

class name_t:
    public common::validate::check_name_t<
        ldf::frame::unconditional::signal_t,
        &ldf::frame::unconditional::signal_t::name,
        0,
        ldf::signal::standards_t >
{
  public:
    explicit name_t(common::validate::logger_t &logger):
        common::validate::check_name_t<
            ldf::frame::unconditional::signal_t,
            &ldf::frame::unconditional::signal_t::name,
            0,
            ldf::signal::standards_t >{ logger, "name" }
    {
    }
};

class offset_t:
    public common::validate::check_int_min_max_t<
        ldf::frame::unconditional::signal_t,
        &ldf::frame::unconditional::signal_t::offset,
        0,
        63,
        ldf::signal::standards_t >
{
  public:
    explicit offset_t(common::validate::logger_t &logger):
        common::validate::check_int_min_max_t<
            ldf::frame::unconditional::signal_t,
            &ldf::frame::unconditional::signal_t::offset,
            0,
            63,
            ldf::signal::standards_t >{ logger, "offset" }
    {
    }
};

}    // namespace signal

}    // namespace lin::ldf::validate::frame::unconditional
