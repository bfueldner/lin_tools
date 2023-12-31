#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/ncf/diagnostic.hpp>

/* 8.2.4 Diagnostic definition */

namespace lin::ncf {

namespace diagnostic::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;

x3::rule< class nad_range, nad::range_t > const nad_range          = "nad_range";
x3::rule< class nad_sequence, nad::sequence_t > const nad_sequence = "nad_sequence";
x3::rule< class nad, nad_t > const nad                             = "nad";

auto const nad_range_def    = integer >> x3::lit("to") >> integer;
auto const nad_sequence_def = integer % ',';
auto const nad_def          = nad_range | nad_sequence;

BOOST_SPIRIT_DEFINE(nad_range, nad_sequence, nad)

}    // namespace diagnostic::parser

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;
using namespace diagnostic::parser;

/* 8.2.4 Diagnostic definition */

x3::rule< class diagnostic, diagnostic_t > const diagnostic = "diagnostic";

auto const diagnostic_nad_action   = [](auto &ctx) { x3::_val(ctx).nad = x3::_attr(ctx); };
auto const diagnostic_class_action = [](auto &ctx) {
    x3::_val(ctx).diagnostic_class = x3::_attr(ctx);
};
auto const diagnostic_p2_min_action = [](auto &ctx) { x3::_val(ctx).p2_min = x3::_attr(ctx); };
auto const diagnostic_st_min_action = [](auto &ctx) { x3::_val(ctx).st_min = x3::_attr(ctx); };
auto const diagnostic_n_as_timeout_action = [](auto &ctx) {
    x3::_val(ctx).n_as_timeout = x3::_attr(ctx);
};
auto const diagnostic_n_cr_timeout_action = [](auto &ctx) {
    x3::_val(ctx).n_cr_timeout = x3::_attr(ctx);
};
auto const diagnostic_support_sids_action = [](auto &ctx) {
    x3::_val(ctx).support_sids = x3::_attr(ctx);
};
auto const diagnostic_max_message_length_action = [](auto &ctx) {
    x3::_val(ctx).max_message_length = x3::_attr(ctx);
};

auto const diagnostic_def =
    x3::lit("diagnostic") > '{' >
    *((x3::lit("NAD") > '=' > nad[diagnostic_nad_action] > ';') |
      (x3::lit("diagnostic_class") > '=' > integer[diagnostic_class_action] > ';') |
      (x3::lit("P2_min") > '=' > real_or_integer[diagnostic_p2_min_action] > "ms" > ';') |
      (x3::lit("ST_min") > '=' > real_or_integer[diagnostic_st_min_action] > "ms" > ';') |
      (x3::lit("N_As_timeout") > '=' > real_or_integer[diagnostic_n_as_timeout_action] > "ms" >
       ';') |
      (x3::lit("N_Cr_timeout") > '=' > real_or_integer[diagnostic_n_cr_timeout_action] > "ms" >
       ';') |
      (x3::lit("support_sid") > '{' > (integer % ',')[diagnostic_support_sids_action] > '}' > ';') |
      (x3::lit("max_message_length") > '=' > integer[diagnostic_max_message_length_action] > ';')) >
    '}';

BOOST_SPIRIT_DEFINE(diagnostic)

}    // namespace parser

}    // namespace lin::ncf

BOOST_FUSION_ADAPT_STRUCT(lin::ncf::diagnostic::nad::range_t, begin, end)
