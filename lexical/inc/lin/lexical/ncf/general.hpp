#pragma once

#include <string>

namespace lin::lexical::ncf {

namespace general {

using lin_protocol_version_t = std::string;
using supplier_t             = int;
using function_t             = int;
using variant_t              = int;
using bitrate_t              = double;
using sends_wake_up_signal   = bool;

}    // namespace general

struct general_t
{
    general::lin_protocol_version_t lin_protocol_version{};
    general::supplier_t supplier{};
    general::function_t function{};
    general::variant_t variant{};
    general::bitrate_t bitrate{};
    general::sends_wake_up_signal sends_wake_up_sign{};
};


}    // namespace lin::lexical::ncf
