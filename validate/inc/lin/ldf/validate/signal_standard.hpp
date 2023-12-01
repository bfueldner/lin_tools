#pragma once

#include <lin/ldf/validate/check.hpp>

/* 9.2.3.1 Standard signals */

namespace lin::ldf::validate::signal::standard {

class size_t: public check::standard_signal_t
{
  public:
    static constexpr int min = 1;
    static constexpr int max = 64;

    explicit size_t(common::validate::logger_t &logger):
        check::standard_signal_t{ logger, "size" }
    {
    }

    void run(const ldf::nodes_t & /*unused*/, const ldf::signal::standard_t &signal) const final;
};

class init_value_t: public check::standard_signal_t
{
  public:
    explicit init_value_t(common::validate::logger_t &logger):
        check::standard_signal_t{ logger, "init_value" }
    {
    }

    void run(const ldf::nodes_t & /*unused*/, const ldf::signal::standard_t &signal) const final;
};

class published_by_t:
    public check_node_name_t<
        ldf::signal::standard_t,
        &ldf::signal::standard_t::published_by,
        ldf::nodes_t >
{
  public:
    explicit published_by_t(common::validate::logger_t &logger):
        check_node_name_t<
            ldf::signal::standard_t,
            &ldf::signal::standard_t::published_by,
            ldf::nodes_t >{ logger, "published_by" }
    {
    }
};

class subscribed_by_t:
    public check_node_names_t<
        ldf::signal::standard_t,
        &ldf::signal::standard_t::subscribed_by,
        ldf::nodes_t >
{
  public:
    explicit subscribed_by_t(common::validate::logger_t &logger):
        check_node_names_t<
            ldf::signal::standard_t,
            &ldf::signal::standard_t::subscribed_by,
            ldf::nodes_t >{ logger, "subscribed_by" }
    {
    }
};

}    // namespace lin::ldf::validate::signal::standard
