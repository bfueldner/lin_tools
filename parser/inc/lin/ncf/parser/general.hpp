#pragma once

#include <boost/spirit/home/x3.hpp>

#include <lin/common/parser/bnf.hpp>

#include <lin/ncf/general.hpp>

/* 8.2.3 General definition */

namespace lin::ncf {

namespace general::parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

/* 8.2.3.1 LIN protocol version number definition */

auto const protocol_version = char_string;

/* 8.2.3.2 LIN Product Identification */

auto const supplier_id = integer;
auto const function_id = integer;
auto const variant_id  = integer;

/* 8.2.3.3 Bit rate */

x3::rule< class bitrate, bitrate_t > const bitrate = "bitrate";
x3::rule< class bitrate_definition_automatic, bitrate_definition::automatic_t > const
    bitrate_definition_automatic = "bitrate_definition_automatic";
x3::rule< class bitrate_definition_select, bitrate_definition::select_t > const
    bitrate_definition_select = "bitrate_definition_select";
x3::rule< class bitrate_definition_fixed, bitrate_definition::fixed_t > const
    bitrate_definition_fixed = "bitrate_definition_fixed";
x3::rule< class bitrate_definition, bitrate_definition_t > const bitrate_definition =
    "bitrate_definition";

auto const bitrate_automatic_min_action = [](auto &ctx) { x3::_val(ctx).min = x3::_attr(ctx); };
auto const bitrate_automatic_max_action = [](auto &ctx) { x3::_val(ctx).max = x3::_attr(ctx); };

auto const bitrate_def = real_or_integer > "kbps";
auto const bitrate_definition_automatic_def =
    x3::lit("automatic") > -(x3::lit("min") > bitrate)[bitrate_automatic_min_action] >
    -(x3::lit("max") > bitrate)[bitrate_automatic_max_action];
auto const bitrate_definition_select_def = x3::lit("select") > '{' > bitrate % ',' > '}';
auto const bitrate_definition_fixed_def  = bitrate;
auto const bitrate_definition_def = bitrate_definition_automatic | bitrate_definition_select |
                                    bitrate_definition_fixed;

BOOST_SPIRIT_DEFINE(
    bitrate,
    bitrate_definition_automatic,
    bitrate_definition_select,
    bitrate_definition_fixed,
    bitrate_definition);

/* 8.2.3.4 Sends wake up signal */

x3::rule< class sends_wake_up_signal, sends_wake_up_signal_t > const sends_wake_up_signal =
    "sends_wake_up_signal";

auto const sends_wake_up_signal_def = '"' > ((x3::lit("no") > x3::attr(false)) |
                                             (x3::lit("yes") > x3::attr(true))) > '"';

BOOST_SPIRIT_DEFINE(sends_wake_up_signal);

}    // namespace general::parser

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace general::parser;

/* 8.2.3 General definition */

x3::rule< class general_definition, general_t > const general_definition = "general_definition";

auto const protocol_version_action = [](auto &ctx) {
    x3::_val(ctx).protocol_version = x3::_attr(ctx);
};
auto const supplier_id_action = [](auto &ctx) { x3::_val(ctx).supplier_id = x3::_attr(ctx); };
auto const function_id_action = [](auto &ctx) { x3::_val(ctx).function_id = x3::_attr(ctx); };
auto const variant_id_action  = [](auto &ctx) { x3::_val(ctx).variant_id = x3::_attr(ctx); };
auto const bitrate_definition_action = [](auto &ctx) {
    x3::_val(ctx).bitrate_definition = x3::_attr(ctx);
};
auto const sends_wake_up_signal_action = [](auto &ctx) {
    x3::_val(ctx).sends_wake_up_signal = x3::_attr(ctx);
};

auto const general_definition_def =
    x3::lit("general") > '{' >
    *((x3::lit("LIN_protocol_version") > '=' > protocol_version[protocol_version_action] > ';') |
      (x3::lit("supplier") > '=' > supplier_id[supplier_id_action] > ';') |
      (x3::lit("function") > '=' > function_id[function_id_action] > ';') |
      (x3::lit("variant") > '=' > variant_id[variant_id_action] > ';') |
      (x3::lit("bitrate") > '=' > bitrate_definition[bitrate_definition_action] > ';') |
      (x3::lit("sends_wake_up_signal") > '=' > sends_wake_up_signal[sends_wake_up_signal_action] >
       ';')) > '}';

BOOST_SPIRIT_DEFINE(general_definition);

}    // namespace parser

}    // namespace lin::ncf
