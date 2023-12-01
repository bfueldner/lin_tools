#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/common/parser/signal_encoding.hpp>
#include <lin/ldf/signal_encoding.hpp>

/* 9.2.6.1 Signal encoding type definition */

namespace lin::ldf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;

x3::rule< class signal_encoding, signal::encoding_t > const signal_encoding    = "signal_encoding";
x3::rule< class signal_encodings, signal::encodings_t > const signal_encodings = "signal_encodings";

auto const signal_encoding_name = identifier;

auto const signal_encoding_def  = signal_encoding_name > '{' > *signal_encoding_value > '}';
auto const signal_encodings_def = x3::lit("Signal_encoding_types") > '{' > *signal_encoding > '}';

BOOST_SPIRIT_DEFINE(signal_encoding, signal_encodings)

}    // namespace lin::ldf::parser

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::signal::encoding_t, name, values)
