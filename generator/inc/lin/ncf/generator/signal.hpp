#pragma once

#include <iostream>

#include <lin/ncf/signal.hpp>

namespace lin::ncf {

/* 8.2.5.2 Signal definition */

namespace signal {

std::ostream &operator<<(std::ostream &out, init_value_array_t const &init_value_array);
std::ostream &operator<<(std::ostream &out, init_value_t const &init_value);

std::ostream &operator<<(std::ostream &out, signal_properties_t const &signal_properties);

}    // namespace signal

std::ostream &operator<<(std::ostream &out, signal_t const &signal);
std::ostream &operator<<(std::ostream &out, signals_t const &signals);

/* 8.2.5.3 Signal encoding type definition */

namespace signal_encoding_type {

std::ostream &operator<<(std::ostream &out, encoding_t const &encoding);
std::ostream &operator<<(std::ostream &out, encodings_t const &encodings);

}    // namespace signal_encoding_type

}    // namespace lin::ncf
