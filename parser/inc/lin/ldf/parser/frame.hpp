#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>

#include <lin/ldf/frame.hpp>

/* 9.2.4 Frame definition */

namespace lin::ldf::frame {

/* 9.2.4.1 Unconditional frames */

namespace unconditional_frame::parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

x3::rule< class frame_entry, frame_entry_t > const frame_entry = "frame_entry";

auto const signal_name   = identifier;
auto const signal_offset = integer;

auto const frame_entry_def = signal_name > ',' > signal_offset > ';';

BOOST_SPIRIT_DEFINE(frame_entry);

}    // namespace unconditional_frame::parser

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;
using namespace unconditional_frame::parser;

x3::rule< class unconditional_frame, unconditional_frame_t > const unconditional_frame =
    "unconditional_frame";
x3::rule< class unconditional_frames, unconditional_frames_t > const unconditional_frames =
    "unconditional_frames";

auto const frame_name   = identifier;
auto const frame_id     = integer;
auto const published_by = identifier;
auto const frame_size   = integer;

auto const unconditional_frame_def = frame_name > ':' > frame_id > ',' > published_by > ',' >
                                     frame_size > '{' > *frame_entry > '}';
auto const unconditional_frames_def = x3::lit("Frames") > '{' > *unconditional_frame > '}';

BOOST_SPIRIT_DEFINE(unconditional_frame, unconditional_frames);

}    // namespace parser

/* 9.2.4.2 Sporadic frames */

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

x3::rule< class sporadic_frame, sporadic_frame_t > const sporadic_frame    = "sporadic_frame";
x3::rule< class sporadic_frames, sporadic_frames_t > const sporadic_frames = "sporadic_frames";

auto const sporadic_frame_name = identifier;
//auto const frame_name          = identifier;

auto const sporadic_frame_def  = sporadic_frame_name > ':' > frame_name % ',' > ';';
auto const sporadic_frames_def = x3::lit("Sporadic_frames") > '{' > *sporadic_frame > '}';

BOOST_SPIRIT_DEFINE(sporadic_frame, sporadic_frames);

}    // namespace parser

/* 9.2.4.3 Event triggered frames */

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

x3::rule< class event_triggered_frame, event_triggered_frame_t > const event_triggered_frame =
    "event_triggered_frame";
x3::rule< class event_triggered_frames, event_triggered_frames_t > const event_triggered_frames =
    "event_triggered_frames";

auto const event_trig_frm_name                = identifier;
auto const collision_resolving_schedule_table = identifier;
//auto const frame_id                           = integer;
//auto const frame_name                         = identifier;

auto const event_triggered_frame_def = event_trig_frm_name > ':' >
                                       collision_resolving_schedule_table > ',' > frame_id > ',' >
                                       frame_name % ',' > ';';
auto const event_triggered_frames_def = x3::lit("Event_triggered_frames") > '{' >
                                        *event_triggered_frame > '}';

BOOST_SPIRIT_DEFINE(event_triggered_frame, event_triggered_frames);

}    // namespace parser

/* 9.2.4.4 Diagnostic frames */

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;
//using namespace unconditional_frame::parser;

x3::rule< class diagnostic_frame, diagnostic_frame_t > const diagnostic_frame = "diagnostic_frame";
x3::rule< class diagnostic_frames, diagnostic_frames_t > const diagnostic_frames =
    "diagnostic_frames";

//auto const frame_name   = identifier;
//auto const frame_id     = integer;

auto const diagnostic_frame_def  = frame_name > ':' > frame_id > '{' > *frame_entry > '}';
auto const diagnostic_frames_def = x3::lit("Diagnostic_frames") > '{' > *diagnostic_frame > '}';

BOOST_SPIRIT_DEFINE(diagnostic_frame, diagnostic_frames);

}    // namespace parser

}    // namespace lin::ldf::frame

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::frame::unconditional_frame::frame_entry_t,
    signal_name,
    signal_offset)

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::frame::unconditional_frame_t,
    frame_name,
    frame_id,
    published_by,
    frame_size,
    frame_entries)

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::frame::sporadic_frame_t, sporadic_frame_name, frame_names)

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::frame::event_triggered_frame_t,
    event_trig_frm_name,
    collision_resolving_schedule_table,
    frame_id,
    frame_names)

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::frame::diagnostic_frame_t, frame_name, frame_id, frame_entries)
