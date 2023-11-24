#pragma once

#include <boost/spirit/home/x3.hpp>

namespace lin::common::parser {

namespace x3 = boost::spirit::x3;

x3::rule< class comment_single_line, x3::unused_type > const comment_single_line =
    "comment_single_line";
x3::rule< class comment_block, x3::unused_type > const comment_block = "comment_block";
x3::rule< class comment, x3::unused_type > const comment             = "comment";

auto const comment_single_line_def = x3::lit("//") >> *(x3::ascii::char_ - x3::eol) >>
                                     (x3::eol | x3::eoi);
auto const comment_block_def = (x3::lit("/*") >>
                                *(comment_block | (x3::ascii::char_ - x3::lit("*/")))) >>
                               x3::lit("*/");
auto const comment_def = x3::ascii::space | comment_single_line | comment_block;

BOOST_SPIRIT_DEFINE(comment_single_line, comment_block, comment)

}    // namespace lin::common::parser
