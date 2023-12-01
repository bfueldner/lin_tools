#include <ostream>

#include <lin/common/generator/indention.hpp>
#include <lin/common/generator/signal_encoding.hpp>
#include <lin/ldf/generator/signal_encoding.hpp>
#include <lin/ldf/signal_encoding.hpp>

/* 9.2.6.1 Signal encoding type definition */

namespace lin::ldf::signal {

std::ostream &operator<<(std::ostream &out, encoding_t const &encoding)
{
    using namespace common::signal::encoding;

    out << common::indention_t::indent << encoding.name << common::indention_t::push << " {\n";
    for (auto const &value : encoding.values)
    {
        out << value;
    }
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, encodings_t const &encodings)
{
    out << common::indention_t::push << "Signal_encoding_types {\n";
    for (auto const &encoding : encodings)
    {
        out << encoding;
    }
    out << common::indention_t::pop << "}\n";
    return out;
}

}    // namespace lin::ldf::signal
