#pragma once

#include <optional>
#include <variant>
#include <vector>

#include <lin/common/bnf.hpp>

/* 8.2.3 General definition */

namespace lin::ncf {

namespace general {

/* 8.2.3.1 LIN protocol version number definition */

using protocol_version_t = common::bnf::char_string_t;

/* 8.2.3.2 LIN Product Identification */

using supplier_id_t = common::bnf::integer_t;
using function_id_t = common::bnf::integer_t;
using variant_id_t  = common::bnf::integer_t;

/* 8.2.3.3 Bit rate */

struct bitrate_t
{
    common::bnf::real_or_integer_t value;
};

namespace bitrate_definition {

struct automatic_t
{
    std::optional< bitrate_t > min{};
    std::optional< bitrate_t > max{};
};

using select_t = std::vector< bitrate_t >;
using fixed_t  = bitrate_t;

}    // namespace bitrate_definition

using bitrate_definition_t = std::variant<
    bitrate_definition::automatic_t,
    bitrate_definition::select_t,
    bitrate_definition::fixed_t >;

/* 8.2.3.4 Sends wake up signal */

using sends_wake_up_signal_t = bool;

}    // namespace general

struct general_t
{
    general::protocol_version_t protocol_version{};
    general::supplier_id_t supplier_id{};
    general::function_id_t function_id{};
    general::variant_id_t variant_id{};
    general::bitrate_definition_t bitrate_definition{};
    general::sends_wake_up_signal_t sends_wake_up_signal{};
};

}    // namespace lin::ncf
