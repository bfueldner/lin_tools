#pragma once

#include <istream>

#include <lin/ncf/command/type.hpp>

namespace lin::ncf::command {

std::istream &operator>>(std::istream &in, command_t &command);
std::istream &operator>>(std::istream &in, type_t &type);

std::ostream &operator<<(std::ostream &out, const command_t &command);
std::ostream &operator<<(std::ostream &out, const type_t &type);

}    // namespace lin::ncf::command
