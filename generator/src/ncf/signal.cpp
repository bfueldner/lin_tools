#include <ios>
#include <ostream>
#include <variant>

#include <lin/ncf/signal.hpp>

#include <lin/common/generator/indention.hpp>
#include <lin/common/generator/signal_encoding_type.hpp>
#include <lin/ncf/generator/signal.hpp>

namespace lin::ncf {

/* 8.2.5.2 Signal definition */

namespace signal {

std::ostream &operator<<(std::ostream &out, init_value_array_t const &init_value_array)
{
    out << "{ " << std::hex;
    for (auto iter = init_value_array.cbegin(); iter != init_value_array.cend(); ++iter)
    {
        out << "0x" << *iter;
        if (iter != init_value_array.cend() - 1)
        {
            out << ", ";
        }
    }
    out << " }" << std::dec;
    return out;
}

std::ostream &operator<<(std::ostream &out, init_value_t const &init_value)
{
    std::visit([&out](auto &&arg) { out << arg; }, init_value);
    return out;
}

std::ostream &operator<<(std::ostream &out, signal_properties_t const &signal_properties)
{
    out << common::indention_t::indent << "init_value = " << signal_properties.init_value << ";\n";
    out << common::indention_t::indent << "size = " << signal_properties.size << ";\n";
    out << common::indention_t::indent << "offset = " << signal_properties.offset << ";\n";
    if (!signal_properties.encoding_name.empty())
    {
        out << common::indention_t::indent << signal_properties.encoding_name << ";\n";
    }
    return out;
}

}    // namespace signal

std::ostream &operator<<(std::ostream &out, signal_t const &signal)
{
    out << common::indention_t::indent << common::indention_t::push << signal.signal_name << " {\n";
    out << signal.signal_properties;
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, signals_t const &signals)
{
    out << common::indention_t::indent << common::indention_t::push << "signals {\n";
    for (auto const &signal : signals)
    {
        out << signal;
    }
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

/* 8.2.5.3 Signal encoding type definition */

namespace signal_encoding_type {

std::ostream &operator<<(std::ostream &out, encoding_t const &encoding)
{
    using namespace common::signal_encoding_type;

    out << common::indention_t::indent << common::indention_t::push << encoding.encoding_name
        << " {\n";
    for (auto const &value : encoding.value)
    {
        out << value;
    }
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, encodings_t const &encodings)
{
    out << common::indention_t::indent << common::indention_t::push << "encoding {\n";
    for (auto const &encoding : encodings)
    {
        out << encoding;
    }
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

}    // namespace signal_encoding_type

}    // namespace lin::ncf
