#pragma once

#include <iostream>

#include <lin/ncf/node_capability_file.hpp>

namespace lin::ncf {

/* 8.2.2 Node definition */

std::ostream &operator<<(std::ostream &out, node_capability_file_t const &node_capability_file);

}    // namespace lin::ncf
