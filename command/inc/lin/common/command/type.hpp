#pragma once

#include <cstdint>

namespace lin::common::command {

enum class type_t : std::uint8_t
{
    export_,    // NOLINT(readability-identifier-naming)
    prettify,
    validate,
};

enum class export_type_t : std::uint8_t
{
    signal,
    frame,
};

}    // namespace lin::common::command
