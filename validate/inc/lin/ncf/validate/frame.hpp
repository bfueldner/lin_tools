#pragma once

#include <lin/ncf/validate/check.hpp>

/* 8.2.5 Frame definition */

namespace lin::ncf::validate::frame {

template < auto ncf::frame_t::*member_, common::bnf::integer_t min_ >
using check_frame_optional_int_min_t =
    common::validate::check_optional_int_min_t< ncf::frame_t, member_, min_ >;

template < auto ncf::frame_t::*member_, common::bnf::integer_t min_, common::bnf::integer_t max_ >
using check_frame_int_min_max_t =
    common::validate::check_int_min_max_t< ncf::frame_t, member_, min_, max_ >;

template < auto ncf::frame_t::*member_ >
using check_frame_signal_vector_name_t =
    common::validate::check_vector_name_t< ncf::frame_t, ncf::signal_t, member_ >;

class length_t: public check_frame_int_min_max_t< &ncf::frame_t::size, 1, 8 >
{
  public:
    explicit length_t(common::validate::logger_t &logger):
        check_frame_int_min_max_t< &ncf::frame_t::size, 1, 8 >{ logger, "length" }
    {
    }
};

class min_period_t: public check_frame_optional_int_min_t< &ncf::frame_t::min_period, 0 >
{
  public:
    explicit min_period_t(common::validate::logger_t &logger):
        check_frame_optional_int_min_t< &ncf::frame_t::min_period, 0 >{ logger, "min_period" }
    {
    }
};

class max_period_t: public check_frame_optional_int_min_t< &ncf::frame_t::max_period, 0 >
{
  public:
    explicit max_period_t(common::validate::logger_t &logger):
        check_frame_optional_int_min_t< &ncf::frame_t::max_period, 0 >{ logger, "max_period" }
    {
    }
};

class min_period_max_period_t: public check::frame_t
{
  public:
    explicit min_period_max_period_t(common::validate::logger_t &logger):
        check::frame_t{ logger, "min_period/max_period" }
    {
    }

    void run(const ncf::frame_t &frame) const final;
};

class signal_names_t: public check_frame_signal_vector_name_t< &ncf::frame_t::signals >
{
  public:
    explicit signal_names_t(common::validate::logger_t &logger):
        check_frame_signal_vector_name_t< &ncf::frame_t::signals >{ logger, "signal_names" }
    {
    }
};

class signal_sizes_t: public check::frame_t
{
  public:
    explicit signal_sizes_t(common::validate::logger_t &logger):
        check::frame_t{ logger, "signal_sizes" }
    {
    }

    void run(const ncf::frame_t &frame) const final;
};

class signal_offsets_t: public check::frame_t
{
  public:
    explicit signal_offsets_t(common::validate::logger_t &logger):
        check::frame_t{ logger, "signal_offsets" }
    {
    }

    void run(const ncf::frame_t &frame) const final;
};

class signal_size_offset_t: public check::frame_t
{
  public:
    explicit signal_size_offset_t(common::validate::logger_t &logger):
        check::frame_t{ logger, "signal_size_offset" }
    {
    }

    void run(const ncf::frame_t &frame) const final;
};

}    // namespace lin::ncf::validate::frame
