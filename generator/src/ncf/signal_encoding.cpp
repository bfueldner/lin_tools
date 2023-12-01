#include <ostream>

#include <lin/common/generator/indention.hpp>
#include <lin/common/generator/signal_encoding.hpp>
#include <lin/ncf/generator/signal_encoding.hpp>
#include <lin/ncf/signal_encoding.hpp>

/* 8.2.5.3 Signal encoding type definition */

namespace lin::ncf::signal {

std::ostream &operator<<(std::ostream &out, const encoding_t &encoding)
{
    out << common::indention_t::indent << common::indention_t::push << encoding.name << " {\n";
    for (auto const &value : encoding.values)
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

}    // namespace lin::ncf::signal
