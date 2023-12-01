#pragma once

#include <optional>
#include <variant>
#include <vector>

#include <lin/common/bitrate.hpp>
#include <lin/common/bnf.hpp>

/* 8.2.3 General definition */

namespace lin::ncf {

namespace general {

/* 8.2.3.1 LIN protocol version number definition */

using protocol_version_t = common::bnf::char_string_t;

/* 8.2.3.2 LIN Product Identification */

using supplier_t = common::bnf::integer_t;
using function_t = common::bnf::integer_t;
using variant_t  = common::bnf::integer_t;

/* 8.2.3.3 Bit rate */

namespace bitrate {

using kbps_t = common::bitrate::kbps_t;

struct automatic_t
{
    std::optional< kbps_t > min{};
    std::optional< kbps_t > max{};
};

using select_t = std::vector< kbps_t >;
using fixed_t  = kbps_t;

}    // namespace bitrate

using bitrate_t = std::variant< bitrate::automatic_t, bitrate::select_t, bitrate::fixed_t >;

/* 8.2.3.4 Sends wake up signal */

using sends_wake_up_signal_t = bool;

}    // namespace general

struct general_t
{
    general::protocol_version_t protocol_version{};
    general::supplier_t supplier{};
    general::function_t function{};
    general::variant_t variant{};
    general::bitrate_t bitrate{};
    general::sends_wake_up_signal_t sends_wake_up_signal{};
};

}    // namespace lin::ncf
