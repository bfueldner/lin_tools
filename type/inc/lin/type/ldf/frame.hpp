#pragma once

#include <vector>

#include <lin/type/common/bnf.hpp>

/* 9.2.4 Frame definition */

namespace lin::type::ldf::frame {

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

/* 9.2.4.4 Diagnostic frames */

struct diagnostic_frame_t
{
    unconditional_frame::frame_name_t frame_name{};
    unconditional_frame::frame_id_t frame_id{};
    unconditional_frame::frame_entries_t frame_entries{};
};

using diagnostic_frames_t = std::vector< diagnostic_frame_t >;

}    // namespace lin::type::ldf::frame
