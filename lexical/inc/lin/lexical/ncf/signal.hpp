#pragma once

#include <variant>
#include <vector>

#include <lin/lexical/common/bnf.hpp>

/* 8.2.5.2 Signal definition */

namespace lin::lexical::ncf {

namespace signal {

using signal_name_t = common::bnf::identifier_t;

using init_value_scalar_t = common::bnf::integer_t;
using init_value_array_t  = std::vector< common::bnf::integer_t >;
using init_value_t        = std::variant< init_value_scalar_t, init_value_array_t >;

struct signal_properties_t
{
    init_value_t init_value{};
    common::bnf::integer_t size{};
    common::bnf::integer_t offset{};
    common::bnf::identifier_t encoding_name{};
};

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

x3::rule< class init_value_scalar, init_value_scalar_t > const init_value_scalar =
    "init_value_scalar";
x3::rule< class init_value_array, init_value_array_t > const init_value_array = "init_value_array";
x3::rule< class init_value, init_value_t > const init_value                   = "init_value";
x3::rule< class signal_properties, signal_properties_t > const signal_properties =
    "signal_properties";

auto const init_value_action    = [](auto &ctx) { x3::_val(ctx).init_value = x3::_attr(ctx); };
auto const size_action          = [](auto &ctx) { x3::_val(ctx).size = x3::_attr(ctx); };
auto const offset_action        = [](auto &ctx) { x3::_val(ctx).offset = x3::_attr(ctx); };
auto const encoding_name_action = [](auto &ctx) { x3::_val(ctx).encoding_name = x3::_attr(ctx); };

auto const encoding_name = identifier;

auto const init_value_scalar_def = x3::lit("init_value") >> '=' >> integer;
auto const init_value_array_def  = x3::lit("init_value") >> '=' >> '{' >> integer % ',' >> '}';
auto const init_value_def        = init_value_scalar | init_value_array;
auto const signal_properties_def = *((init_value[init_value_action] > ';') |
                                     (x3::lit("size") > '=' > integer[size_action] > ';') |
                                     (x3::lit("offset") > '=' > integer[offset_action] > ';')) >
                                   -(encoding_name[encoding_name_action] > ';');

BOOST_SPIRIT_DEFINE(init_value_scalar, init_value_array, init_value, signal_properties);

}    // namespace parser

}    // namespace signal

struct signal_t
{
    signal::signal_name_t signal_name{};
    signal::signal_properties_t signal_properties{};
};

using signals_t = std::vector< signal_t >;

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;
using namespace signal::parser;

/* 8.2.5.2 Signal definition */

x3::rule< class signal, signal_t > const signal                        = "signal";
x3::rule< class signal_definition, signals_t > const signal_definition = "signal_definition";

auto const signal_name = identifier;

auto const signal_def            = signal_name > '{' > signal_properties > '}';
auto const signal_definition_def = x3::lit("signals") > '{' > *signal > '}';

BOOST_SPIRIT_DEFINE(signal, signal_definition);

}    // namespace parser

}    // namespace lin::lexical::ncf

BOOST_FUSION_ADAPT_STRUCT(
    lin::lexical::ncf::signal::signal_properties_t,
    init_value,
    size,
    offset,
    encoding_name)
BOOST_FUSION_ADAPT_STRUCT(lin::lexical::ncf::signal_t, signal_name, signal_properties)
