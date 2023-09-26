#pragma once

#include <lin/ldf/frame.hpp>
#include <lin/ldf/global.hpp>
#include <lin/ldf/node.hpp>
#include <lin/ldf/schedule_table.hpp>
#include <lin/ldf/signal.hpp>

/* 9.2 LIN description file definition */

namespace lin::ldf {

struct lin_description_file_t
{
    global::lin_protocol_version_t lin_protocol_version{};
    global::lin_language_version_t lin_language_version{};
    global::lin_speed_t lin_speed{};
    global::channel_name_t channel_name{};
    node::participating_nodes_t participating_nodes{};
    node::node_composition_t node_composition{};
    signal::standard_signals_t standard_signals{};
    signal::diagnostic_signals_t diagnostic_signals{};
    frame::unconditional_frames_t unconditional_frames{};
    frame::sporadic_frames_t sporadic_frames{};
    frame::event_triggered_frames_t event_triggered_frames{};
    frame::diagnostic_frames_t diagnostic_frames{};
    node::node_attributes_t node_attributes{};
    schedule_tables_t schedule_tables{};
    signal::signal_groups_t signal_groups{};
    signal::signal_encoding_types_t signal_encoding_types{};
    signal::signal_representations_t signal_representations{};
};

}    // namespace lin::ldf
