#include <ostream>

#include <lin/ncf/node_capability_file.hpp>

#include <lin/ncf/generator/node.hpp>
#include <lin/ncf/generator/node_capability_file.hpp>

namespace lin::ncf {

/* 8.2.2 Node definition */

std::ostream &operator<<(std::ostream &out, node_capability_file_t const &node_capability_file)
{
    out << "node_capability_file;\n";
    out << "LIN_language_version = \"" << node_capability_file.language_version << "\";\n";
    for (auto const &node : node_capability_file.node)
    {
        out << node;
    }
    return out;
}

}    // namespace lin::ncf
