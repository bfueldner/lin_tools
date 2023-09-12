#pragma once

#include <lin/lexical/common/bnf.hpp>

/* 9.2.1 Global definition */

namespace lin::lexical::ldf::global {

/* 9.2.1.1 LIN protocol version number definition */

using lin_protocol_version_t = common::bnf::char_string_t;

/* 9.2.1.2 LIN language version number definition */

using lin_language_version_t = common::bnf::char_string_t;

/* 9.2.1.3 LIN speed definition */

using lin_speed_t = common::bnf::real_or_integer_t;

/* 9.2.1.4 Channel postfix name definition */

/* NOTE: Specification says 'identifier', but this does not make sense. */
using channel_name_t = common::bnf::char_string_t;

namespace parser {

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

BOOST_SPIRIT_DEFINE(lin_protocol_version, lin_language_version, lin_speed, channel_name);

}    // namespace parser

}    // namespace lin::lexical::ldf::global
