#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/common/parser/signal_init_value.hpp>
#include <lin/ldf/signal_standard.hpp>

/* 9.2.3.1 Standard signals */

namespace lin::ldf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;

x3::rule< class standard_signal, signal::standard_t > const standard_signal    = "standard_signal";
x3::rule< class standard_signals, signal::standards_t > const standard_signals = "standard_signals";

auto const standard_signal_name          = identifier;
auto const standard_signal_size          = integer;
auto const standard_signal_published_by  = identifier;
auto const standard_signal_subscribed_by = identifier;

auto const standard_signal_def = standard_signal_name > ':' > standard_signal_size > ',' >
                                 signal_init_value > ',' > standard_signal_published_by >
                                 *(',' > standard_signal_subscribed_by) > ';';
auto const standard_signals_def = x3::lit("Signals") > '{' > *standard_signal > '}';

BOOST_SPIRIT_DEFINE(standard_signal, standard_signals)

}    // namespace lin::ldf::parser

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::signal::standard_t,
    name,
    size,
    init_value,
    published_by,
    subscribed_by)
