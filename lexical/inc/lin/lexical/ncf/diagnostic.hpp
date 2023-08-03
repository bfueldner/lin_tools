#pragma once

#include <variant>
#include <vector>

#include <lin/lexical/common/bnf.hpp>

/* 8.2.4 Diagnostic definition */

namespace lin::lexical::ncf {

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

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

x3::rule< class nad_range, nad::range_t > const nad_range          = "nad_range";
x3::rule< class nad_sequence, nad::sequence_t > const nad_sequence = "nad_sequence";
x3::rule< class nad_definition, nad_t > const nad_definition       = "nad_definition";

auto const nad_range_def      = integer >> x3::lit("to") >> integer;
auto const nad_sequence_def   = integer % ',';
auto const nad_definition_def = nad_range | nad_sequence;

BOOST_SPIRIT_DEFINE(nad_range, nad_sequence, nad_definition);

}    // namespace parser

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

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;
using namespace diagnostic::parser;

/* 8.2.4 Diagnostic definition */

x3::rule< class diagnostic_definition, diagnostic_t > const diagnostic_definition =
    "diagnostic_definition";

auto const nad_action              = [](auto &ctx) { x3::_val(ctx).nad = x3::_attr(ctx); };
auto const diagnostic_class_action = [](auto &ctx) {
    x3::_val(ctx).diagnostic_class = x3::_attr(ctx);
};
auto const p2_min_action       = [](auto &ctx) { x3::_val(ctx).p2_min = x3::_attr(ctx); };
auto const st_min_action       = [](auto &ctx) { x3::_val(ctx).st_min = x3::_attr(ctx); };
auto const n_as_timeout_action = [](auto &ctx) { x3::_val(ctx).n_as_timeout = x3::_attr(ctx); };
auto const n_cr_timeout_action = [](auto &ctx) { x3::_val(ctx).n_cr_timeout = x3::_attr(ctx); };
auto const support_sid_action  = [](auto &ctx) { x3::_val(ctx).support_sid = x3::_attr(ctx); };
auto const max_message_length_action = [](auto &ctx) {
    x3::_val(ctx).max_message_length = x3::_attr(ctx);
};

auto const diagnostic_definition_def =
    x3::lit("diagnostic") > '{' >
    *((x3::lit("NAD") > '=' > nad_definition[nad_action] > ';') |
      (x3::lit("diagnostic_class") > '=' > integer[diagnostic_class_action] > ';') |
      (x3::lit("P2_min") > '=' > real_or_integer[p2_min_action] > "ms" > ';') |
      (x3::lit("ST_min") > '=' > real_or_integer[st_min_action] > "ms" > ';') |
      (x3::lit("N_As_timeout") > '=' > real_or_integer[n_as_timeout_action] > "ms" > ';') |
      (x3::lit("N_Cr_timeout") > '=' > real_or_integer[n_cr_timeout_action] > "ms" > ';') |
      (x3::lit("support_sid") > '{' > (integer % ',')[support_sid_action] > '}' > ';') |
      (x3::lit("max_message_length") > '=' > integer[max_message_length_action] > ';')) > '}';

BOOST_SPIRIT_DEFINE(diagnostic_definition);

}    // namespace parser

}    // namespace lin::lexical::ncf

BOOST_FUSION_ADAPT_STRUCT(lin::lexical::ncf::diagnostic::nad::range_t, begin, end)
BOOST_FUSION_ADAPT_STRUCT(
    lin::lexical::ncf::diagnostic_t,
    diagnostic_class,
    p2_min,
    st_min,
    n_as_timeout,
    n_cr_timeout,
    support_sid,
    max_message_length)
