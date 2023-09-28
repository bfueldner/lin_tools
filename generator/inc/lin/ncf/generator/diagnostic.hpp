#pragma once

#include <iostream>

#include <lin/ncf/diagnostic.hpp>

/* 8.2.4 Diagnostic definition */

namespace lin::ncf {

namespace diagnostic {

namespace nad {

std::ostream &operator<<(std::ostream &out, sequence_t const &sequence);
std::ostream &operator<<(std::ostream &out, range_t const &range);

}    // namespace nad

std::ostream &operator<<(std::ostream &out, nad_t const &nad);

}    // namespace diagnostic

std::ostream &operator<<(std::ostream &out, diagnostic_t const &diagnostic);

}    // namespace lin::ncf
