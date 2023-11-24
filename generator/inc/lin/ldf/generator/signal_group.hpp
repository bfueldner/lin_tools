#pragma once

#include <iostream>

#include <lin/ldf/signal_group.hpp>

/* 9.2.3.3 Signal groups */

namespace lin::ldf::signal {

namespace group {

std::ostream &operator<<(std::ostream &out, signal_t const &entry);
std::ostream &operator<<(std::ostream &out, signals_t const &entries);

}    // namespace group

std::ostream &operator<<(std::ostream &out, group_t const &group);
std::ostream &operator<<(std::ostream &out, groups_t const &groups);

}    // namespace lin::ldf::signal
