#include <ostream>

#include <lin/common/generator/indention.hpp>
#include <lin/common/generator/signal_init_value.hpp>
#include <lin/ldf/generator/signal_diagnostic.hpp>
#include <lin/ldf/signal_diagnostic.hpp>

/* 9.2.3.2 Diagnostic signals */

namespace lin::ldf::signal {

std::ostream &operator<<(std::ostream &out, diagnostic_t const &diagnostic)
{
    using common::signal::operator<<;

    out << common::indention_t::indent << diagnostic.name << ": " << diagnostic.size << ", "
        << diagnostic.init_value << ";\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, diagnostics_t const &diagnostics)
{
    out << common::indention_t::push << "Diagnostic_signals {\n";
    for (auto const &diagnostic : diagnostics)
    {
        out << diagnostic;
    }
    out << common::indention_t::pop << "}\n";
    return out;
}

}    // namespace lin::ldf::signal
