#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/common/signal_encoding_type.hpp>

/* Common signal encoding type definition */

namespace lin::common::signal_encoding_type::parser {

namespace x3 = boost::spirit::x3;

//using namespace lexical::common::bnf;
//using namespace type::common::signal_encoding_type;
using namespace common::bnf::parser;

// NOLINTBEGIN(bugprone-forward-declaration-namespace)
x3::rule< class logical_value, logical_value_t > const logical_value    = "logical_value";
x3::rule< class physical_range, physical_range_t > const physical_range = "physical_range";
x3::rule< class bcd_value, bcd_value_t > const bcd_value                = "bcd_value";
x3::rule< class ascii_value, ascii_value_t > const ascii_value          = "ascii_value";
x3::rule< class value, value_t > const value                            = "value";
// NOLINTEND(bugprone-forward-declaration-namespace)

auto const signal_value = integer;
auto const min_value    = integer;
auto const max_value    = integer;
auto const scale        = real_or_integer;
auto const offset       = real_or_integer;
auto const text_info    = char_string;

auto const logical_value_def = x3::lit("logical_value") > ',' > signal_value > -(',' > text_info) >
                               ';';
auto const physical_range_def = x3::lit("physical_value") > ',' > min_value > ',' > max_value >
                                ',' > scale > ',' > offset > -(',' > text_info) > ';';
auto const bcd_value_def   = x3::lit("bcd_value") > ';';
auto const ascii_value_def = x3::lit("ascii_value") > ';';
auto const value_def       = logical_value | physical_range | bcd_value | ascii_value;

BOOST_SPIRIT_DEFINE(logical_value, physical_range, bcd_value, ascii_value, value);

}    // namespace lin::common::signal_encoding_type::parser

BOOST_FUSION_ADAPT_STRUCT(
    lin::common::signal_encoding_type::logical_value_t,
    signal_value,
    text_info)
BOOST_FUSION_ADAPT_STRUCT(
    lin::common::signal_encoding_type::physical_range_t,
    min_value,
    max_value,
    scale,
    offset,
    text_info)
