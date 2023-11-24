#pragma once

#include <optional>
#include <vector>

#include <lin/common/bnf.hpp>

/* 9.2.2.2 Node attributes */

namespace lin::ldf::node {

namespace attribute {

using name_t = common::bnf::identifier_t;

using protocol_version_t = common::bnf::char_string_t;
using diag_address_t     = common::bnf::integer_t;
using configured_nad_t   = diag_address_t;
using initial_nad_t      = diag_address_t;

using supplier_t    = common::bnf::integer_t;
using function_t    = common::bnf::integer_t;
using variant_t     = common::bnf::integer_t;
using signal_name_t = common::bnf::identifier_t;

struct product_id_t
{
    supplier_t supplier{};
    function_t function{};
    std::optional< variant_t > variant{};
};

using response_error_t      = signal_name_t;
using fault_state_signals_t = std::vector< signal_name_t >;
using p2_min_t              = common::bnf::real_or_integer_t;
using st_min_t              = common::bnf::real_or_integer_t;
using n_as_timeout_t        = common::bnf::real_or_integer_t;
using n_cr_timeout_t        = common::bnf::real_or_integer_t;

namespace configurable_frame {

using name_t = common::bnf::identifier_t;
using id_t   = common::bnf::integer_t;

}    // namespace configurable_frame

struct configurable_frame_t
{
    configurable_frame::name_t name{};
    std::optional< id_t > id{};
};
using configurable_frames_t = std::vector< configurable_frame_t >;

}    // namespace attribute

struct attribute_t
{
    attribute::name_t name{};
    attribute::protocol_version_t protocol_version{};
    attribute::configured_nad_t configured_nad{};
    std::optional< attribute::initial_nad_t > initial_nad{};
    std::optional< attribute::product_id_t > product_id{};
    std::optional< attribute::response_error_t > response_error{};
    attribute::fault_state_signals_t fault_state_signals{};
    std::optional< attribute::p2_min_t > p2_min{};
    std::optional< attribute::st_min_t > st_min{};
    std::optional< attribute::n_as_timeout_t > n_as_timeout{};
    std::optional< attribute::n_cr_timeout_t > n_cr_timeout{};
    attribute::configurable_frames_t configurable_frames{};
};

using attributes_t = std::vector< attribute_t >;

}    // namespace lin::ldf::node
