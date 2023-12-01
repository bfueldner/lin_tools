#pragma once

#include <boost/spirit/home/x3.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/ldf/lin_description_file.hpp>

/* 9.2.1 Global definition */

namespace lin::ldf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::parser;

x3::rule< class protocol_version, protocol_version_t > const protocol_version =
    "lin_protocol_version";
x3::rule< class language_version, language_version_t > const language_version =
    "lin_language_version";
x3::rule< class bitrate, bitrate_t > const bitrate                = "lin_speed";
x3::rule< class channel_name, channel_name_t > const channel_name = "channel_name";

auto const protocol_version_def = x3::lit("LIN_protocol_version") > '=' > char_string > ';';
auto const language_version_def = x3::lit("LIN_language_version") > '=' > char_string > ';';
auto const bitrate_def          = x3::lit("LIN_speed") > '=' > real_or_integer > "kbps" > ';';
auto const channel_name_def     = x3::lit("Channel_name") > '=' > char_string > ';';

BOOST_SPIRIT_DEFINE(protocol_version, language_version, bitrate, channel_name)

}    // namespace lin::ldf::parser
