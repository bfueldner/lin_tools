#pragma once

#include <variant>
#include <vector>

#include <lin/common/bnf.hpp>

/* Common signal encoding type definition */

namespace lin::common::signal {

namespace encoding {

using name_t = common::bnf::identifier_t;

struct logical_value_t
{
    bnf::integer_t value{};
    bnf::char_string_t text_info{};
};

struct physical_range_t
{
    bnf::integer_t min{};
    bnf::integer_t max{};
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

using value_t  = std::variant< logical_value_t, physical_range_t, bcd_value_t, ascii_value_t >;
using values_t = std::vector< value_t >;

}    // namespace encoding

struct encoding_t
{
    encoding::name_t name{};
    encoding::values_t values{};
};

using encodings_t = std::vector< encoding_t >;

}    // namespace lin::common::signal
