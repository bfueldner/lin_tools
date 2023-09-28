#pragma once

#include <lin/common/parser/bnf.hpp>

#include <lin/ncf/free_text.hpp>

/* 8.2.7 Free text definition */

namespace lin::ncf::parser {

namespace x3 = boost::spirit::x3;

using namespace common::bnf::parser;

x3::rule< class free_text_definition, free_text_t > const free_text_definition =
    "free_text_definition";

auto const free_text_action = [](auto &ctx) { x3::_val(ctx).value = x3::_attr(ctx); };

auto const free_text_definition_def = x3::lit("free_text") > '{' > char_string[free_text_action] >
                                      '}';

BOOST_SPIRIT_DEFINE(free_text_definition)

}    // namespace lin::ncf::parser
