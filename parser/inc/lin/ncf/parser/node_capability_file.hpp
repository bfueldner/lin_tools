#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/comment.hpp>
#include <lin/ncf/node_capability_file.hpp>
#include <lin/ncf/parser/global.hpp>
#include <lin/ncf/parser/node.hpp>

/* 8.2.2 Node definition */

namespace lin::ncf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;

x3::rule< class node_capability_file, node_capability_file_t > const node_capability_file =
    "node_capability_file";

auto const node_capability_file_def =
    x3::skip(comment)[x3::lit("node_capability_file") > ';' > language_version > *node];

BOOST_SPIRIT_DEFINE(node_capability_file)

}    // namespace lin::ncf::parser

BOOST_FUSION_ADAPT_STRUCT(lin::ncf::node_capability_file_t, language_version, nodes)
