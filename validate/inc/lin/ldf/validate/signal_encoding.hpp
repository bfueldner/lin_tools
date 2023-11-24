#pragma once

#include <lin/ldf/validate/check.hpp>

/* 9.2.6.1 Signal encoding type definition */

namespace lin::ldf::validate::signal::encoding {

class usage_t: public check::signal_encoding_t
{
  public:
    explicit usage_t(common::validate::logger_t &logger):
        check::signal_encoding_t{ logger, "usage" }
    {
    }

    void run(
        const ldf::signal::standards_t & /*unused*/,
        const ldf::signal::representations_t &representations,
        const ldf::signal::encoding_t &encoding) const final;
};

class size_t: public check::signal_encoding_t
{
  public:
    explicit size_t(common::validate::logger_t &logger):
        check::signal_encoding_t{ logger, "size" }
    {
    }

    void run(
        const ldf::signal::standards_t &signals,
        const ldf::signal::representations_t &representations,
        const ldf::signal::encoding_t &encoding) const final;
};


}    // namespace lin::ldf::validate::signal::encoding
