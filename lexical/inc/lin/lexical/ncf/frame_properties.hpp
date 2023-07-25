#pragma once

#include <variant>
#include <vector>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <lin/lexical/common/bnf.hpp>

/* 8.2.5.1 Frame properties */

namespace lin::lexical::ncf {

struct frame_properties_t
{
    common::bnf::integer_t length{};
    common::bnf::integer_t min_period{};
    common::bnf::integer_t max_period{};
    common::bnf::identifier_t event_triggered_frame{};
};

namespace parser {

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

}    // namespace parser

}    // namespace lin::lexical::ncf

BOOST_FUSION_ADAPT_STRUCT(
    lin::lexical::ncf::frame_properties_t,
    length,
    min_period,
    max_period,
    event_triggered_frame)
