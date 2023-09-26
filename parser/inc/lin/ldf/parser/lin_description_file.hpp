#pragma once

#include <lin/common/parser/comment.hpp>
#include <lin/ldf/parser/frame.hpp>
#include <lin/ldf/parser/global.hpp>
#include <lin/ldf/parser/node.hpp>
#include <lin/ldf/parser/schedule_table.hpp>
#include <lin/ldf/parser/signal.hpp>

#include <lin/ldf/lin_description_file.hpp>

/* 9.2 LIN description file definition */

namespace lin::ldf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::comment::parser;
using namespace global::parser;
using namespace signal::parser;
using namespace frame::parser;
using namespace node::parser;

x3::rule< class lin_description_file, lin_description_file_t > const lin_description_file =
    "lin_description_file";

auto const lin_protocol_version_action = [](auto &ctx) {
    x3::_val(ctx).lin_protocol_version = x3::_attr(ctx);
};
auto const lin_language_version_action = [](auto &ctx) {
    x3::_val(ctx).lin_language_version = x3::_attr(ctx);
};
auto const lin_speed_action    = [](auto &ctx) { x3::_val(ctx).lin_speed = x3::_attr(ctx); };
auto const channel_name_action = [](auto &ctx) { x3::_val(ctx).channel_name = x3::_attr(ctx); };
auto const participating_nodes_action = [](auto &ctx) {
    x3::_val(ctx).participating_nodes = x3::_attr(ctx);
};
auto const node_composition_action = [](auto &ctx) {
    x3::_val(ctx).node_composition = x3::_attr(ctx);
};
auto const standard_signals_action = [](auto &ctx) {
    x3::_val(ctx).standard_signals = x3::_attr(ctx);
};
auto const diagnostic_signals_action = [](auto &ctx) {
    x3::_val(ctx).diagnostic_signals = x3::_attr(ctx);
};
auto const unconditional_frames_action = [](auto &ctx) {
    x3::_val(ctx).unconditional_frames = x3::_attr(ctx);
};
auto const sporadic_frames_action = [](auto &ctx) {
    x3::_val(ctx).sporadic_frames = x3::_attr(ctx);
};
auto const event_triggered_frames_action = [](auto &ctx) {
    x3::_val(ctx).event_triggered_frames = x3::_attr(ctx);
};
auto const diagnostic_frames_action = [](auto &ctx) {
    x3::_val(ctx).diagnostic_frames = x3::_attr(ctx);
};
auto const node_attributes_action = [](auto &ctx) {
    x3::_val(ctx).node_attributes = x3::_attr(ctx);
};
auto const schedule_tables_action = [](auto &ctx) {
    x3::_val(ctx).schedule_tables = x3::_attr(ctx);
};
auto const signal_groups_action = [](auto &ctx) { x3::_val(ctx).signal_groups = x3::_attr(ctx); };
auto const signal_encoding_types_action = [](auto &ctx) {
    x3::_val(ctx).signal_encoding_types = x3::_attr(ctx);
};
auto const signal_representations_action = [](auto &ctx) {
    x3::_val(ctx).signal_representations = x3::_attr(ctx);
};

auto const lin_description_file_def = x3::skip(comment)
    [x3::lit("LIN_description_file") > ';' >
     /* clang-format off */
     *(lin_language_version[lin_protocol_version_action] |
       lin_protocol_version[lin_language_version_action] |
       lin_speed[lin_speed_action] |
       channel_name[channel_name_action] |
       participating_nodes[participating_nodes_action] |
       node_composition[node_composition_action] |
       standard_signals[standard_signals_action] |
       diagnostic_signals[diagnostic_signals_action] |
       unconditional_frames[unconditional_frames_action] |
       sporadic_frames[sporadic_frames_action] |
       event_triggered_frames[event_triggered_frames_action] |
       diagnostic_frames[diagnostic_frames_action] |
       node_attributes[node_attributes_action] |
       schedule_tables[schedule_tables_action] |
       signal_groups[signal_groups_action] |
       signal_encoding_types[signal_encoding_types_action] |
       signal_representations[signal_representations_action])
     /* clang-format on */
];

BOOST_SPIRIT_DEFINE(lin_description_file)

}    // namespace lin::ldf::parser
