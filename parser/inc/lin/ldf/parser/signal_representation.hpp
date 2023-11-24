#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/ldf/signal_representation.hpp>

/* 9.2.6.2 Signal representation definition */

namespace lin::ldf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;

x3::rule< class signal_representation, signal::representation_t > const signal_representation =
    "signal_representation";
x3::rule< class signal_representations, signal::representations_t > const signal_representations =
    "signal_representations";

auto const signal_representation_name   = identifier;
auto const signal_representation_signal = identifier;

auto const signal_representation_def = signal_representation_name > ':' >
                                       signal_representation_signal % ',' > ';';
auto const signal_representations_def = x3::lit("Signal_representation") > '{' >
                                        *signal_representation > '}';

BOOST_SPIRIT_DEFINE(signal_representation, signal_representations)

}    // namespace lin::ldf::parser

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::signal::representation_t, name, signals)
