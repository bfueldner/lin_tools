#pragma once

#include <lin/ldf/validate/check.hpp>

/* 9.2.2.2 Node attributes */

namespace lin::ldf::validate::node::attribute {

class protocol_version_t:
    public common::validate::
        check_protocol_version_t< ldf::node::attribute_t, ldf::signal::standards_t >
{
  public:
    explicit protocol_version_t(common::validate::logger_t &logger):
        common::validate::check_protocol_version_t<
            ldf::node::attribute_t,
            ldf::signal::standards_t >{ logger, "lin_protocol" }
    {
    }
};

class configured_nad_t:
    public common::validate::check_int_min_max_t<
        ldf::node::attribute_t,
        &ldf::node::attribute_t::configured_nad,
        1,
        125,
        ldf::signal::standards_t >
{
  public:
    explicit configured_nad_t(common::validate::logger_t &logger):
        common::validate::check_int_min_max_t<
            ldf::node::attribute_t,
            &ldf::node::attribute_t::configured_nad,
            1,
            125,
            ldf::signal::standards_t >{ logger, "configured_nad" }
    {
    }
};

class initial_nad_t:
    public common::validate::check_optional_int_min_max_t<
        ldf::node::attribute_t,
        &ldf::node::attribute_t::initial_nad,
        1,
        125,
        ldf::signal::standards_t >
{
  public:
    explicit initial_nad_t(common::validate::logger_t &logger):
        common::validate::check_optional_int_min_max_t<
            ldf::node::attribute_t,
            &ldf::node::attribute_t::initial_nad,
            1,
            125,
            ldf::signal::standards_t >{ logger, "initial_nad" }
    {
    }
};

class product_id_t: public check::node_attribute_t
{
  public:
    static constexpr int supplier_min = 0;
    static constexpr int supplier_max = 65535;
    static constexpr int function_min = 0;
    static constexpr int function_max = 65535;
    static constexpr int variant_min  = 0;
    static constexpr int variant_max  = 255;

    explicit product_id_t(common::validate::logger_t &logger):
        check::node_attribute_t{ logger, "product_id" }
    {
    }

    void run(const ldf::signal::standards_t & /*unused*/, const ldf::node::attribute_t &attribute)
        const final;
};

class response_error_t:
    public common::validate::check_optional_name_t<
        ldf::node::attribute_t,
        &ldf::node::attribute_t::response_error,
        0,
        ldf::signal::standards_t >
{
  public:
    explicit response_error_t(common::validate::logger_t &logger):
        common::validate::check_optional_name_t<
            ldf::node::attribute_t,
            &ldf::node::attribute_t::response_error,
            0,
            ldf::signal::standards_t >{ logger, "response_error" }
    {
    }
};

class fault_state_signals_t:
    public common::validate::check_names_t<
        ldf::node::attribute_t,
        &ldf::node::attribute_t::fault_state_signals,
        0,
        true,
        ldf::signal::standards_t >
{
  public:
    explicit fault_state_signals_t(common::validate::logger_t &logger):
        common::validate::check_names_t<
            ldf::node::attribute_t,
            &ldf::node::attribute_t::fault_state_signals,
            0,
            true,
            ldf::signal::standards_t >{ logger, "fault_state_signals" }
    {
    }
};

class p2_min_t:
    public common::validate::check_optional_min_t<
        ldf::node::attribute_t,
        common::bnf::real_or_integer_t,
        &ldf::node::attribute_t::p2_min,
        0,
        ldf::signal::standards_t >
{
  public:
    explicit p2_min_t(common::validate::logger_t &logger):
        common::validate::check_optional_min_t<
            ldf::node::attribute_t,
            common::bnf::real_or_integer_t,
            &ldf::node::attribute_t::p2_min,
            0,
            ldf::signal::standards_t >{ logger, "p2_min" }
    {
    }
};

class st_min_t:
    public common::validate::check_optional_min_t<
        ldf::node::attribute_t,
        common::bnf::real_or_integer_t,
        &ldf::node::attribute_t::st_min,
        0,
        ldf::signal::standards_t >
{
  public:
    explicit st_min_t(common::validate::logger_t &logger):
        common::validate::check_optional_min_t<
            ldf::node::attribute_t,
            common::bnf::real_or_integer_t,
            &ldf::node::attribute_t::st_min,
            0,
            ldf::signal::standards_t >{ logger, "st_min" }
    {
    }
};

class n_as_timeout_t:
    public common::validate::check_optional_min_t<
        ldf::node::attribute_t,
        common::bnf::real_or_integer_t,
        &ldf::node::attribute_t::n_as_timeout,
        0,
        ldf::signal::standards_t >
{
  public:
    explicit n_as_timeout_t(common::validate::logger_t &logger):
        common::validate::check_optional_min_t<
            ldf::node::attribute_t,
            common::bnf::real_or_integer_t,
            &ldf::node::attribute_t::n_as_timeout,
            0,
            ldf::signal::standards_t >{ logger, "n_as_timeout" }
    {
    }
};

class n_cr_timeout_t:
    public common::validate::check_optional_min_t<
        ldf::node::attribute_t,
        common::bnf::real_or_integer_t,
        &ldf::node::attribute_t::n_cr_timeout,
        0,
        ldf::signal::standards_t >
{
  public:
    explicit n_cr_timeout_t(common::validate::logger_t &logger):
        common::validate::check_optional_min_t<
            ldf::node::attribute_t,
            common::bnf::real_or_integer_t,
            &ldf::node::attribute_t::n_cr_timeout,
            0,
            ldf::signal::standards_t >{ logger, "n_cr_timeout" }
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

    void run(const ldf::signal::standards_t & /*unused*/, const ldf::node::attribute_t &attribute)
        const final;
};

class configurable_frames_t: public check::node_attribute_t
{
  public:
    explicit configurable_frames_t(common::validate::logger_t &logger):
        check::node_attribute_t{ logger, "configurable_frames" }
    {
    }

    void run(const ldf::signal::standards_t & /*unused*/, const ldf::node::attribute_t &attribute)
        const final;
};

}    // namespace lin::ldf::validate::node::attribute
