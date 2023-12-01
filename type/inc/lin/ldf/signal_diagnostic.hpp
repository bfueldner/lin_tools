#pragma once

#include <vector>

#include <lin/common/bnf.hpp>
#include <lin/common/signal_init_value.hpp>

/* 9.2.3.2 Diagnostic signals */

namespace lin::ldf::signal {

namespace diagnostic {

namespace init_value {

using scalar_t = common::signal::init_value::scalar_t;
using array_t  = common::signal::init_value::array_t;

}    // namespace init_value

using name_t       = common::bnf::identifier_t;
using size_t       = common::bnf::integer_t;
using init_value_t = common::signal::init_value_t;

}    // namespace diagnostic

struct diagnostic_t
{
    diagnostic::name_t name{};
    diagnostic::size_t size{};
    diagnostic::init_value_t init_value{};
};

using diagnostics_t = std::vector< diagnostic_t >;

}    // namespace lin::ldf::signal
