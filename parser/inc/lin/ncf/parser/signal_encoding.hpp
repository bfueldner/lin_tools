#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/common/parser/signal_encoding.hpp>
#include <lin/ncf/signal_encoding.hpp>

/* 8.2.5.3 Signal encoding type definition */

namespace lin::ncf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;

x3::rule< class signal_encoding, signal::encoding_t > const signal_encoding    = "signal_encoding";
x3::rule< class signal_encodings, signal::encodings_t > const signal_encodings = "signal_encodings";

auto const signal_encoding_def  = identifier > '{' > *signal_encoding_value > '}';
auto const signal_encodings_def = x3::lit("encoding") > '{' > *signal_encoding > '}';

BOOST_SPIRIT_DEFINE(signal_encoding, signal_encodings)

}    // namespace lin::ncf::parser

BOOST_FUSION_ADAPT_STRUCT(lin::ncf::signal::encoding_t, name, values)
