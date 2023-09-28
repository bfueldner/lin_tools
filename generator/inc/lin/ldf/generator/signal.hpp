#pragma once

#include <iostream>

#include <lin/ldf/signal.hpp>

/* 9.2.3 Signal definition */

namespace lin::ldf::signal {

/* 9.2.3.1 Standard signals */

namespace standard_signal {

//std::ostream &operator<<(std::ostream &out, init_value_scalar_t const &init_value_scalar);
std::ostream &operator<<(std::ostream &out, init_value_array_t const &init_value_array);
std::ostream &operator<<(std::ostream &out, init_value_t const &init_value);

}    // namespace standard_signal

std::ostream &operator<<(std::ostream &out, standard_signal_t const &standard_signal);
std::ostream &operator<<(std::ostream &out, standard_signals_t const &standard_signals);

/* 9.2.3.2 Diagnostic signals */

std::ostream &operator<<(std::ostream &out, diagnostic_signal_t const &diagnostic_signal);
std::ostream &operator<<(std::ostream &out, diagnostic_signals_t const &diagnostic_signals);

/* 9.2.3.3 Signal groups */

namespace signal_group {

std::ostream &operator<<(std::ostream &out, group_entry_t const &group_entry);
std::ostream &operator<<(std::ostream &out, group_entries_t const &group_entries);

}    // namespace signal_group

std::ostream &operator<<(std::ostream &out, signal_group_t const &signal_group);
std::ostream &operator<<(std::ostream &out, signal_groups_t const &signal_groups);

/* 9.2.6.1 Signal encoding type definition */

std::ostream &operator<<(std::ostream &out, signal_encoding_type_t const &signal_encoding_type);
std::ostream &operator<<(std::ostream &out, signal_encoding_types_t const &signal_encoding_types);

/* 9.2.6.2 Signal representation definition */

std::ostream &operator<<(std::ostream &out, signal_representation_t const &signal_representation);
std::ostream &operator<<(std::ostream &out, signal_representations_t const &signal_representations);

}    // namespace lin::ldf::signal
