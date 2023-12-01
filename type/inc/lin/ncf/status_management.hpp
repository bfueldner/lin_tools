#pragma once

#include <vector>

#include <lin/common/bnf.hpp>

/* 8.2.6 Status management */

namespace lin::ncf {

namespace status_management {

using response_error_t      = common::bnf::identifier_t;
using fault_state_signals_t = std::vector< common::bnf::identifier_t >;

}    // namespace status_management

struct status_management_t
{
    status_management::response_error_t response_error{};
    status_management::fault_state_signals_t fault_state_signals{};
};

}    // namespace lin::ncf
