#include <iomanip>
#include <ios>
#include <ostream>

#include <lin/ldf/node.hpp>

#include <lin/common/generator/indention.hpp>
#include <lin/ldf/generator/node.hpp>

/* 9.2.2 Node definition */

namespace lin::ldf::node {

/* 9.2.2.1 Participating nodes */

namespace participating_nodes {

std::ostream &operator<<(std::ostream &out, master_t const &master)
{
    out << common::indention_t::indent << "Master: " << master.node_name << ", " << master.time_base
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

}    // namespace participating_nodes

std::ostream &operator<<(std::ostream &out, participating_nodes_t const &participating_nodes)
{
    using namespace participating_nodes;

    out << common::indention_t::push << "Nodes {\n";
    out << participating_nodes.master;
    out << participating_nodes.slaves;
    out << common::indention_t::pop << "}\n";
    return out;
}

/* 9.2.2.2 Node attributes */

namespace node_attribute {

std::ostream &operator<<(std::ostream &out, product_id_t const &product_id)
{
    out << "product_id = " << std::hex << std::setfill('0') << "0x" << std::setw(4)
        << product_id.supplier_id << ", 0x" << std::setw(4) << product_id.function_id << std::dec;
    if (product_id.variant)
    {
        out << ", " << product_id.variant.value();
    }
    out << ";";
    return out;
}

std::ostream &operator<<(std::ostream &out, configurable_frame_t const &configurable_frame)
{
    out << common::indention_t::indent << configurable_frame.frame_name;
    if (configurable_frame.message_id)
    {
        out << " = 0x" << std::hex << std::setfill('0') << std::setw(2)
            << configurable_frame.message_id.value() << std::dec;
    }
    out << ";\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, configurable_frames_t const &configurable_frames)
{
    out << common::indention_t::indent << common::indention_t::push << "configurable_frames {\n";
    for (auto const &configurable_frame : configurable_frames)
    {
        out << configurable_frame;
    }
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

}    // namespace node_attribute

// NOLINTBEGIN(readability-function-cognitive-complexity)
std::ostream &operator<<(std::ostream &out, node_attribute_t const &node_attribute)
{
    out << common::indention_t::indent << common::indention_t::push << node_attribute.node_name
        << std::setfill('0') << " {\n";
    out << common::indention_t::indent << "LIN_protocol = \"" << node_attribute.lin_protocol
        << "\";\n";
    out << common::indention_t::indent << "configured_NAD = 0x" << std::hex << std::setw(2)
        << node_attribute.configured_nad << std::dec << ";\n";
    if (node_attribute.initial_nad)
    {
        out << common::indention_t::indent << "initial_NAD = 0x" << std::hex << std::setw(2)
            << node_attribute.initial_nad.value() << std::dec << ";\n";
    }

    if (!node_attribute.lin_protocol.empty() && node_attribute.lin_protocol[0] == '2')
    {
        if (node_attribute.product_id)
        {
            out << common::indention_t::indent << node_attribute.product_id.value() << '\n';
        }

        if (node_attribute.response_error)
        {
            out << common::indention_t::indent
                << "response_error = " << node_attribute.response_error.value() << ";\n";
        }

        if (!node_attribute.fault_state_signals.empty())
        {
            out << common::indention_t::indent << "fault_state_signals = ";
            for (auto iter = node_attribute.fault_state_signals.cbegin();
                 iter != node_attribute.fault_state_signals.cend();
                 ++iter)
            {
                out << *iter;
                if (iter != node_attribute.fault_state_signals.cend() - 1)
                {
                    out << ", ";
                }
            }
            out << ";\n";
        }

        if (node_attribute.p2_min)
        {
            out << common::indention_t::indent << "P2_min = " << node_attribute.p2_min.value()
                << " ms;\n";
        }

        if (node_attribute.st_min)
        {
            out << common::indention_t::indent << "ST_min = " << node_attribute.st_min.value()
                << " ms;\n";
        }

        if (node_attribute.n_as_timeout)
        {
            out << common::indention_t::indent
                << "N_As_timeout = " << node_attribute.n_as_timeout.value() << " ms;\n";
        }

        if (node_attribute.n_cr_timeout)
        {
            out << common::indention_t::indent
                << "N_Cr_timeout = " << node_attribute.n_cr_timeout.value() << " ms;\n";
        }

        if (!node_attribute.configurable_frames.empty())
        {
            out << node_attribute.configurable_frames;
        }
    }
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}
// NOLINTEND(readability-function-cognitive-complexity)

std::ostream &operator<<(std::ostream &out, node_attributes_t const &node_attributes)
{
    out << common::indention_t::push << "Node_attributes {\n";
    for (auto const &node_attribute : node_attributes)
    {
        out << node_attribute;
    }
    out << common::indention_t::pop << "}\n";
    return out;
}

/* 9.2.2.3 Node composition definition */

namespace node_composition {

std::ostream &operator<<(std::ostream &out, composition_t const &composition)
{
    out << common::indention_t::indent << common::indention_t::push << composition.composite_node
        << " {\n";
    out << common::indention_t::indent;
    for (auto iter = composition.logical_node.cbegin(); iter != composition.logical_node.cend();
         ++iter)
    {
        out << *iter;
        if (iter != composition.logical_node.cend() - 1)
        {
            out << ", ";
        }
    }
    out << ";\n";
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, configuration_t const &configuration)
{
    out << common::indention_t::indent << common::indention_t::push << "configuration "
        << configuration.configuration_name << " {\n";
    for (auto const &composite_node : configuration.composite_node)
    {
        out << composite_node;
    }
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

}    // namespace node_composition

std::ostream &operator<<(std::ostream &out, node_composition_t const &node_composition)
{
    out << common::indention_t::push << "composite {\n";
    for (auto const &node : node_composition)
    {
        out << node;
    }
    out << common::indention_t::pop << "}\n";
    return out;
}

}    // namespace lin::ldf::node
