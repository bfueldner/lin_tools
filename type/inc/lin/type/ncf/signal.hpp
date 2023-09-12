#pragma once

#include <variant>
#include <vector>

#include <lin/type/common/bnf.hpp>

/* 8.2.5.2 Signal definition */

namespace lin::type::ncf {

namespace signal {

using signal_name_t = common::bnf::identifier_t;

using init_value_scalar_t = common::bnf::integer_t;
using init_value_array_t  = std::vector< common::bnf::integer_t >;
using init_value_t        = std::variant< init_value_scalar_t, init_value_array_t >;

struct signal_properties_t
{
    init_value_t init_value{};
    common::bnf::integer_t size{};
    common::bnf::integer_t offset{};
    common::bnf::identifier_t encoding_name{};
};

}    // namespace signal

struct signal_t
{
    signal::signal_name_t signal_name{};
    signal::signal_properties_t signal_properties{};
};

using signals_t = std::vector< signal_t >;

}    // namespace lin::type::ncf
