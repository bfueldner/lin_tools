#pragma once

#include <iostream>

#include <lin/ldf/nodes.hpp>

/* 9.2.2.1 Participating nodes */

namespace lin::ldf {

namespace nodes {

std::ostream &operator<<(std::ostream &out, master_t const &master);
std::ostream &operator<<(std::ostream &out, slaves_t const &slaves);

}    // namespace nodes

std::ostream &operator<<(std::ostream &out, nodes_t const &nodes);

}    // namespace lin::ldf
