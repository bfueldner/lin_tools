#pragma once

#include <boost/spirit/home/x3.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/ncf/parser/diagnostic.hpp>
#include <lin/ncf/parser/frame.hpp>
#include <lin/ncf/parser/free_text.hpp>
#include <lin/ncf/parser/general.hpp>
#include <lin/ncf/parser/signal.hpp>
#include <lin/ncf/parser/status.hpp>

#include <lin/ncf/node.hpp>

/* 8.2.2 Node definition */

namespace lin::ncf {

namespace node::parser {

using namespace common::bnf::parser;

auto const node_name = identifier;

}    // namespace node::parser

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace node::parser;
using namespace signal_encoding_type::parser;

x3::rule< class node_definition, node_t > const node_definition = "node_definition";

auto const node_name_action          = [](auto &ctx) { x3::_val(ctx).node_name = x3::_attr(ctx); };
auto const general_definition_action = [](auto &ctx) { x3::_val(ctx).general = x3::_attr(ctx); };
auto const diagnostic_definition_action = [](auto &ctx) {
    x3::_val(ctx).diagnostic = x3::_attr(ctx);
};
auto const frame_definition_action    = [](auto &ctx) { x3::_val(ctx).frames = x3::_attr(ctx); };
auto const encoding_definition_action = [](auto &ctx) { x3::_val(ctx).encodings = x3::_attr(ctx); };
auto const status_management_action   = [](auto &ctx) { x3::_val(ctx).status = x3::_attr(ctx); };
auto const free_text_definition_action = [](auto &ctx) {
    x3::_val(ctx).free_text = x3::_attr(ctx);
};

auto const node_definition_def = x3::lit("node") > node_name[node_name_action] > '{' >
                                 *(general_definition[general_definition_action] |
                                   diagnostic_definition[diagnostic_definition_action] |
                                   frame_definition[frame_definition_action] |
                                   encoding_definition[encoding_definition_action] |
                                   status_management[status_management_action] |
                                   free_text_definition[free_text_definition_action]) > '}';

BOOST_SPIRIT_DEFINE(node_definition)

}    // namespace parser

}    // namespace lin::ncf
