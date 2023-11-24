#pragma once

#include <lin/common/validate/check.hpp>

/* Common signal encoding type definition */

namespace lin::common::validate::signal::encoding {

class types_t: public check::signal_encoding_t
{
  public:
    explicit types_t(common::validate::logger_t &logger):
        check::signal_encoding_t{ logger, "types" }
    {
    }

    void run(const common::signal::encoding_t &encoding) const final;
};

class values_t: public check::signal_encoding_t
{
  public:
    explicit values_t(common::validate::logger_t &logger):
        check::signal_encoding_t{ logger, "values" }
    {
    }

    void run(const common::signal::encoding_t &encoding) const final;
};

namespace value {

class value_t: public check::signal_encoding_value_t
{
  public:
    explicit value_t(common::validate::logger_t &logger):
        check::signal_encoding_value_t{ logger, "value" }
    {
    }

    void run(const common::signal::encoding::value_t &value) const final;
    void run(const common::signal::encoding::logical_value_t &value) const;
    void run(const common::signal::encoding::physical_range_t &range) const;
    void run(const common::signal::encoding::ascii_value_t & /*unused*/) const { _log_ok(); }
    void run(const common::signal::encoding::bcd_value_t & /*unused*/) const { _log_ok(); }
};

class text_info_t: public check::signal_encoding_value_t
{
  public:
    explicit text_info_t(common::validate::logger_t &logger):
        check::signal_encoding_value_t{ logger, "text_info" }
    {
    }

    void run(const common::signal::encoding::value_t &value) const final;
    void run(const common::signal::encoding::logical_value_t &value) const;
    void run(const common::signal::encoding::physical_range_t &range) const;
    void run(const common::signal::encoding::ascii_value_t & /*unused*/) const { _log_ok(); }
    void run(const common::signal::encoding::bcd_value_t & /*unused*/) const { _log_ok(); }
};

}    // namespace value

}    // namespace lin::common::validate::signal::encoding
