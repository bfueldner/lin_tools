#pragma once

#include <iostream>

#include <lin/ncf/frame.hpp>

namespace lin::ncf {

/* 8.2.5.1 Frame properties */

std::ostream &operator<<(std::ostream &out, frame_properties_t const &frame_properties);

/* 8.2.5 Frame definition */

namespace frame {

std::ostream &operator<<(std::ostream &out, frame_kind_t const &frame_kind);
std::ostream &operator<<(std::ostream &out, single_frame_t const &single_frame);

}    // namespace frame

std::ostream &operator<<(std::ostream &out, frames_t const &frames);

}    // namespace lin::ncf
