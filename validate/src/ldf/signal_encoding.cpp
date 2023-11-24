#include <algorithm>
#include <cmath>
#include <string>
#include <type_traits>
#include <variant>
#include <vector>

#include <lin/common/signal_encoding.hpp>
#include <lin/ldf/signal_encoding.hpp>
#include <lin/ldf/signal_representation.hpp>
#include <lin/ldf/signal_standard.hpp>
#include <lin/ldf/validate/signal_encoding.hpp>

/* 9.2.6.1 Signal encoding type definition */

namespace lin::ldf::validate::signal::encoding {

void usage_t::run(
    const ldf::signal::standards_t & /*unused*/,
    const ldf::signal::representations_t &representations,
    const ldf::signal::encoding_t &encoding) const
{
    auto in_use{ false };

    for (auto const &representation : representations)
    {
        if (representation.name == encoding.name)
        {
            in_use = true;
            break;
        }
    }

    if (!in_use)
    {
        _log_warning("Not used");
        return;
    }

    _log_ok();
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
void size_t::run(
    const ldf::signal::standards_t &signals,
    const ldf::signal::representations_t &representations,
    const ldf::signal::encoding_t &encoding) const
{
    auto value_max = [](auto &&arg) {
        using T = std::decay_t< decltype(arg) >;

        if constexpr (std::is_same_v< T, lin::common::signal::encoding::logical_value_t >)
        {
            return arg.value;
        }
        else if constexpr (std::is_same_v< T, lin::common::signal::encoding::physical_range_t >)
        {
            return arg.max;
        }
        return 0;
    };

    /* Get maximum value */
    int max{ 0 };

    for (auto const &value : encoding.values)
    {
        max = std::max(max, std::visit(value_max, value));
    }

    /* Walk representations to find signals using actual encoding */
    std::vector< std::string > encoding_bigger{};
    std::vector< std::string > encoding_smaller{};

    for (auto const &representation : representations)
    {
        if (representation.name == encoding.name)
        {
            for (auto const &representation_signal : representation.signals)
            {
                for (auto const &signal : signals)
                {
                    if (representation_signal == signal.name)
                    {
                        auto size = std::pow(2, signal.size) - 1;

                        if (size < max)
                        {
                            encoding_bigger.push_back(signal.name);
                        }
                        else if (size > max)
                        {
                            encoding_smaller.push_back(signal.name);
                        }
                    }
                }
            }
        }
    }

    if (!encoding_bigger.empty())
    {
        _log_error("Encoding bigger than signal", _to_string(encoding_bigger));
        return;
    }

    if (!encoding_smaller.empty())
    {
        _log_warning("Encoding smaller than signal", _to_string(encoding_smaller));
        return;
    }

    _log_ok();
}
// NOLINTEND(readability-function-cognitive-complexity)

}    // namespace lin::ldf::validate::signal::encoding
