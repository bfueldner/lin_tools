#pragma once

#include <boost/spirit/home/x3.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/ncf/status_management.hpp>

/* 8.2.6 Status management */

namespace lin::ncf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;

/* 8.2.6 Status management */

x3::rule< class status_management, status_management_t > const status_management =
    "status_management";

auto const status_management_response_error_action = [](auto &ctx) {
    x3::_val(ctx).response_error = x3::_attr(ctx);
};
auto const status_management_fault_state_signals_action = [](auto &ctx) {
    x3::_val(ctx).fault_state_signals = x3::_attr(ctx);
};

auto const status_management_def = x3::lit("status_management") > '{' >
                                   *((x3::lit("response_error") > '=' >
                                      identifier[status_management_response_error_action] > ';') |
                                     (x3::lit("fault_state_signals") > '=' >
                                      (identifier %
                                       ',')[status_management_fault_state_signals_action] > ';')) >
                                   '}';

BOOST_SPIRIT_DEFINE(status_management)

}    // namespace lin::ncf::parser
