#pragma once

#include <iostream>

#include <lin/common/bitrate.hpp>

namespace lin::common::bitrate {

std::ostream &operator<<(std::ostream &out, kbps_t const &kbps);

}    // namespace lin::common::bitrate
