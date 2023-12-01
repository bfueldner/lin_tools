#include <iomanip>
#include <ios>
#include <ostream>

#include <lin/common/generator/indention.hpp>
#include <lin/ldf/generator/node_attribute.hpp>
#include <lin/ldf/node_attribute.hpp>

/* 9.2.2.2 Node attributes */

namespace lin::ldf::node {

namespace attribute {

std::ostream &operator<<(std::ostream &out, product_id_t const &product_id)
{
    out << "product_id = " << std::hex << std::setfill('0') << "0x" << std::setw(4)
        << product_id.supplier << ", 0x" << std::setw(4) << product_id.function << std::dec;
    if (product_id.variant)
    {
        out << ", " << product_id.variant.value();
    }
    out << ";";
    return out;
}

std::ostream &operator<<(std::ostream &out, configurable_frame_t const &configurable_frame)
{
    out << common::indention_t::indent << configurable_frame.name;
    if (configurable_frame.id)
    {
        out << " = 0x" << std::hex << std::setfill('0') << std::setw(2)
            << configurable_frame.id.value() << std::dec;
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

}    // namespace attribute

// NOLINTBEGIN(readability-function-cognitive-complexity)
std::ostream &operator<<(std::ostream &out, attribute_t const &attribute)
{
    out << common::indention_t::indent << common::indention_t::push << attribute.name
        << std::setfill('0') << " {\n";
    out << common::indention_t::indent << "LIN_protocol = \"" << attribute.protocol_version
        << "\";\n";
    out << common::indention_t::indent << "configured_NAD = 0x" << std::hex << std::setw(2)
        << attribute.configured_nad << std::dec << ";\n";
    if (attribute.initial_nad)
    {
        out << common::indention_t::indent << "initial_NAD = 0x" << std::hex << std::setw(2)
            << attribute.initial_nad.value() << std::dec << ";\n";
    }

    if (!attribute.protocol_version.empty() && attribute.protocol_version[0] == '2')
    {
        if (attribute.product_id)
        {
            out << common::indention_t::indent << attribute.product_id.value() << '\n';
        }

        if (attribute.response_error)
        {
            out << common::indention_t::indent
                << "response_error = " << attribute.response_error.value() << ";\n";
        }

        if (!attribute.fault_state_signals.empty())
        {
            out << common::indention_t::indent << "fault_state_signals = ";
            for (auto iter = attribute.fault_state_signals.cbegin();
                 iter != attribute.fault_state_signals.cend();
                 ++iter)
            {
                out << *iter;
                if (iter != attribute.fault_state_signals.cend() - 1)
                {
                    out << ", ";
                }
            }
            out << ";\n";
        }

        if (attribute.p2_min)
        {
            out << common::indention_t::indent << "P2_min = " << attribute.p2_min.value()
                << " ms;\n";
        }

        if (attribute.st_min)
        {
            out << common::indention_t::indent << "ST_min = " << attribute.st_min.value()
                << " ms;\n";
        }

        if (attribute.n_as_timeout)
        {
            out << common::indention_t::indent
                << "N_As_timeout = " << attribute.n_as_timeout.value() << " ms;\n";
        }

        if (attribute.n_cr_timeout)
        {
            out << common::indention_t::indent
                << "N_Cr_timeout = " << attribute.n_cr_timeout.value() << " ms;\n";
        }

        if (!attribute.configurable_frames.empty())
        {
            out << attribute.configurable_frames;
        }
    }
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}
// NOLINTEND(readability-function-cognitive-complexity)

std::ostream &operator<<(std::ostream &out, attributes_t const &attributes)
{
    out << common::indention_t::push << "Node_attributes {\n";
    for (auto const &node_attribute : attributes)
    {
        out << node_attribute;
    }
    out << common::indention_t::pop << "}\n";
    return out;
}

}    // namespace lin::ldf::node
