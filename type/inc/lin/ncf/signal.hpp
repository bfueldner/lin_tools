#pragma once

#include <variant>
#include <vector>

#include <lin/common/bnf.hpp>
#include <lin/common/signal_encoding_type.hpp>

namespace lin::ncf {

/* 8.2.5.2 Signal definition */

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

/* 8.2.5.3 Signal encoding type definition */

namespace signal_encoding_type {

using logical_value_t  = common::signal_encoding_type::logical_value_t;
using physical_range_t = common::signal_encoding_type::physical_range_t;
using bcd_value_t      = common::signal_encoding_type::bcd_value_t;
using ascii_value_t    = common::signal_encoding_type::ascii_value_t;

struct encoding_t
{
    common::bnf::identifier_t encoding_name{};
    std::vector< common::signal_encoding_type::value_t > value{};
};

using encodings_t = std::vector< encoding_t >;

}    // namespace signal_encoding_type

}    // namespace lin::ncf
