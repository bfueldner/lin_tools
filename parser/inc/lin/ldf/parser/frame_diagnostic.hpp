#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/ldf/frame_diagnostic.hpp>

/* 9.2.4.4 Diagnostic frames */

namespace lin::ldf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;

x3::rule< class diagnostic_frame_signal, frame::diagnostic::signal_t > const
    diagnostic_frame_signal = "diagnostic_frame_signal";
x3::rule< class diagnostic_frame, frame::diagnostic_t > const diagnostic_frame = "diagnostic_frame";
x3::rule< class diagnostic_frames, frame::diagnostics_t > const diagnostic_frames =
    "diagnostic_frames";

auto const diagnostic_frame_signal_name   = identifier;
auto const diagnostic_frame_signal_offset = integer;
auto const diagnostic_frame_name          = identifier;
auto const diagnostic_frame_id            = integer;

auto const diagnostic_frame_signal_def = diagnostic_frame_signal_name > ',' >
                                         diagnostic_frame_signal_offset > ';';
auto const diagnostic_frame_def = diagnostic_frame_name > ':' > diagnostic_frame_id > '{' >
                                  *diagnostic_frame_signal > '}';
auto const diagnostic_frames_def = x3::lit("Diagnostic_frames") > '{' > *diagnostic_frame > '}';

BOOST_SPIRIT_DEFINE(diagnostic_frame_signal, diagnostic_frame, diagnostic_frames)

}    // namespace lin::ldf::parser

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::frame::diagnostic::signal_t, name, offset)

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::frame::diagnostic_t, name, id, signals)
