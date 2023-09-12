#pragma once

#include <variant>

#include <lin/type/common/bnf.hpp>

/* Common signal encoding type definition */

namespace lin::type::common::signal_encoding_type {

struct logical_value_t
{
    bnf::integer_t signal_value{};
    bnf::char_string_t text_info{};
};

struct physical_range_t
{
    bnf::integer_t min_value{};
    bnf::integer_t max_value{};
    bnf::real_or_integer_t scale{};
    bnf::real_or_integer_t offset{};
    bnf::char_string_t text_info{};
};

struct bcd_value_t
{
};

struct ascii_value_t
{
};

using value_t = std::variant< logical_value_t, physical_range_t, bcd_value_t, ascii_value_t >;

}    // namespace lin::type::common::signal_encoding_type
