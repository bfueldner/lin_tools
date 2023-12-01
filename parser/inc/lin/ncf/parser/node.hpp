#pragma once

#include <boost/spirit/home/x3.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/ncf/node.hpp>
#include <lin/ncf/parser/diagnostic.hpp>
#include <lin/ncf/parser/frame.hpp>
#include <lin/ncf/parser/free_text.hpp>
#include <lin/ncf/parser/general.hpp>
#include <lin/ncf/parser/signal_encoding.hpp>
#include <lin/ncf/parser/status_management.hpp>

/* 8.2.2 Node definition */

namespace lin::ncf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;
using namespace ncf::parser;

auto const node_name = identifier;

x3::rule< class node, node_t > const node = "node";

auto const node_name_action       = [](auto &ctx) { x3::_val(ctx).name = x3::_attr(ctx); };
auto const node_general_action    = [](auto &ctx) { x3::_val(ctx).general = x3::_attr(ctx); };
auto const node_diagnostic_action = [](auto &ctx) { x3::_val(ctx).diagnostic = x3::_attr(ctx); };
auto const node_frames_action     = [](auto &ctx) { x3::_val(ctx).frames = x3::_attr(ctx); };
auto const node_signal_encodings_action = [](auto &ctx) {
    x3::_val(ctx).signal_encodings = x3::_attr(ctx);
};
auto const node_status_management_action = [](auto &ctx) {
    x3::_val(ctx).status_management = x3::_attr(ctx);
};
auto const node_free_text_action = [](auto &ctx) { x3::_val(ctx).free_text = x3::_attr(ctx); };

auto const node_def = x3::lit("node") > node_name[node_name_action] > '{' >
                      *(parser::general[node_general_action] |
                        parser::diagnostic[node_diagnostic_action] |
                        parser::frames[node_frames_action] |
                        parser::signal_encodings[node_signal_encodings_action] |
                        status_management[node_status_management_action] |
                        free_text[node_free_text_action]) > '}';

BOOST_SPIRIT_DEFINE(node)

}    // namespace lin::ncf::parser
