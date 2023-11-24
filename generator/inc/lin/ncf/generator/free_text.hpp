#pragma once

#include <iostream>

#include <lin/ncf/free_text.hpp>

/* 8.2.7 Free text definition */

namespace lin::ncf {

std::ostream &operator<<(std::ostream &out, free_text_t const &free_text);

}    // namespace lin::ncf
