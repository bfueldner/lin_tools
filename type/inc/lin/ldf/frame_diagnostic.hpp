#pragma once

#include <vector>

#include <lin/common/bnf.hpp>

/* 9.2.4.4 Diagnostic frames */

namespace lin::ldf::frame {

namespace diagnostic {

namespace signal {

using name_t   = common::bnf::identifier_t;
using offset_t = common::bnf::integer_t;

}    // namespace signal

struct signal_t
{
    signal::name_t name{};
    signal::offset_t offset{};
};

using name_t    = common::bnf::identifier_t;
using id_t      = common::bnf::integer_t;
using signals_t = std::vector< signal_t >;

}    // namespace diagnostic

struct diagnostic_t
{
    diagnostic::name_t name{};
    diagnostic::id_t id{};
    diagnostic::signals_t signals{};
};

using diagnostics_t = std::vector< diagnostic_t >;

}    // namespace lin::ldf::frame
