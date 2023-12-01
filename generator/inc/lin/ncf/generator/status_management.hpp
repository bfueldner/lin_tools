#pragma once

#include <iostream>

#include <lin/ncf/status_management.hpp>

/* 8.2.6 Status management */

namespace lin::ncf {

std::ostream &operator<<(std::ostream &out, status_management_t const &status_management);

}    // namespace lin::ncf
