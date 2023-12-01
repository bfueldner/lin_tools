#include <algorithm>
#include <string>
#include <vector>

#include <lin/ncf/frame.hpp>
#include <lin/ncf/validate/frame.hpp>

/* 8.2.5 Frame definition */

namespace lin::ncf::validate::frame {

void min_period_max_period_t::run(const ncf::frame_t &frame) const
{
    if (frame.min_period.has_value() && frame.max_period.has_value())
    {
        if (frame.min_period.value() > frame.max_period.value())
        {
            _log_error(
                "Invalid range",
                _to_string(frame.min_period.value()) + ".." + _to_string(frame.max_period.value()),
                "min_period <= max_period");
            return;
        }

        _log_ok();
    }
}

void signal_sizes_t::run(const ncf::frame_t &frame) const
{
    if (frame.signals.empty())
    {
        _log_warning("Empty");
        return;
    }

    auto const &signal = frame.signals.back();
    auto size          = signal.offset + signal.size;
    auto difference    = frame.size * 8 - size;

    if (difference < 0)
    {
        _log_error(
            "Signals greater than frame",
            _to_string(-difference) + " bit",
            _to_string(frame.size * 8) + " bit");
        return;
    }

    if (difference >= 8)
    {
        _log_warning(
            "Signals with unused space",
            std::to_string(difference) + " bit",
            _to_string(frame.size * 8) + " bit");
        return;
    }

    _log_ok();
}

void signal_offsets_t::run(const ncf::frame_t &frame) const
{
    if (frame.signals.empty())
    {
        _log_warning("Empty");
        return;
    }

    auto offset_compare = [](const ncf::signal_t &lhs, const ncf::signal_t &rhs) {
        return lhs.offset < rhs.offset;
    };

    if (!std::is_sorted(frame.signals.begin(), frame.signals.end(), offset_compare))
    {
        _log_warning("Not sorted");
        return;
    }

    _log_ok();
}

void signal_size_offset_t::run(const ncf::frame_t &frame) const
{
    int offset{ 0 };
    std::vector< std::string > names{};

    auto signals        = frame.signals;
    auto offset_compare = [](const ncf::signal_t &lhs, const ncf::signal_t &rhs) {
        return lhs.offset < rhs.offset;
    };

    std::sort(signals.begin(), signals.end(), offset_compare);

    for (auto const &signal : signals)
    {
        if (signal.offset < offset)
        {
            names.push_back(signal.name);
        }
        offset = signal.offset + signal.size;
    }

    if (!names.empty())
    {
        _log_error("Signal overlap", _to_string(names));
        return;
    }

    _log_ok();
}

}    // namespace lin::ncf::validate::frame
