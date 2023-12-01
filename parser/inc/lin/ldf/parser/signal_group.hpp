#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/ldf/signal_group.hpp>

/* 9.2.3.3 Signal groups */

namespace lin::ldf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;

x3::rule< class signal_group_signal, signal::group::signal_t > const signal_group_signal =
    "signal_group_signal";
x3::rule< class signal_group, signal::group_t > const signal_group    = "signal_group";
x3::rule< class signal_groups, signal::groups_t > const signal_groups = "signal_groups";

auto const signal_group_signal_name   = identifier;
auto const signal_group_signal_offset = integer;

auto const signal_group_name = identifier;
auto const signal_group_size = integer;

auto const signal_group_signal_def = signal_group_signal_name > ',' > signal_group_signal_offset >
                                     ';';
auto const signal_group_def = signal_group_name > ':' > signal_group_size > '{' >
                              *signal_group_signal > '}';
auto const signal_groups_def = x3::lit("Signal_groups") > '{' > *signal_group > '}';

BOOST_SPIRIT_DEFINE(signal_group_signal, signal_group, signal_groups)

}    // namespace lin::ldf::parser

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::signal::group::signal_t, name, offset)

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::signal::group_t, name, size, signals)
