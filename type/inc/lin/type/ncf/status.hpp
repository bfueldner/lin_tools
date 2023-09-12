#pragma once

#include <vector>

#include <lin/type/common/bnf.hpp>

/* 8.2.6 Status management */

namespace lin::type::ncf {

struct status_t
{
    common::bnf::identifier_t response_error{};
    std::vector< common::bnf::identifier_t > fault_state_signals{};
};

}    // namespace lin::type::ncf
