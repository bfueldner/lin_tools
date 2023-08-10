#pragma once

#include <lin/lexical/common/signal_encoding_type.hpp>

/* 9.2.6.1 Signal encoding type definition */

namespace lin::lexical::ldf {

namespace signal_encoding_type {

using signal_encoding_type_name_t = common::bnf::identifier_t;

using logical_value_t  = common::signal_encoding_type::logical_value_t;
using physical_range_t = common::signal_encoding_type::physical_range_t;
using bcd_value_t      = common::signal_encoding_type::bcd_value_t;
using ascii_value_t    = common::signal_encoding_type::ascii_value_t;

}    // namespace signal_encoding_type

struct signal_encoding_type_t
{
    signal_encoding_type::signal_encoding_type_name_t signal_encoding_type_name{};
    std::vector< common::signal_encoding_type::value_t > values{};
};

using signal_encoding_types_t = std::vector< signal_encoding_type_t >;

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;
using namespace common::signal_encoding_type::parser;

x3::rule< class signal_encoding_type, signal_encoding_type_t > const signal_encoding_type =
    "signal_encoding_type";
x3::rule< class signal_encoding_types, signal_encoding_types_t > const signal_encoding_types =
    "signal_encoding_types";

auto const signal_encoding_type_name = identifier;

auto const signal_encoding_type_def  = signal_encoding_type_name > '{' > *value > '}';
auto const signal_encoding_types_def = x3::lit("Signal_encoding_types") > '{' >
                                       *signal_encoding_type > '}';

BOOST_SPIRIT_DEFINE(signal_encoding_type, signal_encoding_types);

}    // namespace parser

}    // namespace lin::lexical::ldf

BOOST_FUSION_ADAPT_STRUCT(
    lin::lexical::ldf::signal_encoding_type_t,
    signal_encoding_type_name,
    values)
