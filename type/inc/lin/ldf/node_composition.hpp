#pragma once

#include <vector>

#include <lin/common/bnf.hpp>

/* 9.2.2.3 Node composition definition */

namespace lin::ldf::node {

namespace composition {

namespace configuration {

namespace composite {

using name_t = common::bnf::identifier_t;
using node_t = common::bnf::identifier_t;

}    // namespace composite

struct composite_t
{
    composite::name_t name{};
    std::vector< composite::node_t > nodes{};
};

using name_t = common::bnf::identifier_t;

}    // namespace configuration

struct configuration_t
{
    configuration::name_t name{};
    std::vector< configuration::composite_t > composites{};
};

}    // namespace composition

using compositions_t = std::vector< composition::configuration_t >;

}    // namespace lin::ldf::node
