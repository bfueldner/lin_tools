#pragma once

#include <lin/common/bnf.hpp>

namespace lin::common::bitrate {

struct kbps_t
{
    // NOLINTNEXTLINE(hicpp-explicit-conversions)
    operator common::bnf::real_or_integer_t() const { return value; }
    kbps_t &operator=(
        common::bnf::real_or_integer_t value_)    // NOLINT(readability-identifier-naming)
    {
        value = value_;
        return *this;
    }
    common::bnf::real_or_integer_t value{};
};

}    // namespace lin::common::bitrate
