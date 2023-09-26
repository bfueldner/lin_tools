#pragma once

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
    common::bnf::integer_t diagnostic_class{ 1 };
    common::bnf::real_or_integer_t p2_min{ 50.0 };
    common::bnf::real_or_integer_t st_min{ 0.0 };
    common::bnf::real_or_integer_t n_as_timeout{ 1000.0 };
    common::bnf::real_or_integer_t n_cr_timeout{ 1000.0 };
    std::vector< common::bnf::integer_t > support_sid{ 0xB2, 0xB7 };
    common::bnf::integer_t max_message_length{ 4095 };
};

}    // namespace lin::ncf
