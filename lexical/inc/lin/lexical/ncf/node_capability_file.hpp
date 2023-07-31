#pragma once

#include <lin/lexical/common/bnf.hpp>
#include <lin/lexical/common/comment.hpp>

#include <lin/lexical/ncf/node.hpp>

/* 8.2.2 Node definition */

namespace lin::lexical::ncf {

namespace node_capability_file {

using language_version_t = common::bnf::char_string_t;

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

x3::rule< class language_version, language_version_t > const language_version = "language_version";

auto const language_version_def = x3::lit("LIN_language_version") > '=' > char_string > ';';

BOOST_SPIRIT_DEFINE(language_version);

}    // namespace parser

}    // namespace node_capability_file


struct node_capability_file_t
{
    node_capability_file::language_version_t language_version;
    std::vector< node_t > node;
};

namespace parser {

namespace x3 = boost::spirit::x3;

//using namespace common::bnf::parser;
//using namespace ncf::parser;
using namespace common::comment::parser;
using namespace node_capability_file::parser;
using namespace node::parser;

x3::rule< class node_capability_file_definition, node_capability_file_t > const
    node_capability_file_definition = "node_capability_file_definition";

auto const node_capability_file_definition_def =
    x3::skip(comment)[x3::lit("node_capability_file") > ';' > language_version > *node_definition];

BOOST_SPIRIT_DEFINE(node_capability_file_definition);

}    // namespace parser

}    // namespace lin::lexical::ncf

BOOST_FUSION_ADAPT_STRUCT(lin::lexical::ncf::node_capability_file_t, language_version, node)
