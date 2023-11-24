#include <ostream>

#include <lin/common/generator/indention.hpp>
#include <lin/ncf/generator/diagnostic.hpp>
#include <lin/ncf/generator/frame.hpp>
#include <lin/ncf/generator/free_text.hpp>
#include <lin/ncf/generator/general.hpp>
#include <lin/ncf/generator/node.hpp>
#include <lin/ncf/generator/signal_encoding.hpp>
#include <lin/ncf/generator/status_management.hpp>
#include <lin/ncf/node.hpp>

/* 8.2.2 Node definition */

namespace lin::ncf {

std::ostream &operator<<(std::ostream &out, node_t const &node)
{
    using namespace signal;

    out << common::indention_t::push << "node " << node.name << " {\n";
    out << node.general;
    out << node.diagnostic;
    out << node.frames;
    out << node.signal_encodings;
    out << node.status_management;
    if (!node.free_text.value.empty())
    {
        out << node.free_text;
    }
    out << common::indention_t::pop << "}\n";
    return out;
}

}    // namespace lin::ncf
