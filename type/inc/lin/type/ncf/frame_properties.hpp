#pragma once

#include <lin/type/common/bnf.hpp>

/* 8.2.5.1 Frame properties */

namespace lin::type::ncf {

struct frame_properties_t
{
    common::bnf::integer_t length{};
    common::bnf::integer_t min_period{};
    common::bnf::integer_t max_period{};
    common::bnf::identifier_t event_triggered_frame{};
};

}    // namespace lin::type::ncf
