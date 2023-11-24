#pragma once

#include <boost/spirit/home/x3.hpp>

#include <lin/common/bitrate.hpp>
#include <lin/common/parser/bnf.hpp>

namespace lin::common::parser {

namespace x3 = boost::spirit::x3;

x3::rule< class bitrate_kbps, common::bitrate::kbps_t > const bitrate_kbps = "bitrate_kbps";

auto const bitrate_kbps_action = [](auto &ctx) { x3::_val(ctx) = x3::_attr(ctx); };

auto const bitrate_kbps_def = real_or_integer[bitrate_kbps_action] > "kbps";

BOOST_SPIRIT_DEFINE(bitrate_kbps)

}    // namespace lin::common::parser
