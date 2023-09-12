#include <iomanip>

#include <lin/type_io/common/signal_encoding_type.hpp>

/* Common signal encoding type definition */

namespace lin::type::common::signal_encoding_type {

std::ostream &operator<<(std::ostream &out, const logical_value_t &logic_value)
{
    out << "logical_value, " << logic_value.signal_value;
    if (logic_value.text_info.length() > 0)
    {
        out << ", \"" << logic_value.text_info << "\"";
    }
    out << ";" << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, const physical_range_t &physical_range)
{
    out << "physical_value, " << physical_range.min_value << ", " << physical_range.max_value
        << ", " << physical_range.scale << ", " << physical_range.offset;
    if (physical_range.text_info.length() > 0)
    {
        out << ", \"" << physical_range.text_info << "\"";
    }
    out << ";" << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, const bcd_value_t & /*unused*/)
{
    out << "bcd_value;" << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, const ascii_value_t & /*unused*/)
{
    out << "ascii_value;" << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, const value_t &value)
{
    std::visit([&out](auto &&arg) { out << arg; }, value);
    return out;
}

}    // namespace lin::type::common::signal_encoding_type
