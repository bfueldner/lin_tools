#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>

#include <lin/ldf/node.hpp>

/* 9.2.2 Node definition */

namespace lin::ldf::node {

/* 9.2.2.1 Participating nodes */

namespace participating_nodes::parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

x3::rule< class master, master_t > const master = "master";
x3::rule< class slaves, slaves_t > const slaves = "slaves";

auto const node_name = identifier;
auto const time_base = real_or_integer;
auto const jitter    = real_or_integer;

auto const master_def = x3::lit("Master") > ':' > node_name > ',' > time_base > "ms" > ',' >
                        jitter > "ms" > ';';
auto const slaves_def = x3::lit("Slaves") > ':' > node_name % ',' > ';';

BOOST_SPIRIT_DEFINE(master, slaves)

}    // namespace participating_nodes::parser

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace participating_nodes::parser;

x3::rule< class participating_nodes, participating_nodes_t > const participating_nodes =
    "participating_nodes";

auto const master_action = [](auto &ctx) { x3::_val(ctx).master = x3::_attr(ctx); };
auto const slaves_action = [](auto &ctx) { x3::_val(ctx).slaves = x3::_attr(ctx); };

auto const participating_nodes_def = x3::lit("Nodes") > '{' >
                                     *(master[master_action] | slaves[slaves_action]) > '}';

BOOST_SPIRIT_DEFINE(participating_nodes)

}    // namespace parser

/* 9.2.2.2 Node attributes */

namespace node_attribute::parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

x3::rule< class lin_protocol, lin_protocol_t > const lin_protocol       = "lin_protocol";
x3::rule< class configured_nad, configured_nad_t > const configured_nad = "configured_nad";
x3::rule< class initial_nad, initial_nad_t > const initial_nad          = "initial_nad";

x3::rule< class product_id, product_id_t > const product_id             = "product_id";
x3::rule< class response_error, response_error_t > const response_error = "response_error";
x3::rule< class fault_state_signals, fault_state_signals_t > const fault_state_signals =
    "fault_state_signals";
x3::rule< class p2_min, p2_min_t > const p2_min                   = "p2_min";
x3::rule< class st_min, st_min_t > const st_min                   = "st_min";
x3::rule< class n_as_timeout, n_as_timeout_t > const n_as_timeout = "n_as_timeout";
x3::rule< class n_cr_timeout, n_cr_timeout_t > const n_cr_timeout = "n_cr_timeout";
x3::rule< class configurable_frame, configurable_frame_t > const configurable_frame =
    "configurable_frame";
x3::rule< class configurable_frames, configurable_frames_t > const configurable_frames =
    "configurable_frames";

auto const protocol_version = char_string;
auto const diag_address     = integer;

auto const lin_protocol_def   = x3::lit("LIN_protocol") > '=' > protocol_version > ';';
auto const configured_nad_def = x3::lit("configured_NAD") > '=' > diag_address > ';';
auto const initial_nad_def    = x3::lit("initial_NAD") > '=' > diag_address > ';';

auto const supplier_id = integer;
auto const function_id = integer;
auto const variant     = integer;
auto const signal_name = identifier;
auto const frame_name  = identifier;
auto const message_id  = integer;

auto const product_id_def = x3::lit("product_id") > '=' > supplier_id > ',' > function_id >
                            -(',' > variant) > ';';
auto const response_error_def      = x3::lit("response_error") > '=' > signal_name > ';';
auto const fault_state_signals_def = x3::lit("fault_state_signals") > '=' > signal_name % ',' > ';';
auto const p2_min_def              = x3::lit("P2_min") > '=' > real_or_integer > "ms" > ';';
auto const st_min_def              = x3::lit("ST_min") > '=' > real_or_integer > "ms" > ';';
auto const n_as_timeout_def        = x3::lit("N_As_timeout") > '=' > real_or_integer > "ms" > ';';
auto const n_cr_timeout_def        = x3::lit("N_Cr_timeout") > '=' > real_or_integer > "ms" > ';';
auto const configurable_frame_def  = frame_name > -('=' > message_id) > ';';
auto const configurable_frames_def = x3::lit("configurable_frames") > '{' > *configurable_frame >
                                     '}';

BOOST_SPIRIT_DEFINE(
    lin_protocol,
    configured_nad,
    initial_nad,
    product_id,
    response_error,
    fault_state_signals,
    p2_min,
    st_min,
    n_as_timeout,
    n_cr_timeout,
    configurable_frame,
    configurable_frames)

}    // namespace node_attribute::parser

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace node_attribute::parser;

x3::rule< class node_attribute, node_attribute_t > const node_attribute    = "node_attribute";
x3::rule< class node_attributes, node_attributes_t > const node_attributes = "node_attributes";

auto const node_name_action      = [](auto &ctx) { x3::_val(ctx).node_name = x3::_attr(ctx); };
auto const lin_protocol_action   = [](auto &ctx) { x3::_val(ctx).lin_protocol = x3::_attr(ctx); };
auto const configured_nad_action = [](auto &ctx) { x3::_val(ctx).configured_nad = x3::_attr(ctx); };
auto const initial_nad_action    = [](auto &ctx) { x3::_val(ctx).initial_nad = x3::_attr(ctx); };
auto const product_id_action     = [](auto &ctx) { x3::_val(ctx).product_id = x3::_attr(ctx); };
auto const response_error_action = [](auto &ctx) { x3::_val(ctx).response_error = x3::_attr(ctx); };
auto const fault_state_signals_action = [](auto &ctx) {
    x3::_val(ctx).fault_state_signals = x3::_attr(ctx);
};
auto const p2_min_action       = [](auto &ctx) { x3::_val(ctx).p2_min = x3::_attr(ctx); };
auto const st_min_action       = [](auto &ctx) { x3::_val(ctx).st_min = x3::_attr(ctx); };
auto const n_as_timeout_action = [](auto &ctx) { x3::_val(ctx).n_as_timeout = x3::_attr(ctx); };
auto const n_cr_timeout_action = [](auto &ctx) { x3::_val(ctx).n_cr_timeout = x3::_attr(ctx); };
auto const configurable_frames_action = [](auto &ctx) {
    x3::_val(ctx).configurable_frames = x3::_attr(ctx);
};

auto const node_attribute_def =
    node_name[node_name_action] > '{' >
    *(lin_protocol[lin_protocol_action] | configured_nad[configured_nad_action] |
      initial_nad[initial_nad_action] | product_id[product_id_action] |
      response_error[response_error_action] | fault_state_signals[fault_state_signals_action] |
      p2_min[p2_min_action] | st_min[st_min_action] | n_as_timeout[n_as_timeout_action] |
      n_cr_timeout[n_cr_timeout_action] | configurable_frames[configurable_frames_action]) > '}';
auto const node_attributes_def = x3::lit("Node_attributes") > '{' > *node_attribute > '}';

BOOST_SPIRIT_DEFINE(node_attribute, node_attributes)

}    // namespace parser

/* 9.2.2.3 Node composition definition */

namespace node_composition::parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

x3::rule< class composition, composition_t > const composition       = "composition";
x3::rule< class configuration, configuration_t > const configuration = "configuration";

auto const configuration_name = identifier;
auto const composite_node     = identifier;
auto const logical_node       = identifier;

auto const composition_def   = composite_node > '{' > logical_node % ',' > ';' > '}';
auto const configuration_def = x3::lit("configuration") > configuration_name > '{' > *composition >
                               '}';

BOOST_SPIRIT_DEFINE(composition, configuration)

}    // namespace node_composition::parser

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace node_composition::parser;

x3::rule< class node_composition, node_composition_t > const node_composition = "node_composition";

auto const node_composition_def = x3::lit("composite") > '{' > *configuration > '}';

BOOST_SPIRIT_DEFINE(node_composition)

}    // namespace parser

}    // namespace lin::ldf::node

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::node::participating_nodes::master_t,
    node_name,
    time_base,
    jitter)

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::node::node_attribute::product_id_t,
    supplier_id,
    function_id,
    variant)

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::node::node_attribute::configurable_frame_t,
    frame_name,
    message_id)

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::node::node_composition::composition_t,
    composite_node,
    logical_node)

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::node::node_composition::configuration_t,
    configuration_name,
    composite_node)
