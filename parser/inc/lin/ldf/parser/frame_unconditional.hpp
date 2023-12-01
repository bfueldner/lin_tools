#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/ldf/frame_unconditional.hpp>

/* 9.2.4.1 Unconditional frames */

namespace lin::ldf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;

x3::rule< class unconditional_frame_signal, frame::unconditional::signal_t > const
    unconditional_frame_signal = "unconditional_frame_signal";
x3::rule< class unconditional_frame, frame::unconditional_t > const unconditional_frame =
    "unconditional_frame";
x3::rule< class unconditional_frames, frame::unconditionals_t > const unconditional_frames =
    "unconditional_frames";

auto const unconditional_frame_signal_name   = identifier;
auto const unconditional_frame_signal_offset = integer;

auto const unconditional_frame_name         = identifier;
auto const unconditional_frame_id           = integer;
auto const unconditional_frame_published_by = identifier;
auto const unconditional_frame_size         = integer;

auto const unconditional_frame_signal_def = unconditional_frame_signal_name > ',' >
                                            unconditional_frame_signal_offset > ';';
auto const unconditional_frame_def = unconditional_frame_name > ':' > unconditional_frame_id > ',' >
                                     unconditional_frame_published_by > ',' >
                                     unconditional_frame_size > '{' > *unconditional_frame_signal >
                                     '}';
auto const unconditional_frames_def = x3::lit("Frames") > '{' > *unconditional_frame > '}';

BOOST_SPIRIT_DEFINE(unconditional_frame_signal, unconditional_frame, unconditional_frames)

}    // namespace lin::ldf::parser

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::frame::unconditional::signal_t, name, offset)

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::frame::unconditional_t, name, id, published_by, size, signals)
