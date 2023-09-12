#pragma once

#include <variant>
#include <vector>

#include <lin/type/common/bnf.hpp>

/* 8.2.4 Diagnostic definition */

namespace lin::type::ncf {

namespace diagnostic {

namespace nad {

using sequence_t = std::vector< int >;

struct range_t
{
    int begin{};
    int end{};
};

}    // namespace nad

using nad_t = std::variant< nad::range_t, nad::sequence_t >;

}    // namespace diagnostic

struct diagnostic_t
{
    diagnostic::nad_t nad{};
    int diagnostic_class{ 1 };
    double p2_min{ 50.0 };
    double st_min{ 0.0 };
    double n_as_timeout{ 1000.0 };
    double n_cr_timeout{ 1000.0 };
    std::vector< int > support_sid{ 0xB2, 0xB7 };
    int max_message_length{ 4095 };
};

}    // namespace lin::type::ncf
