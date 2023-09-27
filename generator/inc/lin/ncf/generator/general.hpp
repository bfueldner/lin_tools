#pragma once

#include <iostream>

#include <lin/ncf/general.hpp>

namespace lin::ncf {

/* 8.2.3 General definition */

namespace general {

/* 8.2.3.3 Bit rate */

std::ostream &operator<<(std::ostream &out, bitrate_t const &bitrate);

namespace bitrate_definition {

std::ostream &operator<<(std::ostream &out, automatic_t const &automatic);
std::ostream &operator<<(std::ostream &out, select_t const &select);

}    // namespace bitrate_definition

std::ostream &operator<<(std::ostream &out, bitrate_definition_t const &bitrate_definition);

}    // namespace general

std::ostream &operator<<(std::ostream &out, general_t const &general);

}    // namespace lin::ncf
