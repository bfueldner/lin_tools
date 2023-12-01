#pragma once

#include <istream>

#include <lin/common/command/type.hpp>

namespace lin::common::command {

std::istream &operator>>(std::istream &in, type_t &type);
std::istream &operator>>(std::istream &in, export_type_t &type);

std::ostream &operator<<(std::ostream &out, const type_t &type);
std::ostream &operator<<(std::ostream &out, const export_type_t &type);

}    // namespace lin::common::command
