#pragma once

#include <vector>

#include <lin/common/bnf.hpp>

/* 9.2.4.3 Event triggered frames */

namespace lin::ldf::frame {

namespace event_triggered {

using name_t           = common::bnf::identifier_t;
using schedule_table_t = common::bnf::identifier_t;
using id_t             = common::bnf::integer_t;
using frame_t          = common::bnf::identifier_t;

}    // namespace event_triggered

struct event_triggered_t
{
    event_triggered::name_t name{};
    event_triggered::schedule_table_t schedule_table{};
    event_triggered::id_t id{};
    std::vector< event_triggered::frame_t > frames{};
};

using event_triggereds_t = std::vector< event_triggered_t >;

}    // namespace lin::ldf::frame
