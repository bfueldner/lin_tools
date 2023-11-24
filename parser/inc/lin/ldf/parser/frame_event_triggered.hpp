#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/ldf/frame_event_triggered.hpp>

/* 9.2.4.3 Event triggered frames */

namespace lin::ldf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;

x3::rule< class event_triggered_frame, frame::event_triggered_t > const event_triggered_frame =
    "event_triggered_frame";
x3::rule< class event_triggered_frames, frame::event_triggereds_t > const event_triggered_frames =
    "event_triggered_frames";

auto const event_triggered_frame_name           = identifier;
auto const event_triggered_frame_schedule_table = identifier;
auto const event_triggered_frame_id             = integer;

auto const event_triggered_frame_def = event_triggered_frame_name > ':' >
                                       event_triggered_frame_schedule_table > ',' >
                                       event_triggered_frame_id > ',' >
                                       event_triggered_frame_name % ',' > ';';
auto const event_triggered_frames_def = x3::lit("Event_triggered_frames") > '{' >
                                        *event_triggered_frame > '}';

BOOST_SPIRIT_DEFINE(event_triggered_frame, event_triggered_frames)

}    // namespace lin::ldf::parser

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::frame::event_triggered_t, name, schedule_table, id, frames)
