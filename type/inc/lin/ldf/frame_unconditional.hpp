#pragma once

#include <vector>

#include <lin/common/bnf.hpp>

/* 9.2.4.1 Unconditional frames */

namespace lin::ldf::frame {

namespace unconditional {

namespace signal {

using name_t   = common::bnf::identifier_t;
using offset_t = common::bnf::integer_t;

}    // namespace signal

struct signal_t
{
    signal::name_t name{};
    signal::offset_t offset{};
};

using name_t         = common::bnf::identifier_t;
using id_t           = common::bnf::integer_t;
using published_by_t = common::bnf::identifier_t;
using size_t         = common::bnf::integer_t;
using signals_t      = std::vector< signal_t >;

}    // namespace unconditional

struct unconditional_t
{
    unconditional::name_t name{};
    unconditional::id_t id{};
    unconditional::published_by_t published_by{};
    unconditional::size_t size{};
    unconditional::signals_t signals{};
};

using unconditionals_t = std::vector< unconditional_t >;

}    // namespace lin::ldf::frame
