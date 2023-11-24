#pragma once

#include <lin/ldf/validate/check.hpp>

/* 9.2.3.2 Diagnostic signals */

namespace lin::ldf::validate::signal::diagnostic {

class size_t: public check::diagnostic_signal_t
{
  public:
    explicit size_t(common::validate::logger_t &logger):
        check::diagnostic_signal_t{ logger, "size" }
    {
    }

    void run(const ldf::signal::diagnostic_t &signal) const final;
};

class init_value_t: public check::diagnostic_signal_t
{
  public:
    explicit init_value_t(common::validate::logger_t &logger):
        check::diagnostic_signal_t{ logger, "init_value" }
    {
    }

    void run(const ldf::signal::diagnostic_t &signal) const final;
};

}    // namespace lin::ldf::validate::signal::diagnostic
