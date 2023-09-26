#pragma once

#include <optional>
#include <vector>

#include <lin/common/bnf.hpp>

/* 9.2.2 Node definition */

namespace lin::ldf::node {

/* 9.2.2.1 Participating nodes */

namespace participating_nodes {

struct master_t
{
    common::bnf::identifier_t node_name{};
    common::bnf::real_or_integer_t time_base{};
    common::bnf::real_or_integer_t jitter{};
};

using slaves_t = std::vector< common::bnf::identifier_t >;

}    // namespace participating_nodes

struct participating_nodes_t
{
    participating_nodes::master_t master{};
    participating_nodes::slaves_t slaves{};
};

/* 9.2.2.2 Node attributes */

namespace node_attribute {

using protocol_version_t = common::bnf::char_string_t;
using diag_address_t     = common::bnf::integer_t;

using lin_protocol_t   = protocol_version_t;
using configured_nad_t = diag_address_t;
using initial_nad_t    = diag_address_t;

using supplier_id_t = common::bnf::integer_t;
using function_id_t = common::bnf::integer_t;
using variant_t     = common::bnf::integer_t;
using signal_name_t = common::bnf::identifier_t;

struct product_id_t
{
    supplier_id_t supplier_id{};
    function_id_t function_id{};
    std::optional< variant_t > variant{};
};

using response_error_t      = signal_name_t;
using fault_state_signals_t = std::vector< signal_name_t >;
using p2_min_t              = common::bnf::real_or_integer_t;
using st_min_t              = common::bnf::real_or_integer_t;
using n_as_timeout_t        = common::bnf::real_or_integer_t;
using n_cr_timeout_t        = common::bnf::real_or_integer_t;

using frame_name_t = common::bnf::identifier_t;
using message_id_t = common::bnf::integer_t;

struct configurable_frame_t
{
    frame_name_t frame_name{};
    std::optional< message_id_t > message_id{};
};
using configurable_frames_t = std::vector< configurable_frame_t >;

}    // namespace node_attribute

struct node_attribute_t
{
    common::bnf::identifier_t node_name{};
    node_attribute::lin_protocol_t lin_protocol{};
    node_attribute::configured_nad_t configured_nad{};
    std::optional< node_attribute::initial_nad_t > initial_nad{};
    std::optional< node_attribute::product_id_t > product_id{};
    std::optional< node_attribute::response_error_t > response_error{};
    node_attribute::fault_state_signals_t fault_state_signals{};
    std::optional< node_attribute::p2_min_t > p2_min{};
    std::optional< node_attribute::st_min_t > st_min{};
    std::optional< node_attribute::n_as_timeout_t > n_as_timeout{};
    std::optional< node_attribute::n_cr_timeout_t > n_cr_timeout{};
    node_attribute::configurable_frames_t configurable_frames{};
};

using node_attributes_t = std::vector< node_attribute_t >;

/* 9.2.2.3 Node composition definition */

namespace node_composition {

using configuration_name_t = common::bnf::identifier_t;
using composite_node_t     = common::bnf::identifier_t;
using logical_node_t       = common::bnf::identifier_t;

struct composition_t
{
    composite_node_t composite_node{};
    std::vector< logical_node_t > logical_node{};
};

struct configuration_t
{
    configuration_name_t configuration_name{};
    std::vector< composition_t > composite_node{};
};

}    // namespace node_composition

using node_composition_t = std::vector< node_composition::configuration_t >;

}    // namespace lin::ldf::node
