#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/common/parser/signal_init_value.hpp>
#include <lin/ncf/signal.hpp>

/* 8.2.5.2 Signal definition */

namespace lin::ncf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;

x3::rule< class signal_, signal_t > const signal_ =    // NOLINT(readability-identifier-naming)
    "signal";
x3::rule< class signals_, signals_t > const signals_ =    // NOLINT(readability-identifier-naming)
    "signals";

auto const signal_name_action       = [](auto &ctx) { x3::_val(ctx).name = x3::_attr(ctx); };
auto const signal_init_value_action = [](auto &ctx) { x3::_val(ctx).init_value = x3::_attr(ctx); };
auto const signal_size_action       = [](auto &ctx) { x3::_val(ctx).size = x3::_attr(ctx); };
auto const signal_offset_action     = [](auto &ctx) { x3::_val(ctx).offset = x3::_attr(ctx); };
auto const signal_encoding_name_action = [](auto &ctx) { x3::_val(ctx).encoding = x3::_attr(ctx); };

auto const signal_name   = identifier;
auto const encoding_name = identifier;
auto const signal__def   = signal_name[signal_name_action] > '{' >
                         *((x3::lit("init_value") > '=' >
                            signal_init_value[signal_init_value_action] > ';') |
                           (x3::lit("size") > '=' > integer[signal_size_action] > ';') |
                           (x3::lit("offset") > '=' > integer[signal_offset_action] > ';')) >
                         -(encoding_name[signal_encoding_name_action] > ';') > '}';
auto const signals__def = x3::lit("signals") > '{' > *signal_ > '}';

BOOST_SPIRIT_DEFINE(signal_, signals_)

}    // namespace lin::ncf::parser

BOOST_FUSION_ADAPT_STRUCT(lin::ncf::signal_t, name, init_value, size, offset, encoding)
