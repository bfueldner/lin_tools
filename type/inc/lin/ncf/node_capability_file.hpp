#pragma once

#include <lin/ncf/node.hpp>

/* 8.2 Node capability file definition */

namespace lin::ncf {

/* 8.2.1 Global definition */

/* 8.2.1.1 Node capability language version number definition */

using language_version_t = common::bnf::char_string_t;

struct node_capability_file_t
{
    language_version_t language_version{};
    nodes_t nodes{};
};

}    // namespace lin::ncf
