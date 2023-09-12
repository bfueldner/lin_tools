#pragma once

#include <lin/lexical/common/bnf.hpp>

#include <lin/lexical/ncf/diagnostic.hpp>
#include <lin/lexical/ncf/frame.hpp>
#include <lin/lexical/ncf/free_text.hpp>
#include <lin/lexical/ncf/general.hpp>
#include <lin/lexical/ncf/signal_encoding_type.hpp>
#include <lin/lexical/ncf/status.hpp>

/* 8.2.2 Node definition */

namespace lin::lexical::ncf {

namespace node {

using node_name_t = common::bnf::identifier_t;

namespace parser {

using namespace common::bnf::parser;

auto const node_name = identifier;

}    // namespace parser

}    // namespace node

struct node_t
{
    node::node_name_t node_name{};
    general_t general{};
    diagnostic_t diagnostic{};
    frames_t frames{};
    encodings_t encodings{};
    status_t status{};
    free_text_t free_text{};
};

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace node::parser;

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

BOOST_SPIRIT_DEFINE(node_definition);

}    // namespace parser

}    // namespace lin::lexical::ncf
