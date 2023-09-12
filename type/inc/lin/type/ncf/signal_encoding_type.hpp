#pragma once

#include <vector>

#include <lin/type/common/signal_encoding_type.hpp>

/* 8.2.5.3 Signal encoding type definition */

namespace lin::type::ncf {

struct encoding_t
{
    common::bnf::identifier_t encoding_name{};
    std::vector< common::signal_encoding_type::value_t > value{};
};

using encodings_t = std::vector< encoding_t >;

}    // namespace lin::type::ncf
