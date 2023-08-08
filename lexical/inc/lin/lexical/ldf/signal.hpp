#pragma once

#include <lin/lexical/common/bnf.hpp>

/* 9.2.3 Signal definition */

namespace lin::lexical::ldf::signal {

/* 9.2.3.1 Standard signals */

namespace standard_signal {

using signal_name_t       = common::bnf::identifier_t;
using signal_size_t       = common::bnf::integer_t;
using init_value_scalar_t = common::bnf::integer_t;
using init_value_array_t  = std::vector< common::bnf::integer_t >;
using init_value_t        = std::variant< init_value_scalar_t, init_value_array_t >;
using published_by_t      = common::bnf::identifier_t;
using subscribed_by_t     = common::bnf::identifier_t;

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

x3::rule< class init_value_scalar, init_value_scalar_t > const init_value_scalar =
    "init_value_scalar";
x3::rule< class init_value_array, init_value_array_t > const init_value_array = "init_value_array";
x3::rule< class init_value, init_value_t > const init_value                   = "init_value";

auto const init_value_scalar_def = integer;
auto const init_value_array_def  = '{' >> integer % ',' >> '}';
auto const init_value_def        = init_value_scalar | init_value_array;

BOOST_SPIRIT_DEFINE(init_value_scalar, init_value_array, init_value);

}    // namespace parser

}    // namespace standard_signal

struct standard_signal_t
{
    standard_signal::signal_name_t signal_name{};
    standard_signal::signal_size_t signal_size{};
    standard_signal::init_value_t init_value{};
    standard_signal::published_by_t published_by{};
    std::vector< standard_signal::subscribed_by_t > subscribed_by{};
};

using standard_signals_t = std::vector< standard_signal_t >;

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;
using namespace standard_signal::parser;

x3::rule< class standard_signal, standard_signal_t > const standard_signal    = "standard_signal";
x3::rule< class standard_signals, standard_signals_t > const standard_signals = "standard_signals";

auto const signal_name   = identifier;
auto const signal_size   = integer;
auto const published_by  = identifier;
auto const subscribed_by = identifier;

auto const standard_signal_def = signal_name > ':' > signal_size > ',' > init_value > ',' >
                                 published_by > *(',' > subscribed_by) > ';';
auto const standard_signals_def = x3::lit("Signals") > '{' > *standard_signal > '}';

BOOST_SPIRIT_DEFINE(standard_signal, standard_signals);

}    // namespace parser

/* 9.2.3.2 Diagnostic signals */

namespace diagnostic_signal {

using signal_name_t       = standard_signal::signal_name_t;
using signal_size_t       = standard_signal::signal_size_t;
using init_value_scalar_t = standard_signal::init_value_scalar_t;
using init_value_array_t  = standard_signal::init_value_array_t;
using init_value_t        = standard_signal::init_value_t;

}    // namespace diagnostic_signal

struct diagnostic_signal_t
{
    diagnostic_signal::signal_name_t signal_name{};
    diagnostic_signal::signal_size_t signal_size{};
    diagnostic_signal::init_value_t init_value{};
};

using diagnostic_signals_t = std::vector< diagnostic_signal_t >;

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

x3::rule< class diagnostic_signal, diagnostic_signal_t > const diagnostic_signal =
    "diagnostic_signal";
x3::rule< class diagnostic_signals, diagnostic_signals_t > const diagnostic_signals =
    "diagnostic_signals";

auto const diagnostic_signal_def  = signal_name > ':' > signal_size > ',' > init_value > ';';
auto const diagnostic_signals_def = x3::lit("Diagnostic_signals") > '{' > *diagnostic_signal > '}';

BOOST_SPIRIT_DEFINE(diagnostic_signal, diagnostic_signals);

}    // namespace parser

}    // namespace lin::lexical::ldf::signal

BOOST_FUSION_ADAPT_STRUCT(
    lin::lexical::ldf::signal::standard_signal_t,
    signal_name,
    signal_size,
    init_value,
    published_by,
    subscribed_by)

BOOST_FUSION_ADAPT_STRUCT(
    lin::lexical::ldf::signal::diagnostic_signal_t,
    signal_name,
    signal_size,
    init_value)
