#pragma once

#include <iostream>

#include <lin/ncf/status.hpp>

namespace lin::ncf {

/* 8.2.6 Status management */

std::ostream &operator<<(std::ostream &out, status_t const &status);

}    // namespace lin::ncf
