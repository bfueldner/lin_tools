#pragma once

#include <iostream>

#include <lin/ncf/signal.hpp>

/* 8.2.5.2 Signal definition */

namespace lin::ncf {

std::ostream &operator<<(std::ostream &out, signal_t const &signal);
std::ostream &operator<<(std::ostream &out, signals_t const &signals);

}    // namespace lin::ncf
