#pragma once

#include <boost/spirit/home/x3.hpp>

#include <lin/common/parser/bitrate.hpp>
#include <lin/common/parser/bnf.hpp>
#include <lin/ncf/general.hpp>

/* 8.2.3 General definition */

namespace lin::ncf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;

/* 8.2.3.1 LIN protocol version number definition */

auto const general_protocol_version = char_string;

/* 8.2.3.2 LIN Product Identification */

auto const general_supplier_id = integer;
auto const general_function_id = integer;
auto const general_variant_id  = integer;

/* 8.2.3.3 Bit rate */

x3::rule< class general_bitrate_automatic, general::bitrate::automatic_t > const
    general_bitrate_automatic = "bitrate_automatic";
x3::rule< class general_bitrate_select, general::bitrate::select_t > const general_bitrate_select =
    "general_bitrate_select";
x3::rule< class general_bitrate_fixed, general::bitrate::fixed_t > const general_bitrate_fixed =
    "general_bitrate_fixed";
x3::rule< class general_bitrate, general::bitrate_t > const general_bitrate = "general_bitrate";

auto const general_bitrate_automatic_min_action = [](auto &ctx) {
    x3::_val(ctx).min = x3::_attr(ctx);
};
auto const general_bitrate_automatic_max_action = [](auto &ctx) {
    x3::_val(ctx).max = x3::_attr(ctx);
};

auto const general_bitrate_automatic_def =
    x3::lit("automatic") > -(x3::lit("min") > bitrate_kbps)[general_bitrate_automatic_min_action] >
    -(x3::lit("max") > bitrate_kbps)[general_bitrate_automatic_max_action];
auto const general_bitrate_select_def = x3::lit("select") > '{' > bitrate_kbps % ',' > '}';
auto const general_bitrate_fixed_def  = bitrate_kbps;
auto const general_bitrate_def        = general_bitrate_automatic | general_bitrate_select |
                                 general_bitrate_fixed;

BOOST_SPIRIT_DEFINE(
    general_bitrate_automatic,
    general_bitrate_select,
    general_bitrate_fixed,
    general_bitrate)

/* 8.2.3.4 Sends wake up signal */

x3::rule< class general_sends_wake_up_signal, general::sends_wake_up_signal_t > const
    general_sends_wake_up_signal = "general_sends_wake_up_signal";

auto const general_sends_wake_up_signal_def = '"' > ((x3::lit("no") > x3::attr(false)) |
                                                     (x3::lit("yes") > x3::attr(true))) > '"';

BOOST_SPIRIT_DEFINE(general_sends_wake_up_signal)

/* 8.2.3 General definition */

x3::rule< class general, general_t > const general = "general";

auto const general_protocol_version_action = [](auto &ctx) {
    x3::_val(ctx).protocol_version = x3::_attr(ctx);
};
auto const general_supplier_action = [](auto &ctx) { x3::_val(ctx).supplier = x3::_attr(ctx); };
auto const general_function_action = [](auto &ctx) { x3::_val(ctx).function = x3::_attr(ctx); };
auto const general_variant_action  = [](auto &ctx) { x3::_val(ctx).variant = x3::_attr(ctx); };
auto const general_bitrate_action  = [](auto &ctx) { x3::_val(ctx).bitrate = x3::_attr(ctx); };
auto const general_sends_wake_up_signal_action = [](auto &ctx) {
    x3::_val(ctx).sends_wake_up_signal = x3::_attr(ctx);
};

auto const general_def =
    x3::lit("general") > '{' >
    *((x3::lit("LIN_protocol_version") > '=' >
       general_protocol_version[general_protocol_version_action] > ';') |
      (x3::lit("supplier") > '=' > general_supplier_id[general_supplier_action] > ';') |
      (x3::lit("function") > '=' > general_function_id[general_function_action] > ';') |
      (x3::lit("variant") > '=' > general_variant_id[general_variant_action] > ';') |
      (x3::lit("bitrate") > '=' > general_bitrate[general_bitrate_action] > ';') |
      (x3::lit("sends_wake_up_signal") > '=' >
       general_sends_wake_up_signal[general_sends_wake_up_signal_action] > ';')) > '}';

BOOST_SPIRIT_DEFINE(general)

}    // namespace lin::ncf::parser
