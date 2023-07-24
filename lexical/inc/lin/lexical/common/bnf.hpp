#pragma once

#include <string>

#include <boost/spirit/home/x3.hpp>

namespace lin::lexical::common::bnf {

namespace x3 = boost::spirit::x3;

using char_string_t     = std::string;
using identifier_t      = std::string;
using integer_t         = int;
using real_or_integer_t = double;

namespace parser {

x3::rule< class char_string, char_string_t > const char_string             = "char_string";
x3::rule< class identifier, identifier_t > const identifier                = "identifier";
x3::rule< class integer, integer_t > const integer                         = "integer";
x3::rule< class real_or_integer, real_or_integer_t > const real_or_integer = "real_or_integer";

auto const char_string_def     = x3::lexeme['"' >> *(x3::ascii::char_ - '"') >> '"'];
auto const identifier_def      = x3::ascii::char_("a-zA-Z_") >> *x3::ascii::char_("a-zA-Z_0-9");
auto const integer_def         = ((x3::lit("0x") >> x3::hex) | x3::int_);
auto const real_or_integer_def = x3::double_;

BOOST_SPIRIT_DEFINE(char_string, identifier, integer, real_or_integer);

}    // namespace parser

}    // namespace lin::lexical::common::bnf
