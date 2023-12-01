#pragma once

#include <lin/ncf/validate/check.hpp>

/* 8.2.4 Diagnostic definition */

namespace lin::ncf::validate::diagnostic {

template <
    auto ncf::diagnostic_t::*member_,
    common::bnf::integer_t min_,
    common::bnf::integer_t max_ >
using check_diagnostic_int_min_max_t =
    common::validate::check_int_min_max_t< ncf::diagnostic_t, member_, min_, max_ >;

template <
    auto ncf::diagnostic_t::*member_,
    common::bnf::integer_t min_,
    common::bnf::integer_t max_ >
using check_diagnostic_int_vector_t =
    common::validate::check_int_vector_t< ncf::diagnostic_t, member_, min_, max_ >;

template < auto ncf::diagnostic_t::*member_, common::bnf::integer_t min_ >
using check_diagnostic_optional_int_min_t =
    common::validate::check_optional_int_min_t< ncf::diagnostic_t, member_, min_ >;

template < auto ncf::diagnostic_t::*member_, common::bnf::integer_t min_ >
using check_diagnostic_optional_double_min_t =
    common::validate::check_optional_double_min_t< ncf::diagnostic_t, member_, min_ >;

class nad_t: public check::diagnostic_t
{
  public:
    static constexpr int min = 1;
    static constexpr int max = 125;

    explicit nad_t(common::validate::logger_t &logger):
        check::diagnostic_t{ logger, "nad" },
        _range{ _to_string(min) + ".." + _to_string(max) },
        _nad_sequence_check{ logger, "nad" }
    {
    }

    void run(const ncf::diagnostic_t &diagnostic) const final;
    void run(const ncf::diagnostic::nad::range_t &nad_range) const;
    void run(const ncf::diagnostic::nad::sequence_t &nad_sequence) const;

  private:
    std::string _range;
    ncf::diagnostic::nad::sequence_t _sequence;

    using check_nad_sequence_t =
        common::validate::check_int_vector_t< nad_t, &nad_t::_sequence, min, max >;

    check_nad_sequence_t _nad_sequence_check;
};

class diagnostic_class_t:
    public check_diagnostic_int_min_max_t< &ncf::diagnostic_t::diagnostic_class, 1, 3 >
{
  public:
    explicit diagnostic_class_t(common::validate::logger_t &logger):
        check_diagnostic_int_min_max_t< &ncf::diagnostic_t::diagnostic_class, 1, 3 >{
            logger,
            "diagnostic_class"
        }
    {
    }
};

class p2_min_t: public check_diagnostic_optional_double_min_t< &ncf::diagnostic_t::p2_min, 0 >
{
  public:
    explicit p2_min_t(common::validate::logger_t &logger):
        check_diagnostic_optional_double_min_t< &ncf::diagnostic_t::p2_min, 0 >(logger, "p2_min")
    {
    }
};

class st_min_t: public check_diagnostic_optional_double_min_t< &ncf::diagnostic_t::st_min, 0 >
{
  public:
    explicit st_min_t(common::validate::logger_t &logger):
        check_diagnostic_optional_double_min_t< &ncf::diagnostic_t::st_min, 0 >(logger, "st_min")
    {
    }
};

class n_as_timeout_t:
    public check_diagnostic_optional_double_min_t< &ncf::diagnostic_t::n_as_timeout, 0 >
{
  public:
    explicit n_as_timeout_t(common::validate::logger_t &logger):
        check_diagnostic_optional_double_min_t< &ncf::diagnostic_t::n_as_timeout, 0 >{
            logger,
            "n_as_timeout"
        }
    {
    }
};

class n_cr_timeout_t:
    public check_diagnostic_optional_double_min_t< &ncf::diagnostic_t::n_cr_timeout, 0 >
{
  public:
    explicit n_cr_timeout_t(common::validate::logger_t &logger):
        check_diagnostic_optional_double_min_t< &ncf::diagnostic_t::n_cr_timeout, 0 >{
            logger,
            "n_cr_timeout"
        }
    {
    }
};

class support_sid_t:
    public check_diagnostic_int_vector_t< &ncf::diagnostic_t::support_sids, 0, 255 >
{
  public:
    explicit support_sid_t(common::validate::logger_t &logger):
        check_diagnostic_int_vector_t< &ncf::diagnostic_t::support_sids, 0, 255 >{ logger,
                                                                                   "support_sid" }
    {
    }
};

class max_message_length_t:
    public check_diagnostic_optional_int_min_t< &ncf::diagnostic_t::max_message_length, 1 >
{
  public:
    explicit max_message_length_t(common::validate::logger_t &logger):
        check_diagnostic_optional_int_min_t< &ncf::diagnostic_t::max_message_length, 1 >{
            logger,
            "max_message_length"
        }
    {
    }
};

}    // namespace lin::ncf::validate::diagnostic
