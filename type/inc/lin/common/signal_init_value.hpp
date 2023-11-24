#pragma once

#include <variant>
#include <vector>

#include <lin/common/bnf.hpp>
#include <lin/common/signal_encoding.hpp>

/* Common signal init value definition */

namespace lin::common::signal {

namespace init_value {

using scalar_t = common::bnf::integer_t;
using array_t  = std::vector< common::bnf::integer_t >;

}    // namespace init_value

using init_value_t = std::variant< init_value::scalar_t, init_value::array_t >;

}    // namespace lin::common::signal
