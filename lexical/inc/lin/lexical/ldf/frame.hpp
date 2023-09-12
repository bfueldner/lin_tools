#pragma once

#include <lin/lexical/common/bnf.hpp>

/* 9.2.4 Frame definition */

namespace lin::lexical::ldf::frame {

/* 9.2.4.1 Unconditional frames */

namespace unconditional_frame {

namespace frame_entry {

using signal_name_t   = common::bnf::identifier_t;
using signal_offset_t = common::bnf::integer_t;

}    // namespace frame_entry

struct frame_entry_t
{
    frame_entry::signal_name_t signal_name{};
    frame_entry::signal_offset_t signal_offset{};
};

using frame_entries_t = std::vector< frame_entry_t >;

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

x3::rule< class frame_entry, frame_entry_t > const frame_entry = "frame_entry";

auto const signal_name   = identifier;
auto const signal_offset = integer;

auto const frame_entry_def = signal_name > ',' > signal_offset > ';';

BOOST_SPIRIT_DEFINE(frame_entry);

}    // namespace parser

using frame_name_t   = common::bnf::identifier_t;
using frame_id_t     = common::bnf::integer_t;
using published_by_t = common::bnf::identifier_t;
using frame_size_t   = common::bnf::integer_t;

}    // namespace unconditional_frame

struct unconditional_frame_t
{
    unconditional_frame::frame_name_t frame_name{};
    unconditional_frame::frame_id_t frame_id{};
    unconditional_frame::published_by_t published_by{};
    unconditional_frame::frame_size_t frame_size{};
    unconditional_frame::frame_entries_t frame_entries{};
};

using unconditional_frames_t = std::vector< unconditional_frame_t >;

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

namespace sporadic_frame {

using sporadic_frame_name_t = common::bnf::identifier_t;
using frame_name_t          = common::bnf::identifier_t;

}    // namespace sporadic_frame

struct sporadic_frame_t
{
    sporadic_frame::sporadic_frame_name_t sporadic_frame_name{};
    std::vector< sporadic_frame::frame_name_t > frame_names{};
};

using sporadic_frames_t = std::vector< sporadic_frame_t >;

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

namespace event_triggered_frame {

using event_trig_frm_name_t                = common::bnf::identifier_t;
using collision_resolving_schedule_table_t = common::bnf::identifier_t;
using frame_id_t                           = common::bnf::integer_t;
using frame_name_t                         = common::bnf::identifier_t;

}    // namespace event_triggered_frame

struct event_triggered_frame_t
{
    event_triggered_frame::event_trig_frm_name_t event_trig_frm_name{};
    event_triggered_frame::collision_resolving_schedule_table_t
        collision_resolving_schedule_table{};
    event_triggered_frame::frame_id_t frame_id{};
    std::vector< event_triggered_frame::frame_name_t > frame_names{};
};

using event_triggered_frames_t = std::vector< event_triggered_frame_t >;

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

struct diagnostic_frame_t
{
    unconditional_frame::frame_name_t frame_name{};
    unconditional_frame::frame_id_t frame_id{};
    unconditional_frame::frame_entries_t frame_entries{};
};

using diagnostic_frames_t = std::vector< diagnostic_frame_t >;

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

}    // namespace lin::lexical::ldf::frame

BOOST_FUSION_ADAPT_STRUCT(
    lin::lexical::ldf::frame::unconditional_frame::frame_entry_t,
    signal_name,
    signal_offset)

BOOST_FUSION_ADAPT_STRUCT(
    lin::lexical::ldf::frame::unconditional_frame_t,
    frame_name,
    frame_id,
    published_by,
    frame_size,
    frame_entries)

BOOST_FUSION_ADAPT_STRUCT(
    lin::lexical::ldf::frame::sporadic_frame_t,
    sporadic_frame_name,
    frame_names)

BOOST_FUSION_ADAPT_STRUCT(
    lin::lexical::ldf::frame::event_triggered_frame_t,
    event_trig_frm_name,
    collision_resolving_schedule_table,
    frame_id,
    frame_names)

BOOST_FUSION_ADAPT_STRUCT(
    lin::lexical::ldf::frame::diagnostic_frame_t,
    frame_name,
    frame_id,
    frame_entries)