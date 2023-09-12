#pragma once

#include <iostream>

#include <lin/type/common/signal_encoding_type.hpp>

/* Common signal encoding type definition */

namespace lin::type::common::signal_encoding_type {

std::ostream &operator<<(std::ostream &out, logical_value_t const &logic_value);
std::ostream &operator<<(std::ostream &out, physical_range_t const &physical_range);
std::ostream &operator<<(std::ostream &out, bcd_value_t const &);
std::ostream &operator<<(std::ostream &out, ascii_value_t const &);
std::ostream &operator<<(std::ostream &out, value_t const &value);

}    // namespace lin::type::common::signal_encoding_type
