#pragma once

#include <filesystem>

#include <lin/ncf/command/type.hpp>
#include <lin/ncf/node_capability_file.hpp>

namespace lin::ncf::command::function {

bool parse(lin::ncf::node_capability_file_t &node_capability_file, std::string &text);
void sort(lin::ncf::node_capability_file_t &node_capability_file);


bool export_(    // NOLINT(readability-identifier-naming)
    node_t *node,
    lin::ncf::command::export_type_t type,
    const std::string &namespace_,    // NOLINT(readability-identifier-naming)
    std::filesystem::path &output,
    unsigned int indent,
    bool verbose);

}    // namespace lin::ncf::command::function
