#pragma once

#include <vector>

#include <lin/lexical/common/bnf.hpp>

/* 8.2.6 Status management */

namespace lin::lexical::ncf {

struct status_t
{
    common::bnf::identifier_t response_error{};
    std::vector< common::bnf::identifier_t > fault_state_signals{};
};

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

/* 8.2.6 Status management */

x3::rule< class status_management, status_t > const status_management = "status_management";

auto const response_error_action = [](auto &ctx) { x3::_val(ctx).response_error = x3::_attr(ctx); };
auto const fault_state_signals_action = [](auto &ctx) {
    x3::_val(ctx).fault_state_signals = x3::_attr(ctx);
};

auto const status_management_def = x3::lit("status_management") > '{' >
                                   *((x3::lit("response_error") > '=' >
                                      identifier[response_error_action] > ';') |
                                     (x3::lit("fault_state_signals") > '=' >
                                      (identifier % ',')[fault_state_signals_action] > ';')) > '}';

BOOST_SPIRIT_DEFINE(status_management);

}    // namespace parser

}    // namespace lin::lexical::ncf

BOOST_FUSION_ADAPT_STRUCT(lin::lexical::ncf::status_t, response_error, fault_state_signals)
