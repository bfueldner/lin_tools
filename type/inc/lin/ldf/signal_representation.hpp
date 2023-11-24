#pragma once

#include <vector>

#include <lin/common/bnf.hpp>
#include <lin/common/signal_encoding.hpp>
#include <lin/common/signal_init_value.hpp>

/* 9.2.6.2 Signal representation definition */

namespace lin::ldf::signal {

namespace representation {

using name_t   = common::bnf::identifier_t;
using signal_t = common::bnf::identifier_t;

}    // namespace representation

struct representation_t
{
    representation::name_t name{};
    std::vector< representation::signal_t > signals{};
};

using representations_t = std::vector< representation_t >;

}    // namespace lin::ldf::signal
