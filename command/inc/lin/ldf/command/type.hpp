#pragma once

#include <cstdint>

namespace lin::ncf::command {

enum class command_t : std::uint8_t
{
    validate,
    prettify,
    export_,    // NOLINT(readability-identifier-naming)
};

enum class type_t : std::uint8_t
{
    signal,
    frame,
};

}    // namespace lin::ncf::command
