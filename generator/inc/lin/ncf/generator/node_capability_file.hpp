#pragma once

#include <iostream>

#include <lin/ncf/node_capability_file.hpp>

/* 8.2.2 Node definition */

namespace lin::ncf {

std::ostream &operator<<(std::ostream &out, node_capability_file_t const &node_capability_file);

}    // namespace lin::ncf
