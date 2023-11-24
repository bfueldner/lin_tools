#pragma once

#include <lin/ncf/validate/check.hpp>

/* 8.2.3 General definition */

namespace lin::ncf::validate::general {

template < auto ncf::general_t::*member_, common::bnf::integer_t min_, common::bnf::integer_t max_ >
using check_general_int_min_max_t =
    common::validate::check_int_min_max_t< ncf::general_t, member_, min_, max_ >;

class protocol_version_t: public common::validate::check_protocol_version_t< ncf::general_t >
{
  public:
    explicit protocol_version_t(common::validate::logger_t &logger):
        common::validate::check_protocol_version_t< ncf::general_t >{ logger, "protocol_version" }
    {
    }
};

class supplier_t: public check_general_int_min_max_t< &ncf::general_t::supplier, 0, 0xFFFF >
{
  public:
    explicit supplier_t(common::validate::logger_t &logger):
        check_general_int_min_max_t< &ncf::general_t::supplier, 0, 0xFFFF >{ logger, "supplier" }
    {
    }
};

class function_t: public check_general_int_min_max_t< &ncf::general_t::function, 0, 0xFFFF >
{
  public:
    explicit function_t(common::validate::logger_t &logger):
        check_general_int_min_max_t< &ncf::general_t::function, 0, 0xFFFF >{ logger, "function" }
    {
    }
};

class variant_t: public check_general_int_min_max_t< &ncf::general_t::variant, 0, 0xFF >
{
  public:
    explicit variant_t(common::validate::logger_t &logger):
        check_general_int_min_max_t< &ncf::general_t::variant, 0, 0xFF >{ logger, "variant" }
    {
    }
};

class bitrate_t: public check::general_t
{
  public:
    static constexpr ncf::general::bitrate::kbps_t min = { 1.0 };
    static constexpr ncf::general::bitrate::kbps_t max = { 20.0 };

    explicit bitrate_t(common::validate::logger_t &logger):
        check::general_t{ logger, "bitrate" },
        _range{ _to_string(min) + ".." + _to_string(max) },
        _check_bitrate_select{ logger, "bitrate" },
        _check_bitrate_fixed{ logger, "bitrate" }
    {
    }

    void run(const ncf::general_t &general) const final;
    void run(const ncf::general::bitrate::automatic_t &bitrate_automatic) const;
    void run(const ncf::general::bitrate::select_t &bitrate_select) const;
    void run(const ncf::general::bitrate::fixed_t &bitrate_fixed) const;

  private:
    std::string _range;
    ncf::general::bitrate::select_t _select{};
    ncf::general::bitrate::fixed_t _fixed{};

    using check_bitrate_select_t = common::validate::
        check_vector_t< bitrate_t, ncf::general::bitrate::kbps_t, &bitrate_t::_select, min, max >;
    using check_bitrate_fixed_t = common::validate::
        check_min_max_t< bitrate_t, ncf::general::bitrate::kbps_t, &bitrate_t::_fixed, min, max >;

    check_bitrate_select_t _check_bitrate_select;
    check_bitrate_fixed_t _check_bitrate_fixed;
};

}    // namespace lin::ncf::validate::general
