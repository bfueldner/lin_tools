#pragma once

#include <iostream>

#include <lin/ldf/signal_encoding.hpp>

/* 9.2.6.1 Signal encoding type definition */

namespace lin::ldf::signal {

std::ostream &operator<<(std::ostream &out, encoding_t const &encoding);
std::ostream &operator<<(std::ostream &out, encodings_t const &encodings);

}    // namespace lin::ldf::signal
