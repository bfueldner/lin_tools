#pragma once

#include <variant>
#include <vector>

#include <boost/fusion/include/adapt_struct.hpp>
#include <boost/fusion/include/io.hpp>

#include <lin/lexical/common/bnf.hpp>

/* 8.2.5.3 Signal encoding type definition */

namespace lin::lexical::ncf {

namespace encoding {

using encoding_name_t = common::bnf::identifier_t;

struct logical_value_t
{
    int signal_value{};
    std::string text_info{};
};

struct physical_range_t
{
    int min_value{};
    int max_value{};
    double scale{};
    double offset{};
    std::string text_info{};
};

struct bcd_value_t
{
};

struct ascii_value_t
{
};

using value_t = std::variant< logical_value_t, physical_range_t, bcd_value_t, ascii_value_t >;

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

x3::rule< class logical_value, logical_value_t > const logical_value    = "logical_value";
x3::rule< class physical_range, physical_range_t > const physical_range = "physical_range";
x3::rule< class bcd_value, bcd_value_t > const bcd_value                = "bcd_value";
x3::rule< class ascii_value, ascii_value_t > const ascii_value          = "ascii_value";
x3::rule< class value, value_t > const value                            = "value";

auto const signal_value = integer;
auto const min_value    = integer;
auto const max_value    = integer;
auto const scale        = real_or_integer;
auto const offset       = real_or_integer;
auto const text_info    = char_string;

auto const logical_value_def = x3::lit("logical_value") > ',' > signal_value > -(',' > text_info) >
                               ';';
auto const physical_range_def = x3::lit("physical_value") > ',' > min_value > ',' > max_value >
                                ',' > scale > ',' > offset > -(',' > text_info) > ';';
auto const bcd_value_def   = x3::lit("bcd_value") > ';';
auto const ascii_value_def = x3::lit("ascii_value") > ';';
auto const value_def       = logical_value | physical_range | bcd_value | ascii_value;

BOOST_SPIRIT_DEFINE(logical_value, physical_range, bcd_value, ascii_value, value);

}    // namespace parser

}    // namespace encoding

struct encoding_t
{
    encoding::encoding_name_t encoding_name{};
    std::vector< encoding::value_t > value{};
};

using encodings_t = std::vector< encoding_t >;

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;
using namespace encoding::parser;

/* 8.2.5.3 Signal encoding type definition */

x3::rule< class encoding, encoding_t > const encoding = "encoding";
x3::rule< class encoding_definition, encodings_t > const encoding_definition =
    "encoding_definition";

auto const encoding_name = identifier;

auto const encoding_def            = encoding_name > '{' > *value > '}';
auto const encoding_definition_def = x3::lit("encoding") > '{' > *encoding > '}';

BOOST_SPIRIT_DEFINE(encoding, encoding_definition);

}    // namespace parser

}    // namespace lin::lexical::ncf

BOOST_FUSION_ADAPT_STRUCT(lin::lexical::ncf::encoding::logical_value_t, signal_value, text_info)
BOOST_FUSION_ADAPT_STRUCT(
    lin::lexical::ncf::encoding::physical_range_t,
    min_value,
    max_value,
    scale,
    offset,
    text_info)
BOOST_FUSION_ADAPT_STRUCT(lin::lexical::ncf::encoding_t, encoding_name, value)
