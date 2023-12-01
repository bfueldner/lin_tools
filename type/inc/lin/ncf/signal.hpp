#pragma once

#include <vector>

#include <lin/common/bnf.hpp>
#include <lin/common/signal_encoding.hpp>
#include <lin/common/signal_init_value.hpp>

/* 8.2.5.2 Signal definition */

namespace lin::ncf {

namespace signal {

namespace init_value {

using scalar_t = common::signal::init_value::scalar_t;
using array_t  = common::signal::init_value::array_t;

}    // namespace init_value

using name_t          = common::bnf::identifier_t;
using init_value_t    = common::signal::init_value_t;
using size_t          = common::bnf::integer_t;
using offset_t        = common::bnf::integer_t;
using encoding_name_t = common::bnf::identifier_t;

}    // namespace signal

struct signal_t
{
    signal::name_t name{};
    signal::init_value_t init_value{};
    signal::size_t size{};
    signal::offset_t offset{};
    signal::encoding_name_t encoding{};
};

using signals_t = std::vector< signal_t >;

}    // namespace lin::ncf
