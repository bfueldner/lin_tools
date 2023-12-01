#pragma once

#include <lin/ncf/validate/check.hpp>

/* 8.2.5.2 Signal definition */

namespace lin::ncf::validate::signal {

class init_value_t: public check::signal_t
{
  public:
    explicit init_value_t(common::validate::logger_t &logger):
        check::signal_t{ logger, "init_value" }
    {
    }

    void run(const ncf::signal_t &signal) const final;
};

class size_t: public check::signal_t
{
  public:
    static constexpr int min = 1;
    static constexpr int max = 64;

    explicit size_t(common::validate::logger_t &logger):
        check::signal_t{ logger, "size" }
    {
    }

    void run(const ncf::signal_t &signal) const final;
};

class offset_t: public check::signal_t
{
  public:
    static constexpr int min = 0;
    static constexpr int max = 63;

    explicit offset_t(common::validate::logger_t &logger):
        check::signal_t{ logger, "offset" }
    {
    }

    void run(const ncf::signal_t &signal) const final;
};

}    // namespace lin::ncf::validate::signal
