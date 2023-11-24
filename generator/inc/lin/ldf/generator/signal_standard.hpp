#pragma once

#include <iostream>

#include <lin/ldf/signal_standard.hpp>

/* 9.2.3.1 Standard signals */

namespace lin::ldf::signal {

std::ostream &operator<<(std::ostream &out, standard_t const &standard);
std::ostream &operator<<(std::ostream &out, standards_t const &standards);

}    // namespace lin::ldf::signal
