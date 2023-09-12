#pragma once

#include <lin/lexical/common/bnf.hpp>
#include <lin/lexical/common/signal_encoding_type.hpp>

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

/* 9.2.3.3 Signal groups */

namespace signal_group {

namespace group_entry {

using signal_name_t  = common::bnf::identifier_t;
using group_offset_t = common::bnf::integer_t;

}    // namespace group_entry

struct group_entry_t
{
    group_entry::signal_name_t signal_name{};
    group_entry::group_offset_t group_offset{};
};

using group_entries_t = std::vector< group_entry_t >;

namespace parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

x3::rule< class group_entry, group_entry_t > const group_entry = "group_entry";

auto const signal_name  = identifier;
auto const group_offset = integer;

auto const group_entry_def = signal_name > ',' > group_offset > ';';

BOOST_SPIRIT_DEFINE(group_entry);

}    // namespace parser

using signal_group_name_t = common::bnf::identifier_t;
using group_size_t        = common::bnf::integer_t;

}    // namespace signal_group

struct signal_group_t
{
    signal_group::signal_group_name_t signal_group_name{};
    signal_group::group_size_t group_size{};
    signal_group::group_entries_t group_entries{};
};

using signal_groups_t = std::vector< signal_group_t >;

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

BOOST_SPIRIT_DEFINE(signal_group, signal_groups);

}    // namespace parser

/* 9.2.6.1 Signal encoding type definition */

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

/* 9.2.6.2 Signal representation definition */

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

auto const signal_representation_def  = signal_encoding_type_name > ':' > signal_name % ',' > ';';
auto const signal_representations_def = x3::lit("Signal_representation") > '{' >
                                        *signal_representation > '}';

BOOST_SPIRIT_DEFINE(signal_representation, signal_representations);

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

BOOST_FUSION_ADAPT_STRUCT(
    lin::lexical::ldf::signal::signal_group::group_entry_t,
    signal_name,
    group_offset)

BOOST_FUSION_ADAPT_STRUCT(
    lin::lexical::ldf::signal::signal_group_t,
    signal_group_name,
    group_size,
    group_entries)

BOOST_FUSION_ADAPT_STRUCT(
    lin::lexical::ldf::signal::signal_encoding_type_t,
    signal_encoding_type_name,
    values)

BOOST_FUSION_ADAPT_STRUCT(
    lin::lexical::ldf::signal::signal_representation_t,
    signal_encoding_type_name,
    signal_names)