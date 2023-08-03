#pragma once

#include <variant>
#include <vector>

#include <boost/spirit/home/x3/string/symbols.hpp>

#include <lin/lexical/common/bnf.hpp>

#include <lin/lexical/ncf/frame_properties.hpp>
#include <lin/lexical/ncf/signal.hpp>

/* 8.2.5 Frame definition */

namespace lin::lexical::ncf {

namespace frame {

enum class frame_kind_t
{
    publish,
    subscribe,
};

using frame_name_t = common::bnf::identifier_t;

struct single_frame_t
{
    frame_kind_t frame_kind{};
    frame_name_t frame_name{};
    frame_properties_t frame_properties{};
    signals_t signal_definition{};
};

namespace parser {

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

BOOST_SPIRIT_DEFINE(single_frame);

}    // namespace parser

}    // namespace frame

using frames_t = std::vector< frame::single_frame_t >;

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;
using namespace frame::parser;

/* 8.2.5 Frame definition */

x3::rule< class frame_definition, frames_t > const frame_definition = "frame_definition";

auto const frame_definition_def = x3::lit("frames") > '{' > *single_frame > '}';

BOOST_SPIRIT_DEFINE(frame_definition);

}    // namespace parser

}    // namespace lin::lexical::ncf

BOOST_FUSION_ADAPT_STRUCT(
    lin::lexical::ncf::frame::single_frame_t,
    frame_kind,
    frame_name,
    frame_properties,
    signal_definition)