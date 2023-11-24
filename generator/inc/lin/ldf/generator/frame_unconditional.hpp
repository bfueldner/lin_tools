#pragma once

#include <iostream>

#include <lin/ldf/frame_unconditional.hpp>

/* 9.2.4.1 Unconditional frames */

namespace lin::ldf::frame {

namespace unconditional {

std::ostream &operator<<(std::ostream &out, signal_t const &signal);
std::ostream &operator<<(std::ostream &out, signals_t const &signals);

}    // namespace unconditional

std::ostream &operator<<(std::ostream &out, unconditional_t const &unconditional);
std::ostream &operator<<(std::ostream &out, unconditionals_t const &unconditionals);

}    // namespace lin::ldf::frame
