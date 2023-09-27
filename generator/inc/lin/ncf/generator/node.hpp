#pragma once

#include <iostream>

#include <lin/ncf/node.hpp>

namespace lin::ncf {

/* 8.2.2 Node definition */

std::ostream &operator<<(std::ostream &out, node_t const &node);

}    // namespace lin::ncf
