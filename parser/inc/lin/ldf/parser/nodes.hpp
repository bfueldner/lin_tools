#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/ldf/nodes.hpp>

/* 9.2.2.1 Participating nodes */

namespace lin::ldf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;

x3::rule< class nodes_master, nodes::master_t > const nodes_master = "nodes_master";
x3::rule< class nodes_slaves, nodes::slaves_t > const nodes_slaves = "nodes_slaves";
x3::rule< class nodes, nodes_t > const nodes                       = "nodes";

auto const nodes_node_name = identifier;
auto const nodes_time_base = real_or_integer;
auto const nodes_jitter    = real_or_integer;

auto const nodes_master_action = [](auto &ctx) { x3::_val(ctx).master = x3::_attr(ctx); };
auto const nodes_slaves_action = [](auto &ctx) { x3::_val(ctx).slaves = x3::_attr(ctx); };

auto const nodes_master_def = x3::lit("Master") > ':' > nodes_node_name > ',' > nodes_time_base >
                              "ms" > ',' > nodes_jitter > "ms" > ';';
auto const nodes_slaves_def = x3::lit("Slaves") > ':' > nodes_node_name % ',' > ';';
auto const nodes_def        = x3::lit("Nodes") > '{' > *(nodes_master[nodes_master_action] |
                                                  nodes_slaves[nodes_slaves_action]) > '}';

BOOST_SPIRIT_DEFINE(nodes_master, nodes_slaves, nodes)

}    // namespace lin::ldf::parser

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::nodes::master_t, name, time_base, jitter)
