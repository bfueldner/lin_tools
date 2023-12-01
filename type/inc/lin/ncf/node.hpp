#pragma once

#include <vector>

#include <lin/common/bnf.hpp>
#include <lin/ncf/diagnostic.hpp>
#include <lin/ncf/frame.hpp>
#include <lin/ncf/free_text.hpp>
#include <lin/ncf/general.hpp>
#include <lin/ncf/signal_encoding.hpp>
#include <lin/ncf/status_management.hpp>

/* 8.2.2 Node definition */

namespace lin::ncf {

namespace node {

using name_t = common::bnf::identifier_t;

}    // namespace node

struct node_t
{
    node::name_t name{};
    general_t general{};
    diagnostic_t diagnostic{};
    frames_t frames{};
    signal::encodings_t signal_encodings{};
    status_management_t status_management{};
    free_text_t free_text{};
};
using nodes_t = std::vector< node_t >;

}    // namespace lin::ncf
