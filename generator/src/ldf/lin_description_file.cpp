#include <ostream>

#include <lin/ldf/lin_description_file.hpp>

#include <lin/ldf/generator/frame_diagnostic.hpp>
#include <lin/ldf/generator/frame_event_triggered.hpp>
#include <lin/ldf/generator/frame_sporadic.hpp>
#include <lin/ldf/generator/frame_unconditional.hpp>
#include <lin/ldf/generator/lin_description_file.hpp>
#include <lin/ldf/generator/node_attribute.hpp>
#include <lin/ldf/generator/node_composition.hpp>
#include <lin/ldf/generator/nodes.hpp>
#include <lin/ldf/generator/schedule_table.hpp>
#include <lin/ldf/generator/signal_diagnostic.hpp>
#include <lin/ldf/generator/signal_encoding.hpp>
#include <lin/ldf/generator/signal_group.hpp>
#include <lin/ldf/generator/signal_representation.hpp>
#include <lin/ldf/generator/signal_standard.hpp>

/* 9.2 LIN description file definition */

namespace lin::ldf {

std::ostream &operator<<(std::ostream &out, lin_description_file_t const &lin_description_file)
{
    using namespace signal;
    using namespace node;

    out << "LIN_description_file;\n";
    out << "LIN_protocol_version = \"" << lin_description_file.protocol_version << "\";\n";
    out << "LIN_language_version = \"" << lin_description_file.language_version << "\";\n";
    out << "LIN_speed = " << lin_description_file.bitrate << " kbps;\n";
    if (!lin_description_file.channel_name.empty())
    {
        out << "Channel_name = \"" << lin_description_file.channel_name << "\";\n";
    }

    out << lin_description_file.nodes;
    if (!lin_description_file.node_compositions.empty())
    {
        out << lin_description_file.node_compositions;
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

    if (!lin_description_file.signal_encodings.empty())
    {
        out << lin_description_file.signal_encodings;
    }

    if (!lin_description_file.signal_representations.empty())
    {
        out << lin_description_file.signal_representations;
    }
    return out;
}

}    // namespace lin::ldf
