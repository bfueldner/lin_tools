#pragma once

#include <lin/common/bnf.hpp>
#include <lin/ncf/diagnostic.hpp>
#include <lin/ncf/frame.hpp>
#include <lin/ncf/free_text.hpp>
#include <lin/ncf/general.hpp>
#include <lin/ncf/signal_encoding_type.hpp>
#include <lin/ncf/status.hpp>

/* 8.2.2 Node definition */

namespace lin::ncf {

namespace node {

using node_name_t = common::bnf::identifier_t;

}    // namespace node

struct node_t
{
    node::node_name_t node_name{};
    general_t general{};
    diagnostic_t diagnostic{};
    frames_t frames{};
    signal_encoding_type::encodings_t encodings{};
    status_t status{};
    free_text_t free_text{};
};

}    // namespace lin::ncf
