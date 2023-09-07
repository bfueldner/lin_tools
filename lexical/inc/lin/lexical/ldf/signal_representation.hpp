#pragma once

#include <lin/lexical/common/signal_encoding_type.hpp>

/* 9.2.6.2 Signal representation definition */

namespace lin::lexical::ldf {

namespace signal_representation {

using signal_encoding_type_name_t = common::bnf::identifier_t;
using signal_name_t               = common::bnf::identifier_t;

}    // namespace signal_representation

struct signal_representation_t
{
    signal_representation::signal_encoding_type_name_t signal_encoding_type_name{};
    std::vector< signal_representation::signal_name_t > signal_names{};
};

using signal_representations_t = std::vector< signal_representation_t >;

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;
using namespace common::signal_encoding_type::parser;

x3::rule< class signal_representation, signal_representation_t > const signal_representation =
    "signal_representation";
x3::rule< class signal_representations, signal_representations_t > const signal_representations =
    "signal_representations";

auto const signal_encoding_type_name = identifier;
auto const signal_name               = identifier;

auto const signal_representation_def  = signal_encoding_type_name > ':' > signal_name % ',' > ';';
auto const signal_representations_def = x3::lit("Signal_representation") > '{' >
                                        *signal_representation > '}';

BOOST_SPIRIT_DEFINE(signal_representation, signal_representations);

}    // namespace parser

}    // namespace lin::lexical::ldf

BOOST_FUSION_ADAPT_STRUCT(
    lin::lexical::ldf::signal_representation_t,
    signal_encoding_type_name,
    signal_names)
