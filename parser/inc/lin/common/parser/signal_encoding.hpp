#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/common/signal_encoding.hpp>

/* Common signal encoding type definition */

namespace lin::common::parser {

namespace x3 = boost::spirit::x3;

// NOLINTBEGIN(bugprone-forward-declaration-namespace)
x3::rule< class signal_encoding_logical_value, signal::encoding::logical_value_t > const
    signal_encoding_logical_value = "signal_encoding_logical_value";
x3::rule< class signal_encoding_physical_range, signal::encoding::physical_range_t > const
    signal_encoding_physical_range = "signal_encoding_physical_range";
x3::rule< class signal_encoding_bcd_value, signal::encoding::bcd_value_t > const
    signal_encoding_bcd_value = "signal_encoding_bcd_value";
x3::rule< class signal_encoding_ascii_value, signal::encoding::ascii_value_t > const
    signal_encoding_ascii_value = "signal_encoding_ascii_value";
x3::rule< class signal_encoding_value, signal::encoding::value_t > const signal_encoding_value =
    "signal_encoding_value";
// NOLINTEND(bugprone-forward-declaration-namespace)

auto const signal_encoding_signal_value = integer;
auto const signal_encoding_min_value    = integer;
auto const signal_encoding_max_value    = integer;
auto const signal_encoding_scale        = real_or_integer;
auto const signal_encoding_offset       = real_or_integer;
auto const signal_encoding_text_info    = char_string;

auto const signal_encoding_logical_value_def = x3::lit("logical_value") > ',' >
                                               signal_encoding_signal_value >
                                               -(',' > signal_encoding_text_info) > ';';
auto const signal_encoding_physical_range_def = x3::lit("physical_value") > ',' >
                                                signal_encoding_min_value > ',' >
                                                signal_encoding_max_value > ',' >
                                                signal_encoding_scale > ',' >
                                                signal_encoding_offset >
                                                -(',' > signal_encoding_text_info) > ';';
auto const signal_encoding_bcd_value_def   = x3::lit("bcd_value") > ';';
auto const signal_encoding_ascii_value_def = x3::lit("ascii_value") > ';';
auto const signal_encoding_value_def       = signal_encoding_logical_value |
                                       signal_encoding_physical_range | signal_encoding_bcd_value |
                                       signal_encoding_ascii_value;

BOOST_SPIRIT_DEFINE(
    signal_encoding_logical_value,
    signal_encoding_physical_range,
    signal_encoding_bcd_value,
    signal_encoding_ascii_value,
    signal_encoding_value)

}    // namespace lin::common::parser

BOOST_FUSION_ADAPT_STRUCT(lin::common::signal::encoding::logical_value_t, value, text_info)

BOOST_FUSION_ADAPT_STRUCT(
    lin::common::signal::encoding::physical_range_t,
    min,
    max,
    scale,
    offset,
    text_info)
