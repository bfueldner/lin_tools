#pragma once

#include <iostream>

#include <lin/ldf/node_composition.hpp>

/* 9.2.2.3 Node composition definition */

namespace lin::ldf::node {

namespace composition {

namespace configuration {

std::ostream &operator<<(std::ostream &out, composite_t const &composite);

}    // namespace configuration

std::ostream &operator<<(std::ostream &out, configuration_t const &configuration);

}    // namespace composition

std::ostream &operator<<(std::ostream &out, compositions_t const &composition);

}    // namespace lin::ldf::node
