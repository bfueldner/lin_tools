#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/common/parser/signal_init_value.hpp>
#include <lin/ldf/signal_diagnostic.hpp>

/* 9.2.3.2 Diagnostic signals */

namespace lin::ldf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;

x3::rule< class diagnostic_signal, signal::diagnostic_t > const diagnostic_signal =
    "diagnostic_signal";
x3::rule< class diagnostic_signals, signal::diagnostics_t > const diagnostic_signals =
    "diagnostic_signals";

auto const diagnostic_signal_name = identifier;
auto const diagnostic_signal_size = integer;

auto const diagnostic_signal_def = diagnostic_signal_name > ':' > diagnostic_signal_size > ',' >
                                   signal_init_value > ';';
auto const diagnostic_signals_def = x3::lit("Diagnostic_signals") > '{' > *diagnostic_signal > '}';

BOOST_SPIRIT_DEFINE(diagnostic_signal, diagnostic_signals)

}    // namespace lin::ldf::parser

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::signal::diagnostic_t, name, size, init_value)
