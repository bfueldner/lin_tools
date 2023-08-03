#pragma once

#include <lin/lexical/common/bnf.hpp>

/* 9.2.2 Node definition */

namespace lin::lexical::ldf {

namespace nodes {

/* 9.2.2.1 Participating nodes */

struct master_t
{
    common::bnf::identifier_t node_name{};
    common::bnf::real_or_integer_t time_base{};
    common::bnf::real_or_integer_t jitter{};
};

using slaves_t = std::vector< common::bnf::identifier_t >;

namespace parser {

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

BOOST_SPIRIT_DEFINE(master, slaves);

}    // namespace parser

}    // namespace nodes

struct nodes_t
{
    nodes::master_t master{};
    nodes::slaves_t slaves{};
};

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace nodes::parser;

x3::rule< class nodes, nodes_t > const nodes = "nodes";

auto const master_action = [](auto &ctx) { x3::_val(ctx).master = x3::_attr(ctx); };
auto const slaves_action = [](auto &ctx) { x3::_val(ctx).slaves = x3::_attr(ctx); };

auto const nodes_def = x3::lit("Nodes") > '{' > *(master[master_action] | slaves[slaves_action]) >
                       '}';

BOOST_SPIRIT_DEFINE(nodes);

}    // namespace parser

}    // namespace lin::lexical::ldf

BOOST_FUSION_ADAPT_STRUCT(lin::lexical::ldf::nodes::master_t, node_name, time_base, jitter)
BOOST_FUSION_ADAPT_STRUCT(lin::lexical::ldf::nodes_t, master, slaves)
