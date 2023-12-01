#pragma once

#include <iostream>

#include <lin/ldf/signal_diagnostic.hpp>

/* 9.2.3.2 Diagnostic signals */

namespace lin::ldf::signal {

std::ostream &operator<<(std::ostream &out, diagnostic_t const &diagnostic);
std::ostream &operator<<(std::ostream &out, diagnostics_t const &diagnostics);

}    // namespace lin::ldf::signal
