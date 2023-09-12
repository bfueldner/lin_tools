#pragma once

#include <lin/type/ncf/diagnostic.hpp>
#include <lin/type/ncf/frame.hpp>
#include <lin/type/ncf/free_text.hpp>
#include <lin/type/ncf/general.hpp>
#include <lin/type/ncf/signal_encoding_type.hpp>
#include <lin/type/ncf/status.hpp>

/* 8.2.2 Node definition */

namespace lin::type::ncf {

namespace node {

using node_name_t = common::bnf::identifier_t;

}    // namespace node

struct node_t
{
    node::node_name_t node_name{};
    general_t general{};
    diagnostic_t diagnostic{};
    frames_t frames{};
    encodings_t encodings{};
    status_t status{};
    free_text_t free_text{};
};

}    // namespace lin::type::ncf
