#include <ostream>

#include <lin/common/generator/indention.hpp>
#include <lin/ldf/generator/nodes.hpp>
#include <lin/ldf/nodes.hpp>

/* 9.2.2 Node definition */

namespace lin::ldf {

/* 9.2.2.1 Participating nodes */

namespace nodes {

std::ostream &operator<<(std::ostream &out, master_t const &master)
{
    out << common::indention_t::indent << "Master: " << master.name << ", " << master.time_base
        << " ms, " << master.jitter << " ms;\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, slaves_t const &slaves)
{
    out << common::indention_t::indent << "Slaves: ";
    for (auto iter = slaves.cbegin(); iter != slaves.cend(); ++iter)
    {
        out << *iter;
        if (iter != slaves.cend() - 1)
        {
            out << ", ";
        }
    }
    out << ";\n";
    return out;
}

}    // namespace nodes

std::ostream &operator<<(std::ostream &out, nodes_t const &nodes)
{
    using namespace nodes;

    out << common::indention_t::push << "Nodes {\n";
    out << nodes.master;
    out << nodes.slaves;
    out << common::indention_t::pop << "}\n";
    return out;
}

}    // namespace lin::ldf
