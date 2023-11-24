#include <ostream>

#include <lin/common/generator/indention.hpp>
#include <lin/ldf/generator/node_composition.hpp>
#include <lin/ldf/node_composition.hpp>

/* 9.2.2.3 Node composition definition */

namespace lin::ldf::node {

namespace composition {

namespace configuration {

std::ostream &operator<<(std::ostream &out, composite_t const &composite)
{
    out << common::indention_t::indent << common::indention_t::push << composite.name << " {\n";
    out << common::indention_t::indent;
    for (auto iter = composite.nodes.cbegin(); iter != composite.nodes.cend(); ++iter)
    {
        out << *iter;
        if (iter != composite.nodes.cend() - 1)
        {
            out << ", ";
        }
    }
    out << ";\n";
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

}    // namespace configuration

std::ostream &operator<<(std::ostream &out, configuration_t const &configuration)
{
    out << common::indention_t::indent << common::indention_t::push << "configuration "
        << configuration.name << " {\n";
    for (auto const &composite_node : configuration.composites)
    {
        out << composite_node;
    }
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

}    // namespace composition

std::ostream &operator<<(std::ostream &out, compositions_t const &composition)
{
    out << common::indention_t::push << "composite {\n";
    for (auto const &node : composition)
    {
        out << node;
    }
    out << common::indention_t::pop << "}\n";
    return out;
}

}    // namespace lin::ldf::node
