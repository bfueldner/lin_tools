#pragma once

#include <lin/common/bitrate.hpp>
#include <lin/ldf/frame_diagnostic.hpp>
#include <lin/ldf/frame_event_triggered.hpp>
#include <lin/ldf/frame_sporadic.hpp>
#include <lin/ldf/frame_unconditional.hpp>
#include <lin/ldf/node_attribute.hpp>
#include <lin/ldf/node_composition.hpp>
#include <lin/ldf/nodes.hpp>
#include <lin/ldf/schedule_table.hpp>
#include <lin/ldf/signal_diagnostic.hpp>
#include <lin/ldf/signal_encoding.hpp>
#include <lin/ldf/signal_group.hpp>
#include <lin/ldf/signal_representation.hpp>
#include <lin/ldf/signal_standard.hpp>

/* 9.2 LIN description file definition */

namespace lin::ldf {

/* 9.2.1 Global definition */

/* 9.2.1.1 LIN protocol version number definition */

using protocol_version_t = common::bnf::char_string_t;

/* 9.2.1.2 LIN language version number definition */

using language_version_t = common::bnf::char_string_t;

/* 9.2.1.3 LIN speed definition */

/* NOTE: Specification says 'speed', but in NCF it is called 'bitrate'. */
using bitrate_t = common::bitrate::kbps_t;

/* 9.2.1.4 Channel postfix name definition */

/* NOTE: Specification says 'identifier', but example shows 'char_string'. */
using channel_name_t = common::bnf::char_string_t;

struct lin_description_file_t
{
    protocol_version_t protocol_version{};
    language_version_t language_version{};
    bitrate_t bitrate{};
    channel_name_t channel_name{};
    nodes_t nodes{};
    node::compositions_t node_compositions{};
    signal::standards_t standard_signals{};
    signal::diagnostics_t diagnostic_signals{};
    frame::unconditionals_t unconditional_frames{};
    frame::sporadics_t sporadic_frames{};
    frame::event_triggereds_t event_triggered_frames{};
    frame::diagnostics_t diagnostic_frames{};
    node::attributes_t node_attributes{};
    schedule_tables_t schedule_tables{};
    signal::groups_t signal_groups{};
    signal::encodings_t signal_encodings{};
    signal::representations_t signal_representations{};
};

}    // namespace lin::ldf
