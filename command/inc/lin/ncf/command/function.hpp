#pragma once

#include <filesystem>

#include <lin/ncf/command/type.hpp>
#include <lin/ncf/node_capability_file.hpp>

namespace lin::ncf::command {

bool validate(lin::ncf::node_capability_file_t &node_capability_file, bool verbose);
bool prettify(
    lin::ncf::node_capability_file_t &node_capability_file,
    unsigned int indent,
    std::filesystem::path &output,
    bool verbose);
bool export_(    // NOLINT(readability-identifier-naming)
    node_t *node,
    lin::ncf::command::type_t type,
    const std::string &namespace_,    // NOLINT(readability-identifier-naming)
    unsigned int indent,
    std::filesystem::path &output,
    bool verbose);

}    // namespace lin::ncf::command
