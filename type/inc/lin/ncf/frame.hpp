#pragma once

#include <cstdint>
#include <optional>
#include <vector>

#include <lin/common/bnf.hpp>
#include <lin/ncf/signal.hpp>

/* 8.2.5 Frame definition */

namespace lin::ncf {

/* 8.2.5.1 Frame properties */

namespace frame {

enum class kind_t : std::uint8_t
{
    subscribe,
    publish,
};

using name_t                  = common::bnf::identifier_t;
using length_t                = common::bnf::integer_t;
using min_period_t            = std::optional< common::bnf::integer_t >;
using max_period_t            = std::optional< common::bnf::integer_t >;
using event_triggered_frame_t = std::optional< common::bnf::identifier_t >;

}    // namespace frame

struct frame_t
{
    frame::kind_t kind{};
    frame::name_t name{};
    frame::length_t size{};
    frame::min_period_t min_period{};
    frame::max_period_t max_period{};
    frame::event_triggered_frame_t event_triggered_frame{};
    signals_t signals{};
};

using frames_t = std::vector< frame_t >;

}    // namespace lin::ncf
