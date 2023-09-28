#include <cstddef>
#include <ostream>
#include <string>

#include <lin/common/generator/indention.hpp>

/* Space indention construct */

namespace lin::common {

// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
unsigned int indention_count = 4;
unsigned int indention_level = 0;
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

std::ostream &operator<<(std::ostream &out, indention_t const &indention)
{
    switch (indention)
    {
        case indention_t::indent:
        {
            out << std::string(static_cast< size_t >(indention_count * indention_level), ' ');
            break;
        }

        case indention_t::push:
        {
            indention_level++;
            break;
        }

        case indention_t::pop:
        {
            if (indention_level > 0)
            {
                indention_level--;
            }
            break;
        }

        case indention_t::reset:
        {
            indention_count = 4;
            indention_level = 0;
            break;
        }
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, indention_width_t const &indention_width)
{
    indention_count = indention_width.value;
    return out;
}

}    // namespace lin::common
