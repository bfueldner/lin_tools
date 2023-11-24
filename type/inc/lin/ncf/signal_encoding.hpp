#pragma once

#include <lin/common/bnf.hpp>
#include <lin/common/signal_encoding.hpp>
#include <lin/common/signal_init_value.hpp>

/* 8.2.5.3 Signal encoding type definition */

namespace lin::ncf::signal {

namespace encoding {

using name_t           = common::bnf::identifier_t;
using logical_value_t  = common::signal::encoding::logical_value_t;
using physical_range_t = common::signal::encoding::physical_range_t;
using bcd_value_t      = common::signal::encoding::bcd_value_t;
using ascii_value_t    = common::signal::encoding::ascii_value_t;
using value_t          = common::signal::encoding::value_t;
using values_t         = common::signal::encoding::values_t;

}    // namespace encoding

using encoding_t  = common::signal::encoding_t;
using encodings_t = common::signal::encodings_t;

}    // namespace lin::ncf::signal
