#include <ostream>

#include <lin/common/generator/indention.hpp>
#include <lin/common/generator/signal_init_value.hpp>
#include <lin/ncf/generator/signal.hpp>
#include <lin/ncf/signal.hpp>

/* 8.2.5.2 Signal definition */

namespace lin::ncf {

std::ostream &operator<<(std::ostream &out, signal_t const &signal)
{
    using common::signal::operator<<;

    out << common::indention_t::indent << common::indention_t::push << signal.name << " {\n";
    out << common::indention_t::indent << "init_value = " << signal.init_value << ";\n";
    out << common::indention_t::indent << "size = " << signal.size << ";\n";
    out << common::indention_t::indent << "offset = " << signal.offset << ";\n";
    if (!signal.encoding.empty())
    {
        out << common::indention_t::indent << signal.encoding << ";\n";
    }

    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, signals_t const &signals)
{
    out << common::indention_t::indent << common::indention_t::push << "signals {\n";
    for (auto const &signal : signals)
    {
        out << signal;
    }
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

}    // namespace lin::ncf
