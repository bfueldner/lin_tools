#pragma once

#include <lin/ldf/validate/check.hpp>

/* 9.2.4.4 Diagnostic frames */

namespace lin::ldf::validate::frame::diagnostic {

class id_t:
    public common::validate::
        check_int_min_max_t< ldf::frame::diagnostic_t, &ldf::frame::diagnostic_t::id, 0x3C, 0x3D >
{
  public:
    explicit id_t(common::validate::logger_t &logger):
        common::validate::check_int_min_max_t<
            ldf::frame::diagnostic_t,
            &ldf::frame::diagnostic_t::id,
            0x3C,
            0x3D >{ logger, "id" }
    {
    }
};

class signals_t:
    public check_offsets_t<
        ldf::frame::diagnostic_t,
        ldf::frame::diagnostic::signal_t,
        &ldf::frame::diagnostic_t::signals >
{
  public:
    explicit signals_t(common::validate::logger_t &logger):
        check_offsets_t<
            ldf::frame::diagnostic_t,
            ldf::frame::diagnostic::signal_t,
            &ldf::frame::diagnostic_t::signals >{ logger, "signals" }
    {
    }
};

namespace signal {

class name_t:
    public common::validate::check_name_t<
        ldf::frame::diagnostic::signal_t,
        &ldf::frame::diagnostic::signal_t::name,
        0,
        ldf::signal::diagnostics_t >
{
  public:
    explicit name_t(common::validate::logger_t &logger):
        common::validate::check_name_t<
            ldf::frame::diagnostic::signal_t,
            &ldf::frame::diagnostic::signal_t::name,
            0,
            ldf::signal::diagnostics_t >{ logger, "name" }
    {
    }
};

class offset_t: public check::diagnostic_frame_signal_t
{
  public:
    static constexpr int min{ 0 };
    static constexpr int max{ 63 };

    explicit offset_t(common::validate::logger_t &logger):
        check::diagnostic_frame_signal_t{ logger, "offset" }
    {
    }

    void run(
        const ldf::signal::diagnostics_t &signals,
        const ldf::frame::diagnostic::signal_t &signal) const final;
};

}    // namespace signal

}    // namespace lin::ldf::validate::frame::diagnostic
