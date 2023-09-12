#pragma once

#include <variant>
#include <vector>

#include <lin/type/common/bnf.hpp>
#include <lin/type/ncf/frame_properties.hpp>
#include <lin/type/ncf/signal.hpp>

/* 8.2.5 Frame definition */

namespace lin::type::ncf {

namespace frame {

enum class frame_kind_t
{
    publish,
    subscribe,
};

using frame_name_t = common::bnf::identifier_t;

struct single_frame_t
{
    frame_kind_t frame_kind{};
    frame_name_t frame_name{};
    frame_properties_t frame_properties{};
    signals_t signal_definition{};
};

}    // namespace frame

using frames_t = std::vector< frame::single_frame_t >;

}    // namespace lin::type::ncf
