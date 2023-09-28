#pragma once

#include <iostream>

#include <lin/ldf/lin_description_file.hpp>

/* 9.2 LIN description file definition */

namespace lin::ldf {

std::ostream &operator<<(std::ostream &out, lin_description_file_t const &lin_description_file);

}    // namespace lin::ldf
