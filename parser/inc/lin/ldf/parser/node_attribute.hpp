#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/ldf/node_attribute.hpp>

/* 9.2.2.2 Node attributes */

namespace lin::ldf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;

x3::rule< class node_attribute_protocol_version, node::attribute::protocol_version_t > const
    node_attribute_protocol_version = "node_attribute_protocol_version";
x3::rule< class node_attribute_configured_nad, node::attribute::configured_nad_t > const
    node_attribute_configured_nad = "node_attribute_configured_nad";
x3::rule< class node_attribute_initial_nad, node::attribute::initial_nad_t > const
    node_attribute_initial_nad = "node_attribute_initial_nad";
x3::rule< class node_attribute_product_id, node::attribute::product_id_t > const
    node_attribute_product_id = "node_attribute_product_id";
x3::rule< class node_attribute_response_error, node::attribute::response_error_t > const
    node_attribute_response_error = "node_attribute_response_error";
x3::rule< class node_attribute_fault_state_signals, node::attribute::fault_state_signals_t > const
    node_attribute_fault_state_signals = "node_attribute_fault_state_signals";
x3::rule< class node_attribute_p2_min, node::attribute::p2_min_t > const node_attribute_p2_min =
    "node_attribute_p2_min";
x3::rule< class node_attribute_st_min, node::attribute::st_min_t > const node_attribute_st_min =
    "node_attribute_st_min";
x3::rule< class node_attribute_n_as_timeout, node::attribute::n_as_timeout_t > const
    node_attribute_n_as_timeout = "node_attribute_n_as_timeout";
x3::rule< class node_attribute_n_cr_timeout, node::attribute::n_cr_timeout_t > const
    node_attribute_n_cr_timeout = "node_attribute_n_cr_timeout";
x3::rule< class node_attribute_configurable_frame, node::attribute::configurable_frame_t > const
    node_attribute_configurable_frame = "node_attribute_configurable_frame";
x3::rule< class node_attribute_configurable_frames, node::attribute::configurable_frames_t > const
    node_attribute_configurable_frames = "node_attribute_configurable_frames";

auto const node_attribute_name         = identifier;
auto const node_attribute_diag_address = integer;
auto const node_attribute_supplier_id  = integer;
auto const node_attribute_function_id  = integer;
auto const node_attribute_variant      = integer;
auto const node_attribute_signal_name  = identifier;
auto const node_attribute_frame_name   = identifier;
auto const node_attribute_message_id   = integer;

auto const node_attribute_protocol_version_def = x3::lit("LIN_protocol") > '=' > char_string > ';';
auto const node_attribute_configured_nad_def   = x3::lit("configured_NAD") > '=' >
                                               node_attribute_diag_address > ';';
auto const node_attribute_initial_nad_def = x3::lit("initial_NAD") > '=' >
                                            node_attribute_diag_address > ';';
auto const node_attribute_product_id_def = x3::lit("product_id") > '=' >
                                           node_attribute_supplier_id > ',' >
                                           node_attribute_function_id >
                                           -(',' > node_attribute_variant) > ';';
auto const node_attribute_response_error_def = x3::lit("response_error") > '=' >
                                               node_attribute_signal_name > ';';
auto const node_attribute_fault_state_signals_def = x3::lit("fault_state_signals") > '=' >
                                                    node_attribute_signal_name % ',' > ';';
auto const node_attribute_p2_min_def       = x3::lit("P2_min") > '=' > real_or_integer > "ms" > ';';
auto const node_attribute_st_min_def       = x3::lit("ST_min") > '=' > real_or_integer > "ms" > ';';
auto const node_attribute_n_as_timeout_def = x3::lit("N_As_timeout") > '=' > real_or_integer >
                                             "ms" > ';';
auto const node_attribute_n_cr_timeout_def = x3::lit("N_Cr_timeout") > '=' > real_or_integer >
                                             "ms" > ';';
auto const node_attribute_configurable_frame_def = node_attribute_frame_name >
                                                   -('=' > node_attribute_message_id) > ';';
auto const node_attribute_configurable_frames_def = x3::lit("configurable_frames") > '{' >
                                                    *node_attribute_configurable_frame > '}';

BOOST_SPIRIT_DEFINE(
    node_attribute_protocol_version,
    node_attribute_configured_nad,
    node_attribute_initial_nad,
    node_attribute_product_id,
    node_attribute_response_error,
    node_attribute_fault_state_signals,
    node_attribute_p2_min,
    node_attribute_st_min,
    node_attribute_n_as_timeout,
    node_attribute_n_cr_timeout,
    node_attribute_configurable_frame,
    node_attribute_configurable_frames)

x3::rule< class node_attribute, node::attribute_t > const node_attribute    = "node_attribute";
x3::rule< class node_attributes, node::attributes_t > const node_attributes = "node_attributes";

auto const node_attribute_name_action = [](auto &ctx) { x3::_val(ctx).name = x3::_attr(ctx); };
auto const node_attribute_protocol_version_action = [](auto &ctx) {
    x3::_val(ctx).protocol_version = x3::_attr(ctx);
};
auto const node_attribute_configured_nad_action = [](auto &ctx) {
    x3::_val(ctx).configured_nad = x3::_attr(ctx);
};
auto const node_attribute_initial_nad_action = [](auto &ctx) {
    x3::_val(ctx).initial_nad = x3::_attr(ctx);
};
auto const node_attribute_product_id_action = [](auto &ctx) {
    x3::_val(ctx).product_id = x3::_attr(ctx);
};
auto const node_attribute_response_error_action = [](auto &ctx) {
    x3::_val(ctx).response_error = x3::_attr(ctx);
};
auto const node_attribute_fault_state_signals_action = [](auto &ctx) {
    x3::_val(ctx).fault_state_signals = x3::_attr(ctx);
};
auto const node_attribute_p2_min_action = [](auto &ctx) { x3::_val(ctx).p2_min = x3::_attr(ctx); };
auto const node_attribute_st_min_action = [](auto &ctx) { x3::_val(ctx).st_min = x3::_attr(ctx); };
auto const node_attribute_n_as_timeout_action = [](auto &ctx) {
    x3::_val(ctx).n_as_timeout = x3::_attr(ctx);
};
auto const node_attribute_n_cr_timeout_action = [](auto &ctx) {
    x3::_val(ctx).n_cr_timeout = x3::_attr(ctx);
};
auto const node_attribute_configurable_frames_action = [](auto &ctx) {
    x3::_val(ctx).configurable_frames = x3::_attr(ctx);
};

auto const node_attribute_def =
    node_attribute_name[node_attribute_name_action] > '{' >
    *(node_attribute_protocol_version[node_attribute_protocol_version_action] |
      node_attribute_configured_nad[node_attribute_configured_nad_action] |
      node_attribute_initial_nad[node_attribute_initial_nad_action] |
      node_attribute_product_id[node_attribute_product_id_action] |
      node_attribute_response_error[node_attribute_response_error_action] |
      node_attribute_fault_state_signals[node_attribute_fault_state_signals_action] |
      node_attribute_p2_min[node_attribute_p2_min_action] |
      node_attribute_st_min[node_attribute_st_min_action] |
      node_attribute_n_as_timeout[node_attribute_n_as_timeout_action] |
      node_attribute_n_cr_timeout[node_attribute_n_cr_timeout_action] |
      node_attribute_configurable_frames[node_attribute_configurable_frames_action]) > '}';
auto const node_attributes_def = x3::lit("Node_attributes") > '{' > *node_attribute > '}';

BOOST_SPIRIT_DEFINE(node_attribute, node_attributes)

}    // namespace lin::ldf::parser

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::node::attribute::product_id_t, supplier, function, variant)

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::node::attribute::configurable_frame_t, name, id)
