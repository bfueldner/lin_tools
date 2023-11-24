#include <ostream>

#include <lin/common/generator/indention.hpp>
#include <lin/ldf/generator/signal_group.hpp>
#include <lin/ldf/signal_group.hpp>

/* 9.2.3.3 Signal groups */

namespace lin::ldf::signal {

namespace group {

std::ostream &operator<<(std::ostream &out, signal_t const &entry)
{
    out << common::indention_t::indent << entry.name << ", " << entry.offset << ";\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, signals_t const &entries)
{
    for (auto const &entry : entries)
    {
        out << entry;
    }
    return out;
}

}    // namespace group

std::ostream &operator<<(std::ostream &out, group_t const &group)
{
    out << common::indention_t::indent << group.name << ": " << group.size
        << common::indention_t::push << " {\n";
    out << group.signals;
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, groups_t const &groups)
{
    out << common::indention_t::push << "Signal_groups {\n";
    for (auto const &group : groups)
    {
        out << group;
    }
    out << common::indention_t::pop << "}\n";
    return out;
}

}    // namespace lin::ldf::signal
