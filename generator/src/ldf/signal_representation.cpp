#include <ostream>

#include <lin/common/generator/indention.hpp>
#include <lin/ldf/generator/signal_representation.hpp>
#include <lin/ldf/signal_representation.hpp>

/* 9.2.6.2 Signal representation definition */

namespace lin::ldf::signal {

std::ostream &operator<<(std::ostream &out, representation_t const &representation)
{
    out << common::indention_t::indent << representation.name << ": ";
    for (auto iter = representation.signals.cbegin(); iter != representation.signals.cend(); ++iter)
    {
        out << *iter;
        if (iter != representation.signals.cend() - 1)
        {
            out << ", ";
        }
    }
    out << ";\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, representations_t const &representations)
{
    out << common::indention_t::push << "Signal_representation {\n";
    for (auto const &representation : representations)
    {
        out << representation;
    }
    out << common::indention_t::pop << "}\n";
    return out;
}

}    // namespace lin::ldf::signal
