#pragma once

#include <vector>

#include <lin/common/bnf.hpp>

/* 9.2.4.2 Sporadic frames */

namespace lin::ldf::frame {

namespace sporadic {

using name_t  = common::bnf::identifier_t;
using frame_t = common::bnf::identifier_t;

}    // namespace sporadic

struct sporadic_t
{
    sporadic::name_t name{};
    std::vector< sporadic::frame_t > frames{};
};

using sporadics_t = std::vector< sporadic_t >;

}    // namespace lin::ldf::frame
