#pragma once

#include <string>

namespace lin::common::validate {

struct version_t
{
    unsigned int high;
    unsigned int low;
};

namespace version {

version_t from_string(std::string text);

}    // namespace version

}    // namespace lin::common::validate
