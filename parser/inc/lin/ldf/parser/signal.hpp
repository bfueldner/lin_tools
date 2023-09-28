#pragma once

#include <boost/spirit/home/x3.hpp>

#include <boost/fusion/adapted/struct/adapt_struct.hpp>

#include <lin/common/parser/bnf.hpp>
#include <lin/common/parser/signal_encoding_type.hpp>

#include <lin/ldf/signal.hpp>

/* 9.2.3 Signal definition */

namespace lin::ldf::signal {

/* 9.2.3.1 Standard signals */

namespace standard_signal::parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

x3::rule< class init_value_scalar, init_value_scalar_t > const init_value_scalar =
    "init_value_scalar";
x3::rule< class init_value_array, init_value_array_t > const init_value_array = "init_value_array";
x3::rule< class init_value, init_value_t > const init_value                   = "init_value";

auto const init_value_scalar_def = integer;
auto const init_value_array_def  = '{' >> integer % ',' >> '}';
auto const init_value_def        = init_value_scalar | init_value_array;

BOOST_SPIRIT_DEFINE(init_value_scalar, init_value_array, init_value)

}    // namespace standard_signal::parser

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

BOOST_SPIRIT_DEFINE(standard_signal, standard_signals)

}    // namespace parser

/* 9.2.3.2 Diagnostic signals */

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;
//using namespace ldf::signal::parser;

x3::rule< class diagnostic_signal, diagnostic_signal_t > const diagnostic_signal =
    "diagnostic_signal";
x3::rule< class diagnostic_signals, diagnostic_signals_t > const diagnostic_signals =
    "diagnostic_signals";

auto const diagnostic_signal_def  = signal_name > ':' > signal_size > ',' > init_value > ';';
auto const diagnostic_signals_def = x3::lit("Diagnostic_signals") > '{' > *diagnostic_signal > '}';

BOOST_SPIRIT_DEFINE(diagnostic_signal, diagnostic_signals)

}    // namespace parser

/* 9.2.3.3 Signal groups */

namespace signal_group::parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

x3::rule< class group_entry, group_entry_t > const group_entry = "group_entry";

auto const signal_name  = identifier;
auto const group_offset = integer;

auto const group_entry_def = signal_name > ',' > group_offset > ';';

BOOST_SPIRIT_DEFINE(group_entry)

}    // namespace signal_group::parser

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;
using namespace signal_group::parser;

x3::rule< class signal_group, signal_group_t > const signal_group    = "signal_group";
x3::rule< class signal_groups, signal_groups_t > const signal_groups = "signal_groups";

auto const signal_group_name = identifier;
auto const group_size        = integer;

auto const signal_group_def  = signal_group_name > ':' > group_size > '{' > *group_entry > '}';
auto const signal_groups_def = x3::lit("Signal_groups") > '{' > *signal_group > '}';

BOOST_SPIRIT_DEFINE(signal_group, signal_groups)

}    // namespace parser

/* 9.2.6.1 Signal encoding type definition */

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

BOOST_SPIRIT_DEFINE(signal_encoding_type, signal_encoding_types)

}    // namespace parser

/* 9.2.6.2 Signal representation definition */

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;
using namespace common::signal_encoding_type::parser;

x3::rule< class signal_representation, signal_representation_t > const signal_representation =
    "signal_representation";
x3::rule< class signal_representations, signal_representations_t > const signal_representations =
    "signal_representations";

auto const signal_representation_def  = signal_encoding_type_name > ':' > signal_name % ',' > ';';
auto const signal_representations_def = x3::lit("Signal_representation") > '{' >
                                        *signal_representation > '}';

BOOST_SPIRIT_DEFINE(signal_representation, signal_representations)

}    // namespace parser

}    // namespace lin::ldf::signal

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::signal::standard_signal_t,
    signal_name,
    signal_size,
    init_value,
    published_by,
    subscribed_by)

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::signal::diagnostic_signal_t,
    signal_name,
    signal_size,
    init_value)

BOOST_FUSION_ADAPT_STRUCT(lin::ldf::signal::signal_group::group_entry_t, signal_name, group_offset)

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::signal::signal_group_t,
    signal_group_name,
    group_size,
    group_entries)

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::signal::signal_encoding_type_t,
    signal_encoding_type_name,
    values)

BOOST_FUSION_ADAPT_STRUCT(
    lin::ldf::signal::signal_representation_t,
    signal_encoding_type_name,
    signal_names)
