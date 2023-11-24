#pragma once

#include <iostream>

#include <lin/ldf/frame_diagnostic.hpp>

/* 9.2.4.4 Diagnostic frames */

namespace lin::ldf::frame {

std::ostream &operator<<(std::ostream &out, diagnostic_t const &diagnostic);
std::ostream &operator<<(std::ostream &out, diagnostics_t const &diagnostics);

}    // namespace lin::ldf::frame
