#include <ostream>
#include <variant>

#include <lin/common/signal_encoding_type.hpp>

#include <lin/common/generator/indention.hpp>
#include <lin/common/generator/signal_encoding_type.hpp>

/* Common signal encoding type definition */

namespace lin::common::signal_encoding_type {

std::ostream &operator<<(std::ostream &out, const logical_value_t &logic_value)
{
    out << "logical_value, " << logic_value.signal_value;
    if (!logic_value.text_info.empty())
    {
        out << ", \"" << logic_value.text_info << "\"";
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, const physical_range_t &physical_range)
{
    out << "physical_value, " << physical_range.min_value << ", " << physical_range.max_value
        << ", " << physical_range.scale << ", " << physical_range.offset;
    if (!physical_range.text_info.empty())
    {
        out << ", \"" << physical_range.text_info << "\"";
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, const bcd_value_t & /*unused*/)
{
    out << "bcd_value";
    return out;
}

std::ostream &operator<<(std::ostream &out, const ascii_value_t & /*unused*/)
{
    out << "ascii_value";
    return out;
}

std::ostream &operator<<(std::ostream &out, const value_t &value)
{
    std::visit([&out](auto &&arg) { out << indention_t::indent << arg << ";\n"; }, value);
    return out;
}

}    // namespace lin::common::signal_encoding_type
