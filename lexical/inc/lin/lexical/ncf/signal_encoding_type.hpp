#pragma once

#include <variant>
#include <vector>

#include <lin/lexical/common/signal_encoding.hpp>

/* 8.2.5.3 Signal encoding type definition */

namespace lin::lexical::ncf {

struct encoding_t
{
    common::bnf::identifier_t encoding_name{};
    std::vector< common::signal_encoding::value_t > value{};
};

using encodings_t = std::vector< encoding_t >;

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;
using namespace common::signal_encoding::parser;

/* 8.2.5.3 Signal encoding type definition */

// NOLINTBEGIN(bugprone-forward-declaration-namespace)
x3::rule< class encoding, encoding_t > const encoding = "encoding";
x3::rule< class encoding_definition, encodings_t > const encoding_definition =
    "encoding_definition";
// NOLINTEND(bugprone-forward-declaration-namespace)

auto const encoding_name = identifier;

auto const encoding_def            = encoding_name > '{' > *value > '}';
auto const encoding_definition_def = x3::lit("encoding") > '{' > *encoding > '}';

BOOST_SPIRIT_DEFINE(encoding, encoding_definition);

}    // namespace parser

}    // namespace lin::lexical::ncf

BOOST_FUSION_ADAPT_STRUCT(lin::lexical::ncf::encoding_t, encoding_name, value)
