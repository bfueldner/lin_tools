#pragma once

#include <variant>
#include <vector>

#include <lin/common/bnf.hpp>
#include <lin/common/signal_encoding_type.hpp>

/* 9.2.3 Signal definition */

namespace lin::ldf::signal {

/* 9.2.3.1 Standard signals */

namespace standard_signal {

using signal_name_t       = common::bnf::identifier_t;
using signal_size_t       = common::bnf::integer_t;
using init_value_scalar_t = common::bnf::integer_t;
using init_value_array_t  = std::vector< common::bnf::integer_t >;
using init_value_t        = std::variant< init_value_scalar_t, init_value_array_t >;
using published_by_t      = common::bnf::identifier_t;
using subscribed_by_t     = common::bnf::identifier_t;

}    // namespace standard_signal

struct standard_signal_t
{
    standard_signal::signal_name_t signal_name{};
    standard_signal::signal_size_t signal_size{};
    standard_signal::init_value_t init_value{};
    standard_signal::published_by_t published_by{};
    std::vector< standard_signal::subscribed_by_t > subscribed_by{};
};

using standard_signals_t = std::vector< standard_signal_t >;

/* 9.2.3.2 Diagnostic signals */

namespace diagnostic_signal {

using signal_name_t       = standard_signal::signal_name_t;
using signal_size_t       = standard_signal::signal_size_t;
using init_value_scalar_t = standard_signal::init_value_scalar_t;
using init_value_array_t  = standard_signal::init_value_array_t;
using init_value_t        = standard_signal::init_value_t;

}    // namespace diagnostic_signal

struct diagnostic_signal_t
{
    diagnostic_signal::signal_name_t signal_name{};
    diagnostic_signal::signal_size_t signal_size{};
    diagnostic_signal::init_value_t init_value{};
};

using diagnostic_signals_t = std::vector< diagnostic_signal_t >;

/* 9.2.3.3 Signal groups */

namespace signal_group {

namespace group_entry {

using signal_name_t  = common::bnf::identifier_t;
using group_offset_t = common::bnf::integer_t;

}    // namespace group_entry

struct group_entry_t
{
    group_entry::signal_name_t signal_name{};
    group_entry::group_offset_t group_offset{};
};

using group_entries_t = std::vector< group_entry_t >;

using signal_group_name_t = common::bnf::identifier_t;
using group_size_t        = common::bnf::integer_t;

}    // namespace signal_group

struct signal_group_t
{
    signal_group::signal_group_name_t signal_group_name{};
    signal_group::group_size_t group_size{};
    signal_group::group_entries_t group_entries{};
};

using signal_groups_t = std::vector< signal_group_t >;

/* 9.2.6.1 Signal encoding type definition */

namespace signal_encoding_type {

using signal_encoding_type_name_t = common::bnf::identifier_t;

using logical_value_t  = common::signal_encoding_type::logical_value_t;
using physical_range_t = common::signal_encoding_type::physical_range_t;
using bcd_value_t      = common::signal_encoding_type::bcd_value_t;
using ascii_value_t    = common::signal_encoding_type::ascii_value_t;

}    // namespace signal_encoding_type

struct signal_encoding_type_t
{
    signal_encoding_type::signal_encoding_type_name_t signal_encoding_type_name{};
    std::vector< common::signal_encoding_type::value_t > values{};
};

using signal_encoding_types_t = std::vector< signal_encoding_type_t >;

/* 9.2.6.2 Signal representation definition */

namespace signal_representation {

using signal_encoding_type_name_t = common::bnf::identifier_t;
using signal_name_t               = common::bnf::identifier_t;

}    // namespace signal_representation

struct signal_representation_t
{
    signal_representation::signal_encoding_type_name_t signal_encoding_type_name{};
    std::vector< signal_representation::signal_name_t > signal_names{};
};

using signal_representations_t = std::vector< signal_representation_t >;

}    // namespace lin::ldf::signal
