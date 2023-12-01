#pragma once

#include <iostream>

#include <lin/ldf/signal_representation.hpp>

/* 9.2.6.2 Signal representation definition */

namespace lin::ldf::signal {

std::ostream &operator<<(std::ostream &out, representation_t const &representation);
std::ostream &operator<<(std::ostream &out, representations_t const &representations);

}    // namespace lin::ldf::signal
