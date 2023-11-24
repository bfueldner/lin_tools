#pragma once

#include <lin/ldf/validate/check.hpp>

/* 9.2.3.3 Signal groups */

namespace lin::ldf::validate::signal::group {

class size_t:
    public common::validate::check_min_max_t<
        ldf::signal::group_t,
        ldf::signal::group::size_t,
        &ldf::signal::group_t::size,
        1,
        64,
        ldf::signal::standards_t >
{
  public:
    explicit size_t(common::validate::logger_t &logger):
        common::validate::check_min_max_t<
            ldf::signal::group_t,
            ldf::signal::group::size_t,
            &ldf::signal::group_t::size,
            1,
            64,
            ldf::signal::standards_t >{ logger, "size" }
    {
    }
};

class signal_sizes_t: public check::signal_group_t
{
  public:
    explicit signal_sizes_t(common::validate::logger_t &logger):
        check::signal_group_t{ logger, "signal_sizes" }
    {
    }

    void run(const ldf::signal::standards_t &signals, const ldf::signal::group_t &group)
        const final;
};

class signal_offsets_t: public check::signal_group_t
{
  public:
    explicit signal_offsets_t(common::validate::logger_t &logger):
        check::signal_group_t{ logger, "signal_offsets" }
    {
    }

    void run(const ldf::signal::standards_t &signals, const ldf::signal::group_t &group)
        const final;
};

class signals_t:
    public check_offsets_t<
        ldf::signal::group_t,
        ldf::signal::group::signal_t,
        &ldf::signal::group_t::signals,
        ldf::signal::standards_t >
{
  public:
    explicit signals_t(common::validate::logger_t &logger):
        check_offsets_t<
            ldf::signal::group_t,
            ldf::signal::group::signal_t,
            &ldf::signal::group_t::signals,
            ldf::signal::standards_t >{ logger, "signals" }
    {
    }
};

namespace signal {

class name_t:
    public common::validate::check_name_t<
        ldf::signal::group::signal_t,
        &ldf::signal::group::signal_t::name,
        0,
        ldf::signal::standards_t >
{
  public:
    explicit name_t(common::validate::logger_t &logger):
        common::validate::check_name_t<
            ldf::signal::group::signal_t,
            &ldf::signal::group::signal_t::name,
            0,
            ldf::signal::standards_t >{ logger, "name" }
    {
    }
};

class offset_t:
    public common::validate::check_int_min_max_t<
        ldf::signal::group::signal_t,
        &ldf::signal::group::signal_t::offset,
        0,
        63,
        ldf::signal::standards_t >
{
  public:
    explicit offset_t(common::validate::logger_t &logger):
        common::validate::check_int_min_max_t<
            ldf::signal::group::signal_t,
            &ldf::signal::group::signal_t::offset,
            0,
            63,
            ldf::signal::standards_t >{ logger, "offset" }
    {
    }
};

}    // namespace signal

}    // namespace lin::ldf::validate::signal::group
