#pragma once

#include <lin/common/bnf.hpp>

/* 8.2.7 Free text definition */

namespace lin::ncf {

struct free_text_t
{
    common::bnf::char_string_t value;
};

}    // namespace lin::ncf
