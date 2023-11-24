#include <ostream>

#include <lin/common/generator/indention.hpp>
#include <lin/common/generator/signal_init_value.hpp>
#include <lin/ldf/generator/signal_standard.hpp>
#include <lin/ldf/signal_standard.hpp>

/* 9.2.3.1 Standard signals */

namespace lin::ldf::signal {

std::ostream &operator<<(std::ostream &out, standard_t const &standard)
{
    using common::signal::operator<<;

    out << common::indention_t::indent << standard.name << ": " << (long int)standard.size << ", "
        << standard.init_value << ", " << standard.published_by;
    for (auto const &subscriber : standard.subscribed_by)
    {
        out << ", " << subscriber;
    }
    out << ";\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, standards_t const &standards)
{
    out << common::indention_t::push << "Signals {\n";
    for (auto const &standard : standards)
    {
        out << standard;
    }
    out << common::indention_t::pop << "}\n";
    return out;
}

}    // namespace lin::ldf::signal
