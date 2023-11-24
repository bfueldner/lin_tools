#pragma once

#include <lin/ncf/validate/check.hpp>

/* 8.2.6 Status management */

namespace lin::ncf::validate::status_management {

class response_error_t: public check::status_management_t
{
  public:
    explicit response_error_t(common::validate::logger_t &logger):
        check::status_management_t{ logger, "response_error" }
    {
    }

    void run(const ncf::frames_t &frames, const ncf::status_management_t &status_management)
        const final;
};

class fault_state_signals_t: public check::status_management_t
{
  public:
    explicit fault_state_signals_t(common::validate::logger_t &logger):
        check::status_management_t{ logger, "fault_state_signals" }

    {
    }

    void run(const ncf::frames_t &frames, const ncf::status_management_t &status_management)
        const final;
};

}    // namespace lin::ncf::validate::status_management
