#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/common/parser/signal_encoding_type.hpp>

#include <lin/ncf/signal_encoding_type.hpp>

/* 8.2.5.3 Signal encoding type definition */

namespace lin::ncf::signal_encoding_type::parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;
using namespace common::signal_encoding_type::parser;

/* 8.2.5.3 Signal encoding type definition */

x3::rule< class encoding, encoding_t > const encoding = "encoding";
x3::rule< class encoding_definition, encodings_t > const encoding_definition =
    "encoding_definition";

auto const encoding_name = identifier;

auto const encoding_def            = encoding_name > '{' > *value > '}';
auto const encoding_definition_def = x3::lit("encoding") > '{' > *encoding > '}';

BOOST_SPIRIT_DEFINE(encoding, encoding_definition);

}    // namespace lin::ncf::signal_encoding_type::parser

BOOST_FUSION_ADAPT_STRUCT(lin::ncf::signal_encoding_type::encoding_t, encoding_name, value)
