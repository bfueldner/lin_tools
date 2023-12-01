#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/ldf/frame_sporadic.hpp>

/* 9.2.4.2 Sporadic frames */

namespace lin::ldf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;

x3::rule< class sporadic, frame::sporadic_t > const sporadic_frame    = "sporadic_frame";
x3::rule< class sporadics, frame::sporadics_t > const sporadic_frames = "sporadic_frames";

auto const sporadic_frame_name = identifier;

auto const sporadic_frame_def  = sporadic_frame_name > ':' > sporadic_frame_name % ',' > ';';
auto const sporadic_frames_def = x3::lit("Sporadic_frames") > '{' > *sporadic_frame > '}';

BOOST_SPIRIT_DEFINE(sporadic_frame, sporadic_frames)

}    // namespace lin::ldf::parser

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::frame::sporadic_t, name, frames)
