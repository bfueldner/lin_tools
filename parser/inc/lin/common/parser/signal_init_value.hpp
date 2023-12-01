#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/common/signal_init_value.hpp>

/* Common signal init value definition */

namespace lin::common::parser {

namespace x3 = boost::spirit::x3;

x3::rule< class signal_init_value_scalar, signal::init_value::scalar_t > const
    signal_init_value_scalar = "signal_init_value_scalar";
x3::rule< class signal_init_value_array, signal::init_value::array_t > const
    signal_init_value_array = "signal_init_value_array";
x3::rule< class signal_init_value, signal::init_value_t > const signal_init_value =
    "signal_init_value";

auto const signal_init_value_scalar_def = integer;
auto const signal_init_value_array_def  = '{' >> integer % ',' >> '}';
auto const signal_init_value_def        = signal_init_value_scalar | signal_init_value_array;

BOOST_SPIRIT_DEFINE(signal_init_value_scalar, signal_init_value_array, signal_init_value)

}    // namespace lin::common::parser
