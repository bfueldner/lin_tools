#pragma once

#include <boost/spirit/home/x3/string/symbols.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/ncf/parser/signal.hpp>

#include <lin/ncf/frame.hpp>

namespace lin::ncf {

/* 8.2.5.1 Frame properties */

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

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

BOOST_SPIRIT_DEFINE(frame_properties)

}    // namespace parser

/* 8.2.5 Frame definition */

namespace frame::parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;
using namespace ncf::parser;

struct frame_kind_t: x3::symbols< frame::frame_kind_t >
{
    frame_kind_t()
    {
        add("publish", frame::frame_kind_t::publish)("subscribe", frame::frame_kind_t::subscribe);
    }
};

x3::rule< class single_frame, single_frame_t > const single_frame = "single_frame";

auto const frame_kind_action       = [](auto &ctx) { x3::_val(ctx).frame_kind = x3::_attr(ctx); };
auto const frame_name_action       = [](auto &ctx) { x3::_val(ctx).frame_name = x3::_attr(ctx); };
auto const frame_properties_action = [](auto &ctx) {
    x3::_val(ctx).frame_properties = x3::_attr(ctx);
};
auto const signal_definition_action = [](auto &ctx) {
    x3::_val(ctx).signal_definition = x3::_attr(ctx);
};

frame_kind_t const frame_kind;
auto const frame_name = identifier;

/* NOTE: frame_properties and signal_definition are position dependent. */
auto const single_frame_def = frame_kind[frame_kind_action] > frame_name[frame_name_action] > '{' >
                              frame_properties[frame_properties_action] >
                              signal_definition[signal_definition_action] > '}';

BOOST_SPIRIT_DEFINE(single_frame)

}    // namespace frame::parser

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;
using namespace frame::parser;

x3::rule< class frame_definition, frames_t > const frame_definition = "frame_definition";

auto const frame_definition_def = x3::lit("frames") > '{' > *single_frame > '}';

BOOST_SPIRIT_DEFINE(frame_definition)

}    // namespace parser

}    // namespace lin::ncf