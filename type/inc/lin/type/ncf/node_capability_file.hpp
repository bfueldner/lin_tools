#pragma once

#include <lin/type/common/bnf.hpp>

#include <lin/type/ncf/node.hpp>

/* 8.2.2 Node definition */

namespace lin::type::ncf {

namespace node_capability_file {

using language_version_t = common::bnf::char_string_t;

}    // namespace node_capability_file

struct node_capability_file_t
{
    node_capability_file::language_version_t language_version;
    std::vector< node_t > node;
};

}    // namespace lin::type::ncf
