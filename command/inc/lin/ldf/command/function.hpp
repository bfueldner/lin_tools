#pragma once

#include <lin/common/command/type.hpp>
#include <lin/ldf/lin_description_file.hpp>

namespace lin::ldf::command::function {

bool parse(lin::ldf::lin_description_file_t &lin_description_file, std::string &text);
void sort(lin::ldf::lin_description_file_t &lin_description_file);

}    // namespace lin::ldf::command::function
