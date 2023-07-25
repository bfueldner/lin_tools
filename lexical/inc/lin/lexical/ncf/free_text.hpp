#pragma once

#include <lin/lexical/common/bnf.hpp>

/* 8.2.7 Free text definition */

namespace lin::lexical::ncf {

using free_text_t = common::bnf::char_string_t;

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

/* 8.2.7 Free text definition */

x3::rule< class free_text_definition, free_text_t > const free_text_definition =
    "free_text_definition";

auto const free_text_definition_def = x3::lit("free_text") > '{' > char_string > '}';

BOOST_SPIRIT_DEFINE(free_text_definition);

}    // namespace parser

}    // namespace lin::lexical::ncf
