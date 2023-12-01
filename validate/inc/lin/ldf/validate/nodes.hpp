#pragma once

#include <lin/ldf/validate/check.hpp>

/* 9.2.2 Node definition */

namespace lin::ldf::validate::nodes {

class master_time_base_t: public check::nodes_t
{
  public:
    explicit master_time_base_t(common::validate::logger_t &logger):
        check::nodes_t{ logger, "master" },
        _check_time_base{ logger, "master.time_base" }
    {
    }

    void run(const ldf::nodes_t &nodes) const final { _check_time_base.run(nodes.master); }

  private:
    using check_time_base_t = common::validate::check_min_t<
        ldf::nodes::master_t,
        ldf::nodes::master::time_base_t,
        &ldf::nodes::master_t::time_base,
        0 >;

    check_time_base_t _check_time_base;
};

class master_jitter_t: public check::nodes_t
{
  public:
    explicit master_jitter_t(common::validate::logger_t &logger):
        check::nodes_t{ logger, "master" },
        _check_jitter{ logger, "master.jitter" }
    {
    }

    void run(const ldf::nodes_t &nodes) const final { _check_jitter.run(nodes.master); }

  private:
    using check_jitter_t = common::validate::check_min_t<
        ldf::nodes::master_t,
        ldf::nodes::master::jitter_t,
        &ldf::nodes::master_t::jitter,
        0 >;

    check_jitter_t _check_jitter;
};

class node_names_t: public check::nodes_t
{
  public:
    explicit node_names_t(common::validate::logger_t &logger):
        check::nodes_t{ logger, "node_names" }
    {
    }

    void run(const ldf::nodes_t &nodes) const final;
};

}    // namespace lin::ldf::validate::nodes
