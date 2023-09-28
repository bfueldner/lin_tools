#include <iomanip>
#include <ios>
#include <ostream>
#include <variant>

#include <lin/ncf/diagnostic.hpp>

#include <lin/common/generator/indention.hpp>
#include <lin/ncf/generator/diagnostic.hpp>

/* 8.2.4 Diagnostic definition */

namespace lin::ncf {

namespace diagnostic {

namespace nad {

std::ostream &operator<<(std::ostream &out, sequence_t const &sequence)
{
    for (auto iter = sequence.cbegin(); iter != sequence.cend(); ++iter)
    {
        if (iter != sequence.cbegin())
        {
            out << ", ";
        }
        out << *iter;
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, range_t const &range)
{
    out << range.begin << " to " << range.end;
    return out;
}

}    // namespace nad

std::ostream &operator<<(std::ostream &out, nad_t const &nad)
{
    std::visit([&out](auto &&arg) { out << arg; }, nad);
    return out;
}

}    // namespace diagnostic

std::ostream &operator<<(std::ostream &out, diagnostic_t const &diagnostic)
{
    using namespace diagnostic;

    out << common::indention_t::indent << common::indention_t::push << "diagnostic {\n";
    out << common::indention_t::indent << "NAD = " << diagnostic.nad << ";\n";
    out << common::indention_t::indent << "diagnostic_class = " << diagnostic.diagnostic_class
        << ";\n";
    if (diagnostic.p2_min)
    {
        out << common::indention_t::indent << "P2_min = " << diagnostic.p2_min.value() << " ms;\n";
    }

    if (diagnostic.st_min)
    {
        out << common::indention_t::indent << "ST_min = " << diagnostic.st_min.value() << " ms;\n";
    }

    if (diagnostic.n_as_timeout)
    {
        out << common::indention_t::indent << "N_As_timeout = " << diagnostic.n_as_timeout.value()
            << " ms;\n";
    }

    if (diagnostic.n_cr_timeout)
    {
        out << common::indention_t::indent << "N_Cr_timeout = " << diagnostic.n_cr_timeout.value()
            << " ms;\n";
    }

    if (!diagnostic.support_sid.empty())
    {
        out << common::indention_t::indent << "support_sid { " << std::hex << std::setfill('0');
        for (auto iter = diagnostic.support_sid.cbegin(); iter != diagnostic.support_sid.cend();
             ++iter)
        {
            out << "0x" << std::setw(2) << *iter;
            if (iter != diagnostic.support_sid.cend() - 1)
            {
                out << ", ";
            }
        }
        out << std::dec << " };\n";
    }

    if (diagnostic.max_message_length)
    {
        out << common::indention_t::indent
            << "max_message_length = " << diagnostic.max_message_length.value() << ";\n";
    }
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

}    // namespace lin::ncf
