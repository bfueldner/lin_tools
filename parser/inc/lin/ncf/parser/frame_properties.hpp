#pragma once

#include <boost/spirit/home/x3.hpp>

#include <lin/common/parser/bnf.hpp>

#include <lin/ncf/frame_properties.hpp>

/* 8.2.5.1 Frame properties */

namespace lin::ncf ::parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

/* 8.2.5.1 Frame properties */

x3::rule< class frame_properties, frame_properties_t > const frame_properties = "frame_properties";

auto const length_action     = [](auto &ctx) { x3::_val(ctx).length = x3::_attr(ctx); };
auto const min_period_action = [](auto &ctx) { x3::_val(ctx).min_period = x3::_attr(ctx); };
auto const max_period_action = [](auto &ctx) { x3::_val(ctx).max_period = x3::_attr(ctx); };
auto const event_triggered_frame_action = [](auto &ctx) {
    x3::_val(ctx).event_triggered_frame = x3::_attr(ctx);
};

auto const frame_properties_def =
    *((x3::lit("length") > '=' > integer[length_action] > ';') |
      (x3::lit("min_period") > '=' > integer[min_period_action] > "ms" > ';') |
      (x3::lit("max_period") > '=' > integer[max_period_action] > "ms" > ';') |
      (x3::lit("event_triggered_frame") > '=' > identifier[event_triggered_frame_action] > ';'));

BOOST_SPIRIT_DEFINE(frame_properties);

}    // namespace lin::ncf::parser
