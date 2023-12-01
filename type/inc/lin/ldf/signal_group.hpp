#pragma once

#include <vector>

#include <lin/common/bnf.hpp>
#include <lin/common/signal_init_value.hpp>

/* 9.2.3.3 Signal groups */

namespace lin::ldf::signal {

namespace group {

namespace signal {

using name_t   = common::bnf::identifier_t;
using offset_t = common::bnf::integer_t;

}    // namespace signal

struct signal_t
{
    signal::name_t name{};
    signal::offset_t offset{};
};


using name_t    = common::bnf::identifier_t;
using size_t    = common::bnf::integer_t;
using signals_t = std::vector< signal_t >;

}    // namespace group

struct group_t
{
    group::name_t name{};
    group::size_t size{};
    group::signals_t signals{};
};

using groups_t = std::vector< group_t >;

}    // namespace lin::ldf::signal
