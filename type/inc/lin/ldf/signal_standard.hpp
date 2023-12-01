#pragma once

#include <vector>

#include <lin/common/bnf.hpp>
#include <lin/common/signal_init_value.hpp>

/* 9.2.3.1 Standard signals */

namespace lin::ldf::signal {

namespace standard {

namespace init_value {

using scalar_t = common::signal::init_value::scalar_t;
using array_t  = common::signal::init_value::array_t;

}    // namespace init_value

using name_t          = common::bnf::identifier_t;
using size_t          = common::bnf::integer_t;
using init_value_t    = common::signal::init_value_t;
using published_by_t  = common::bnf::identifier_t;
using subscribed_by_t = common::bnf::identifier_t;

}    // namespace standard

struct standard_t
{
    standard::name_t name{};
    standard::size_t size{};
    standard::init_value_t init_value{};
    standard::published_by_t published_by{};
    std::vector< standard::subscribed_by_t > subscribed_by{};
};

using standards_t = std::vector< standard_t >;

}    // namespace lin::ldf::signal
