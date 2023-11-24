#pragma once

#include <iostream>

#include <lin/ncf/node.hpp>

/* 8.2.2 Node definition */

namespace lin::ncf {

std::ostream &operator<<(std::ostream &out, node_t const &node);

}    // namespace lin::ncf
