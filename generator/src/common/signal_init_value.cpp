#include <ios>
#include <ostream>
#include <variant>

#include <lin/common/generator/signal_init_value.hpp>
#include <lin/common/signal_init_value.hpp>

/* Common signal init value definition */

namespace lin::common::signal {

namespace init_value {

std::ostream &operator<<(std::ostream &out, array_t const &array)
{
    out << "{ " << std::hex;
    for (auto iter = array.cbegin(); iter != array.cend(); ++iter)
    {
        out << "0x" << *iter;
        if (iter != array.cend() - 1)
        {
            out << ", ";
        }
    }
    out << " }" << std::dec;
    return out;
}

}    // namespace init_value

std::ostream &operator<<(std::ostream &out, init_value_t const &init_value)
{
    using namespace init_value;

    std::visit([&out](auto &&arg) { out << arg; }, init_value);
    return out;
}

}    // namespace lin::common::signal
