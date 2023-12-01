#pragma once

#include <iostream>

#include <lin/ncf/signal_encoding.hpp>

/* 8.2.5.3 Signal encoding type definition */

namespace lin::ncf::signal {

std::ostream &operator<<(std::ostream &out, encoding_t const &encoding);
std::ostream &operator<<(std::ostream &out, encodings_t const &encodings);

}    // namespace lin::ncf::signal
