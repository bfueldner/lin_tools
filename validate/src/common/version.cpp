#include <stdexcept>
#include <string>
#include <vector>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#include <lin/common/validate/version.hpp>

namespace lin::common::validate::version {

version_t from_string(std::string text)
{
    std::vector< std::string > parts;
    boost::split(
        parts, text, boost::is_any_of("."));    // NOLINT(clang-analyzer-cplusplus.NewDeleteLeaks)

    if (parts.size() != 2)
    {
        throw std::out_of_range("No valid version format");
    }

    return { static_cast< unsigned int >(std::stoul(parts[0])),
             static_cast< unsigned int >(std::stoul(parts[1])) };
}

}    // namespace lin::common::validate::version
