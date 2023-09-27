#include <ostream>

#include <lin/ncf/free_text.hpp>

#include <lin/common/generator/indention.hpp>
#include <lin/ncf/generator/free_text.hpp>

namespace lin::ncf {

std::ostream &operator<<(std::ostream &out, free_text_t const &free_text)
{
    out << common::indention_t::indent << common::indention_t::push << "free_text {\n";
    out << common::indention_t::indent << "\"" << free_text.value << "\"\n";
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

}    // namespace lin::ncf
