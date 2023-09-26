#pragma once

#include <boost/spirit/home/x3.hpp>

#include <lin/common/parser/bnf.hpp>

#include <lin/ldf/global.hpp>

/* 9.2.1 Global definition */

namespace lin::ldf::global::parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

x3::rule< class lin_protocol_version, lin_protocol_version_t > const lin_protocol_version =
    "lin_protocol_version";
x3::rule< class lin_language_version, lin_language_version_t > const lin_language_version =
    "lin_language_version";
x3::rule< class lin_speed, lin_speed_t > const lin_speed          = "lin_speed";
x3::rule< class channel_name, channel_name_t > const channel_name = "channel_name";

auto const lin_protocol_version_def = x3::lit("LIN_protocol_version") > '=' > char_string > ';';
auto const lin_language_version_def = x3::lit("LIN_language_version") > '=' > char_string > ';';
auto const lin_speed_def            = x3::lit("LIN_speed") > '=' > real_or_integer > "kbps" > ';';
auto const channel_name_def         = x3::lit("Channel_name") > '=' > char_string > ';';

BOOST_SPIRIT_DEFINE(lin_protocol_version, lin_language_version, lin_speed, channel_name)

}    // namespace lin::ldf::global::parser
