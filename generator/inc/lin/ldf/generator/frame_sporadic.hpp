#pragma once

#include <iostream>

#include <lin/ldf/frame_sporadic.hpp>

/* 9.2.4.2 Sporadic frames */

namespace lin::ldf::frame {

std::ostream &operator<<(std::ostream &out, sporadic_t const &sporadic);
std::ostream &operator<<(std::ostream &out, sporadics_t const &sporadics);

}    // namespace lin::ldf::frame
