#pragma once

#include <boost/spirit/home/x3.hpp>

namespace lin::common::comment::parser {

namespace x3 = boost::spirit::x3;

x3::rule< class single_line_comment, x3::unused_type > const single_line_comment =
    "single_line_comment";
x3::rule< class block_comment, x3::unused_type > const block_comment = "block_comment";
x3::rule< class comment, x3::unused_type > const comment             = "comment";

auto const single_line_comment_def = x3::lit("//") >> *(x3::ascii::char_ - x3::eol) >>
                                     (x3::eol | x3::eoi);
auto const block_comment_def = (x3::lit("/*") >>
                                *(block_comment | (x3::ascii::char_ - x3::lit("*/")))) >>
                               x3::lit("*/");
auto const comment_def = x3::ascii::space | single_line_comment | block_comment;

BOOST_SPIRIT_DEFINE(single_line_comment, block_comment, comment)

}    // namespace lin::common::comment::parser
