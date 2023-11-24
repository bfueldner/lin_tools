#pragma once

#include <iostream>

#include <lin/ncf/frame.hpp>

/* 8.2.5 Frame definition */

namespace lin::ncf {

namespace frame {

std::ostream &operator<<(std::ostream &out, kind_t const &frame_kind);

}    // namespace frame

/* 8.2.5.1 Frame properties */

std::ostream &operator<<(std::ostream &out, frame_t const &frame);
std::ostream &operator<<(std::ostream &out, frames_t const &frames);

}    // namespace lin::ncf
