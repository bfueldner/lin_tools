#pragma once

#include <cstdint>
#include <ostream>

/* Space indention construct */

namespace lin::common {

enum class indention_t : std::uint8_t
{
    push,
    pop,
    indent,
    reset,
};

struct indention_width_t
{
    unsigned int value;
};

std::ostream &operator<<(std::ostream &out, indention_t const &indention);
std::ostream &operator<<(std::ostream &out, indention_width_t const &indention_width);

}    // namespace lin::common
