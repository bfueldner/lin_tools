#pragma once

#include <iostream>

#include <lin/ncf/general.hpp>

/* 8.2.3 General definition */

namespace lin::ncf {

namespace general {

/* 8.2.3.3 Bit rate */

namespace bitrate {

std::ostream &operator<<(std::ostream &out, automatic_t const &automatic);
std::ostream &operator<<(std::ostream &out, select_t const &select);
//std::ostream &operator<<(std::ostream &out, fixed_t const &fixed);

}    // namespace bitrate

std::ostream &operator<<(std::ostream &out, bitrate_t const &bitrate);

}    // namespace general

std::ostream &operator<<(std::ostream &out, general_t const &general);

}    // namespace lin::ncf
