#pragma once

#include <vector>

#include <lin/ncf/global.hpp>
#include <lin/ncf/node.hpp>

/* 8.2.2 Node definition */

namespace lin::ncf {

struct node_capability_file_t
{
    global::language_version_t language_version{};
    std::vector< node_t > node{};
};

}    // namespace lin::ncf
