#pragma once

#include <boost/spirit/home/x3/string/symbols.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/ncf/frame.hpp>
#include <lin/ncf/parser/signal.hpp>

/* 8.2.5 Frame definition */
/* 8.2.5.1 Frame properties */

namespace lin::ncf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;

struct kind_t: x3::symbols< frame::kind_t >
{
    kind_t() { add("publish", frame::kind_t::publish)("subscribe", frame::kind_t::subscribe); }
};

x3::rule< class frame, frame_t > const frame    = "frame";
x3::rule< class frames, frames_t > const frames = "frames";

auto const frame_name_action       = [](auto &ctx) { x3::_val(ctx).name = x3::_attr(ctx); };
auto const frame_kind_action       = [](auto &ctx) { x3::_val(ctx).kind = x3::_attr(ctx); };
auto const frame_size_action       = [](auto &ctx) { x3::_val(ctx).size = x3::_attr(ctx); };
auto const frame_min_period_action = [](auto &ctx) { x3::_val(ctx).min_period = x3::_attr(ctx); };
auto const frame_max_period_action = [](auto &ctx) { x3::_val(ctx).max_period = x3::_attr(ctx); };
auto const frame_event_triggered_frame_action = [](auto &ctx) {
    x3::_val(ctx).event_triggered_frame = x3::_attr(ctx);
};
auto const signals_action = [](auto &ctx) { x3::_val(ctx).signals = x3::_attr(ctx); };

kind_t const frame_kind;
auto const frame_name = identifier;

auto const frame_def =
    frame_kind[frame_kind_action] > frame_name[frame_name_action] > '{' >
    *((x3::lit("length") > '=' > integer[frame_size_action] > ';') |
      (x3::lit("min_period") > '=' > integer[frame_min_period_action] > "ms" > ';') |
      (x3::lit("max_period") > '=' > integer[frame_max_period_action] > "ms" > ';') |
      (x3::lit("event_triggered_frame") > '=' > identifier[frame_event_triggered_frame_action] >
       ';')) > signals_[signals_action] > '}';
auto const frames_def = x3::lit("frames") > '{' > *frame > '}';

BOOST_SPIRIT_DEFINE(frame, frames)

}    // namespace lin::ncf::parser
