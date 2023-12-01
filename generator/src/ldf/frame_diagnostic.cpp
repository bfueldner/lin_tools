#include <iomanip>
#include <ios>
#include <ostream>

#include <lin/common/generator/indention.hpp>
#include <lin/ldf/frame_diagnostic.hpp>
#include <lin/ldf/generator/frame_diagnostic.hpp>

/* 9.2.4.4 Diagnostic frames */

namespace lin::ldf::frame {

std::ostream &operator<<(std::ostream &out, diagnostic_t const &diagnostic)
{
    out << common::indention_t::indent << common::indention_t::push << diagnostic.name << ": "
        << std::hex << "0x" << std::setw(2) << std::setfill('0') << diagnostic.id << std::dec
        << " {\n";
    for (auto const &signal : diagnostic.signals)
    {
        out << common::indention_t::indent << signal.name << ", " << signal.offset << ";\n";
    }
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, diagnostics_t const &diagnostics)
{
    out << common::indention_t::push << "Diagnostic_frames {\n";
    for (auto const &diagnostic : diagnostics)
    {
        out << diagnostic;
    }
    out << common::indention_t::pop << "}\n";
    return out;
}

}    // namespace lin::ldf::frame
