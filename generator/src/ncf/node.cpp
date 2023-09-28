#include <ostream>

#include <lin/ncf/node.hpp>

#include <lin/common/generator/indention.hpp>
#include <lin/ncf/generator/diagnostic.hpp>
#include <lin/ncf/generator/frame.hpp>
#include <lin/ncf/generator/free_text.hpp>
#include <lin/ncf/generator/general.hpp>
#include <lin/ncf/generator/node.hpp>
#include <lin/ncf/generator/signal.hpp>
#include <lin/ncf/generator/status.hpp>

namespace lin::ncf {

/* 8.2.2 Node definition */

std::ostream &operator<<(std::ostream &out, node_t const &node)
{
    out << common::indention_t::push << "node " << node.node_name << " {\n";
    out << node.general;
    out << node.diagnostic;
    out << node.frames;
    out << node.encodings;
    out << node.status;
    if (!node.free_text.value.empty())
    {
        out << node.free_text;
    }
    out << common::indention_t::pop << "}\n";
    return out;
}

}    // namespace lin::ncf
