#include <variant>
#include <vector>

#include <lin/ncf/general.hpp>
#include <lin/ncf/validate/general.hpp>

/* 8.2.5 General definition */

namespace lin::ncf::validate::general {

void bitrate_t::run(const ncf::general_t &general) const
{
    std::visit([this](auto &&arg) { run(arg); }, general.bitrate);
}

void bitrate_t::run(const ncf::general::bitrate::automatic_t &bitrate_automatic) const
{
    bool ok{ false };

    if (bitrate_automatic.min.has_value())
    {
        if (bitrate_automatic.min.value() < min)
        {
            _log_error("Minimum value too low", _to_string(bitrate_automatic.min.value()), _range);
            return;
        }
        ok = true;
    }

    if (bitrate_automatic.max.has_value())
    {
        if (bitrate_automatic.max.value() > max)
        {
            _log_error("Maximum value too high", _to_string(bitrate_automatic.max.value()), _range);
            return;
        }
        ok = true;
    }

    if (bitrate_automatic.min.has_value() && bitrate_automatic.max.has_value())
    {
        if (bitrate_automatic.min.value() >= bitrate_automatic.max.value())
        {
            _log_error(
                "Range invalid",
                _to_string(bitrate_automatic.min.value()) + ".." +
                    _to_string(bitrate_automatic.max.value()),
                _range + " < " + _range);
            return;
        }
    }

    if (ok)
    {
        _log_ok();
    }
}

void bitrate_t::run(const ncf::general::bitrate::select_t &bitrate_select) const
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    *const_cast< std::vector< ncf::general::bitrate::kbps_t > * >(&_select) = bitrate_select;
    _check_bitrate_select.run(*this);
}

void bitrate_t::run(const ncf::general::bitrate::fixed_t &bitrate_fixed) const
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    *const_cast< ncf::general::bitrate::kbps_t * >(&_fixed) = bitrate_fixed;
    _check_bitrate_fixed.run(*this);
}

}    // namespace lin::ncf::validate::general
