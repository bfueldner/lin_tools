#include <ostream>

#include <lin/common/bitrate.hpp>
#include <lin/common/bnf.hpp>
#include <lin/common/generator/bitrate.hpp>

namespace lin::common::bitrate {

std::ostream &operator<<(std::ostream &out, kbps_t const &kbps)
{
    out << static_cast< common::bnf::real_or_integer_t >(kbps) << " kbps";
    return out;
}

}    // namespace lin::common::bitrate
