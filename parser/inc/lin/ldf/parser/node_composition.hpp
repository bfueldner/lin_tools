#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/ldf/node_composition.hpp>

/* 9.2.2.3 Node composition definition */

namespace lin::ldf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;

x3::rule< class node_composite, node::composition::configuration::composite_t > const
    node_composite = "node_composite";
x3::rule< class node_configuration, node::composition::configuration_t > const node_configuration =
    "node_configuration";
x3::rule< class node_compositions, node::compositions_t > const node_compositions =
    "node_compositions";

auto const composite_name     = identifier;
auto const composite_node     = identifier;
auto const configuration_name = identifier;
auto const logical_node       = identifier;

auto const node_composite_def     = composite_name > '{' > composite_node % ',' > ';' > '}';
auto const node_configuration_def = x3::lit("configuration") > configuration_name > '{' >
                                    *node_composite > '}';
auto const node_compositions_def = x3::lit("composite") > '{' > *node_configuration > '}';

BOOST_SPIRIT_DEFINE(node_composite, node_configuration, node_compositions)

}    // namespace lin::ldf::parser

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::node::composition::configuration::composite_t, name, nodes)

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::node::composition::configuration_t, name, composites)
