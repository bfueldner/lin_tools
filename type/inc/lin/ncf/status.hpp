#pragma once

#include <vector>

#include <lin/common/bnf.hpp>

/* 8.2.6 Status management */

namespace lin::ncf {

struct status_t
{
    common::bnf::identifier_t response_error{};
    std::vector< common::bnf::identifier_t > fault_state_signals{};
};

}    // namespace lin::ncf
