#pragma once

#include <optional>
#include <variant>
#include <vector>

#include <lin/common/bnf.hpp>

/* 8.2.4 Diagnostic definition */

namespace lin::ncf {

namespace diagnostic {

namespace nad {

using sequence_t = std::vector< common::bnf::integer_t >;

struct range_t
{
    common::bnf::integer_t begin{};
    common::bnf::integer_t end{};
};

}    // namespace nad

using nad_t = std::variant< nad::range_t, nad::sequence_t >;

}    // namespace diagnostic

struct diagnostic_t
{
    diagnostic::nad_t nad{};
    common::bnf::integer_t diagnostic_class{};
    std::optional< common::bnf::real_or_integer_t > p2_min{};
    std::optional< common::bnf::real_or_integer_t > st_min{};
    std::optional< common::bnf::real_or_integer_t > n_as_timeout{};
    std::optional< common::bnf::real_or_integer_t > n_cr_timeout{};
    std::vector< common::bnf::integer_t > support_sid{};
    std::optional< common::bnf::integer_t > max_message_length{};
};

}    // namespace lin::ncf
