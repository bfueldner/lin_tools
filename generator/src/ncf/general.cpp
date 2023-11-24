#include <iomanip>
#include <ios>
#include <ostream>
#include <variant>

#include <lin/common/generator/bitrate.hpp>
#include <lin/common/generator/indention.hpp>
#include <lin/ncf/general.hpp>
#include <lin/ncf/generator/general.hpp>

namespace lin::ncf {

/* 8.2.3 General definition */

namespace general {

/* 8.2.3.3 Bit rate */

namespace bitrate {

std::ostream &operator<<(std::ostream &out, automatic_t const &automatic)
{
    out << "automatic";
    if (automatic.min)
    {
        out << " min " << automatic.min.value();
    }

    if (automatic.max)
    {
        out << " max " << automatic.max.value();
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, select_t const &select)
{
    out << "select { ";
    for (auto iter = select.cbegin(); iter != select.cend(); ++iter)
    {
        out << *iter;
        if (iter != select.cend() - 1)
        {
            out << ", ";
        }
    }
    out << " }";
    return out;
}

}    // namespace bitrate

std::ostream &operator<<(std::ostream &out, bitrate_t const &bitrate)
{
    using namespace bitrate;

    std::visit([&out](auto &&arg) { out << arg; }, bitrate);
    return out;
}

}    // namespace general

std::ostream &operator<<(std::ostream &out, general_t const &general)
{
    using namespace general;

    out << common::indention_t::indent << common::indention_t::push << "general {\n";
    out << common::indention_t::indent << "LIN_protocol_version = \"" << general.protocol_version
        << "\";\n";

    out << std::hex << std::setfill('0');
    out << common::indention_t::indent << "supplier = 0x" << std::setw(4) << general.supplier
        << ";\n";
    out << common::indention_t::indent << "function = 0x" << std::setw(4) << general.function
        << ";\n";
    out << std::dec;
    out << common::indention_t::indent << "variant = " << general.variant << ";\n";
    out << common::indention_t::indent << "bitrate = " << general.bitrate << ";\n";
    out << common::indention_t::indent << "sends_wake_up_signal = \""
        << (general.sends_wake_up_signal ? "yes" : "no") << "\";\n";
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

}    // namespace lin::ncf
