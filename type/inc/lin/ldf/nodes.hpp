#pragma once

#include <vector>

#include <lin/common/bnf.hpp>

/* 9.2.2.1 Participating nodes */

namespace lin::ldf {

namespace nodes {

namespace master {

using name_t      = common::bnf::identifier_t;
using time_base_t = common::bnf::real_or_integer_t;
using jitter_t    = common::bnf::real_or_integer_t;

}    // namespace master

struct master_t
{
    master::name_t name{};
    master::time_base_t time_base{};
    master::jitter_t jitter{};
};

using slave_t  = common::bnf::identifier_t;
using slaves_t = std::vector< slave_t >;

}    // namespace nodes

struct nodes_t
{
    nodes::master_t master{};
    nodes::slaves_t slaves{};
};

}    // namespace lin::ldf
