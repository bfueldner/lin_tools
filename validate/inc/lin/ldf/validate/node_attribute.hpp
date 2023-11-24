#pragma once

#include <lin/ldf/validate/check.hpp>

/* 9.2.2.2 Node attributes */

namespace lin::ldf::validate::node::attribute {

class protocol_version_t:
    public common::validate::check_protocol_version_t< ldf::node::attribute_t >
{
  public:
    explicit protocol_version_t(common::validate::logger_t &logger):
        common::validate::check_protocol_version_t< ldf::node::attribute_t >{ logger,
                                                                              "lin_protocol" }
    {
    }
};

class configured_nad_t:
    public common::validate::check_int_min_max_t<
        ldf::node::attribute_t,
        &ldf::node::attribute_t::configured_nad,
        1,
        125 >
{
  public:
    explicit configured_nad_t(common::validate::logger_t &logger):
        common::validate::check_int_min_max_t<
            ldf::node::attribute_t,
            &ldf::node::attribute_t::configured_nad,
            1,
            125 >{ logger, "configured_nad" }
    {
    }
};

class initial_nad_t:
    public common::validate::check_optional_int_min_max_t<
        ldf::node::attribute_t,
        &ldf::node::attribute_t::initial_nad,
        1,
        125 >
{
  public:
    explicit initial_nad_t(common::validate::logger_t &logger):
        common::validate::check_optional_int_min_max_t<
            ldf::node::attribute_t,
            &ldf::node::attribute_t::initial_nad,
            1,
            125 >{ logger, "initial_nad" }
    {
    }
};

class attributes_t: public check::node_attribute_t
{
  public:
    explicit attributes_t(common::validate::logger_t &logger):
        check::node_attribute_t{ logger, "attributes" }
    {
    }

    void run(const ldf::node::attribute_t &attribute) const final;
};


class configurable_frames_t: public check::node_attribute_t
{
  public:
    explicit configurable_frames_t(common::validate::logger_t &logger):
        check::node_attribute_t{ logger, "configurable_frames" }
    {
    }

    void run(const ldf::node::attribute_t &attribute) const final;
};

}    // namespace lin::ldf::validate::node::attribute
