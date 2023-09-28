#include <ostream>

#include <lin/ldf/lin_description_file.hpp>

#include <lin/ldf/generator/frame.hpp>
#include <lin/ldf/generator/lin_description_file.hpp>
#include <lin/ldf/generator/node.hpp>
#include <lin/ldf/generator/schedule_table.hpp>
#include <lin/ldf/generator/signal.hpp>

/* 9.2 LIN description file definition */

namespace lin::ldf {

std::ostream &operator<<(std::ostream &out, lin_description_file_t const &lin_description_file)
{
    using namespace node;

    out << "LIN_description_file;\n";
    out << "LIN_protocol_version = \"" << lin_description_file.lin_protocol_version << "\";\n";
    out << "LIN_language_version = \"" << lin_description_file.lin_language_version << "\";\n";
    out << "LIN_speed = " << lin_description_file.lin_speed << " kbps;\n";
    if (!lin_description_file.channel_name.empty())
    {
        out << "Channel_name = \"" << lin_description_file.channel_name << "\";\n";
    }
    out << lin_description_file.participating_nodes;
    if (!lin_description_file.node_composition.empty())
    {
        out << lin_description_file.node_composition;
    }
    out << lin_description_file.standard_signals;
    if (!lin_description_file.diagnostic_signals.empty())
    {
        out << lin_description_file.diagnostic_signals;
    }
    out << lin_description_file.unconditional_frames;
    if (!lin_description_file.sporadic_frames.empty())
    {
        out << lin_description_file.sporadic_frames;
    }
    if (!lin_description_file.event_triggered_frames.empty())
    {
        out << lin_description_file.event_triggered_frames;
    }
    if (!lin_description_file.diagnostic_frames.empty())
    {
        out << lin_description_file.diagnostic_frames;
    }
    out << lin_description_file.node_attributes;
    out << lin_description_file.schedule_tables;
    if (!lin_description_file.signal_groups.empty())
    {
        out << lin_description_file.signal_groups;
    }
    if (!lin_description_file.signal_encoding_types.empty())
    {
        out << lin_description_file.signal_encoding_types;
    }
    if (!lin_description_file.signal_representations.empty())
    {
        out << lin_description_file.signal_representations;
    }
    return out;
}

}    // namespace lin::ldf
