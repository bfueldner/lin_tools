#pragma once

#include <lin/ldf/validate/check.hpp>

/* 9.2.2.3 Node composition definition */

namespace lin::ldf::validate::node::composition {

class composite_names_t:
    public common::validate::check_vector_name_t<
        ldf::node::composition::configuration_t,
        ldf::node::composition::configuration::composite_t,
        &ldf::node::composition::configuration_t::composites >
{
  public:
    explicit composite_names_t(common::validate::logger_t &logger):
        common::validate::check_vector_name_t<
            ldf::node::composition::configuration_t,
            ldf::node::composition::configuration::composite_t,
            &ldf::node::composition::configuration_t::composites >{ logger, "composite_names" }
    {
    }
};

namespace configuration {

class composite_nodes_t: public check::node_composition_configuration_composite_t
{
  public:
    explicit composite_nodes_t(common::validate::logger_t &logger):
        check::node_composition_configuration_composite_t{ logger, "composite_nodes" }
    {
    }

    void run(
        const ldf::nodes_t &nodes,
        const ldf::node::composition::configuration::composite_t &composite) const final;
};

}    // namespace configuration

}    // namespace lin::ldf::validate::node::composition
