#pragma once

#include <lin/ldf/validate/check.hpp>

/* 9.2.6.2 Signal representation definition */

namespace lin::ldf::validate::signal::representation {

class encoding_t:
    public common::validate::check_name_t<
        ldf::signal::representation_t,
        &ldf::signal::representation_t::name,
        0,
        ldf::signal::encodings_t,
        ldf::signal::standards_t >
{
  public:
    explicit encoding_t(common::validate::logger_t &logger):
        common::validate::check_name_t<
            ldf::signal::representation_t,
            &ldf::signal::representation_t::name,
            0,
            ldf::signal::encodings_t,
            ldf::signal::standards_t >{ logger, "encoding" }
    {
    }
};

class signals_t:
    public common::validate::check_names_t<
        ldf::signal::representation_t,
        &ldf::signal::representation_t::signals,
        1,
        ldf::signal::encodings_t,
        ldf::signal::standards_t >
{
  public:
    explicit signals_t(common::validate::logger_t &logger):
        common::validate::check_names_t<
            ldf::signal::representation_t,
            &ldf::signal::representation_t::signals,
            1,
            ldf::signal::encodings_t,
            ldf::signal::standards_t >{ logger, "signals" }
    {
    }
};

}    // namespace lin::ldf::validate::signal::representation
