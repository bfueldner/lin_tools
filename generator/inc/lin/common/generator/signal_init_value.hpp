#pragma once

#include <iostream>

#include <lin/common/signal_init_value.hpp>

/* Common signal init value definition */

namespace lin::common::signal {

namespace init_value {

std::ostream &operator<<(std::ostream &out, array_t const &array);

}    // namespace init_value

std::ostream &operator<<(std::ostream &out, init_value_t const &init_value);

}    // namespace lin::common::signal
