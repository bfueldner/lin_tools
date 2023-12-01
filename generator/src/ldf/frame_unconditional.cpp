#include <iomanip>
#include <ios>
#include <ostream>

#include <lin/common/generator/indention.hpp>
#include <lin/ldf/frame_unconditional.hpp>
#include <lin/ldf/generator/frame_unconditional.hpp>

/* 9.2.4.1 Unconditional frames */

namespace lin::ldf::frame {

namespace unconditional {

std::ostream &operator<<(std::ostream &out, signal_t const &signal)
{
    out << common::indention_t::indent << signal.name << ", " << signal.offset << ";\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, signals_t const &signals)
{
    for (auto const &signal : signals)
    {
        out << signal;
    }
    return out;
}

}    // namespace unconditional

std::ostream &operator<<(std::ostream &out, unconditional_t const &unconditional)
{
    out << common::indention_t::indent << common::indention_t::push << unconditional.name << ": "
        << std::hex << "0x" << std::setw(2) << std::setfill('0') << unconditional.id << std::dec
        << ", " << unconditional.published_by << ", " << unconditional.size << " {\n";
    for (auto const &signal : unconditional.signals)
    {
        out << signal;
    }
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, unconditionals_t const &unconditionals)
{
    out << common::indention_t::push << "Frames {\n";
    for (auto const &unconditional : unconditionals)
    {
        out << unconditional;
    }
    out << common::indention_t::pop << "}\n";
    return out;
}

}    // namespace lin::ldf::frame
