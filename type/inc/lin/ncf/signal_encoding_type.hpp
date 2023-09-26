#pragma once

#include <vector>

#include <lin/common/bnf.hpp>
#include <lin/common/signal_encoding_type.hpp>

/* 8.2.5.3 Signal encoding type definition */

namespace lin::ncf::signal_encoding_type {

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

}    // namespace lin::ncf::signal_encoding_type
