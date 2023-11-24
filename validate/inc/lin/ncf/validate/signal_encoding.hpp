#pragma once

#include <lin/ncf/validate/check.hpp>

/* 8.2.5.3 Signal encoding type definition */

namespace lin::ncf::validate::signal_encoding {

class usage_t: public check::signal_encodings_t
{
  public:
    explicit usage_t(common::validate::logger_t &logger):
        check::signal_encodings_t{ logger, "usage" }
    {
    }

    void run(const ncf::frames_t &frames, const ncf::signal::encodings_t &signal_encodings)
        const final;
};

}    // namespace lin::ncf::validate::signal_encoding
