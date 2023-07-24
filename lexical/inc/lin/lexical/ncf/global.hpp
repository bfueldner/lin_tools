#pragma once

#include <lin/lexical/common/bnf.hpp>

/* 8.2.1 Global definition */

namespace lin::lexical::ncf::global {

/* 8.2.1.1 Node capability language version number definition */

using language_version_t = common::bnf::char_string_t;

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

x3::rule< class language_version, language_version_t > const language_version = "language_version";

auto const language_version_def = x3::lit("LIN_language_version") > '=' > char_string > ';';

BOOST_SPIRIT_DEFINE(language_version);

}    // namespace parser

}    // namespace lin::lexical::ncf::global
