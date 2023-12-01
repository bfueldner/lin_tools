#include <algorithm>
#include <string>
#include <type_traits>
#include <variant>

#include <lin/common/signal_encoding.hpp>
#include <lin/common/validate/signal_encoding.hpp>

/* Common signal encoding type definition */

namespace lin::common::validate::signal::encoding {

void types_t::run(const common::signal::encoding_t &encoding) const
{
    int logical_physical_count{ 0 };
    int ascii_count{ 0 };
    int bcd_count{ 0 };

    for (auto const &value : encoding.values)
    {
        std::visit(
            [&logical_physical_count, &ascii_count, &bcd_count](auto &&arg) {
                using T = std::decay_t< decltype(arg) >;
                if constexpr (
                    std::is_same_v< T, common::signal::encoding::logical_value_t > ||
                    std::is_same_v< T, common::signal::encoding::physical_range_t >)
                {
                    logical_physical_count++;
                }
                else if constexpr (std::is_same_v< T, common::signal::encoding::ascii_value_t >)
                {
                    ascii_count++;
                }
                else if constexpr (std::is_same_v< T, common::signal::encoding::bcd_value_t >)
                {
                    bcd_count++;
                }
            },
            value);
    }

    if ((ascii_count > 0) && (encoding.values.size() > 1))
    {
        _log_error("ASCII encoding can not be mixed with other encodings");
        return;
    }

    if ((bcd_count > 0) && (encoding.values.size() > 1))
    {
        _log_error("BCD encoding can not be mixed with other encodings");
        return;
    }

    _log_ok();
}

void values_t::run(const common::signal::encoding_t &encoding) const
{
    if (encoding.values.empty())
    {
        _log_warning("Empty");
        return;
    }

    /* ASCII and BCD values are ignored */
    auto value_min = [](auto &&arg) {
        using T = std::decay_t< decltype(arg) >;

        if constexpr (std::is_same_v< T, lin::common::signal::encoding::logical_value_t >)
        {
            return arg.value;
        }
        else if constexpr (std::is_same_v< T, lin::common::signal::encoding::physical_range_t >)
        {
            return arg.min;
        }
        return 0;
    };

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

    auto value_compare = [&value_min](
                             const lin::common::signal::encoding::value_t &lhs,
                             const lin::common::signal::encoding::value_t &rhs) {
        return std::visit(value_min, lhs) < std::visit(value_min, rhs);
    };

    auto values = encoding.values;
    std::sort(values.begin(), values.end(), value_compare);

    auto iter = values.begin();

    if (std::visit(value_min, *iter) > 0)
    {
        _log_warning("Not all values defined");
        return;
    }

    auto last = std::visit(value_max, *iter);

    while (++iter != values.end())
    {
        auto next = std::visit(value_min, *iter);
        auto diff = next - last;

        if (diff <= 0)
        {
            _log_error("Value or range overlap", _to_string(next));
            return;
        }

        if (diff > 1)
        {
            _log_warning("Not all values defined");
            return;
        }
        last = std::visit(value_max, *iter);
    }

    if (!std::is_sorted(encoding.values.begin(), encoding.values.end(), value_compare))
    {
        _log_warning("Not sorted");
        return;
    }

    _log_ok();
}

namespace value {

void value_t::run(const common::signal::encoding::value_t &value) const
{
    std::visit([this](auto &&arg) { run(arg); }, value);
}

void value_t::run(const common::signal::encoding::logical_value_t &value) const
{
    if (value.value < 0)
    {
        _log_error("Value too low", _to_string(value.value), ">= 0");
        return;
    }

    _log_ok();
}

void value_t::run(const common::signal::encoding::physical_range_t &range) const
{
    if (range.min < 0)
    {
        _log_error("Minimum value too low", _to_string(range.min), ">= 0");
        return;
    }

    if (range.min >= range.max)
    {
        _log_error("Range invalid", _to_string(range.min) + ".." + _to_string(range.max));
        return;
    }

    _log_ok();
}

void text_info_t::run(const common::signal::encoding::value_t &value) const
{
    std::visit([this](auto &&arg) { run(arg); }, value);
}

void text_info_t::run(const common::signal::encoding::logical_value_t &value) const
{
    if (value.text_info.empty())
    {
        _log_warning("Empty");
        return;
    }

    _log_ok();
}

void text_info_t::run(const common::signal::encoding::physical_range_t &range) const
{
    if (range.text_info.empty())
    {
        _log_warning("Empty");
        return;
    }

    _log_ok();
}

}    // namespace value

}    // namespace lin::common::validate::signal::encoding
