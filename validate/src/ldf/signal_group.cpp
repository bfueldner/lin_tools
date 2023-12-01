#include <algorithm>
#include <string>
#include <vector>

#include <lin/ldf/signal_group.hpp>
#include <lin/ldf/signal_standard.hpp>
#include <lin/ldf/validate/signal_group.hpp>

/* 9.2.3.3 Signal groups */

namespace lin::ldf::validate::signal::group {

void signal_sizes_t::run(const ldf::signal::standards_t &signals, const ldf::signal::group_t &group)
    const
{
    if (group.signals.empty())
    {
        return;
    }

    auto offset_compare = [](const ldf::signal::group::signal_t &lhs,
                             const ldf::signal::group::signal_t &rhs) {
        return lhs.offset < rhs.offset;
    };

    auto frame_signals = group.signals;
    std::sort(frame_signals.begin(), frame_signals.end(), offset_compare);

    auto size = frame_signals.back().offset;
    for (auto const &signal : signals)
    {
        if (signal.name == frame_signals.back().name)
        {
            size += signal.size;
            break;
        }
    }

    auto difference = group.size * 8 - size;

    if (difference < 0)
    {
        _log_error(
            "Signals greater than frame",
            _to_string(-difference) + " bit",
            _to_string(group.size * 8) + " bit");
        return;
    }

    if (difference >= 8)
    {
        _log_warning(
            "Signals with unused space",
            std::to_string(difference) + " bit",
            _to_string(group.size * 8) + " bit");
        return;
    }

    _log_ok();
}

void signal_offsets_t::run(
    const ldf::signal::standards_t &signals,
    const ldf::signal::group_t &group) const
{
    if (group.signals.empty())
    {
        return;
    }

    auto offset_compare = [](const ldf::signal::group::signal_t &lhs,
                             const ldf::signal::group::signal_t &rhs) {
        return lhs.offset < rhs.offset;
    };

    auto group_signals = group.signals;
    std::sort(group_signals.begin(), group_signals.end(), offset_compare);

    int offset{ 0 };
    std::vector< std::string > names{};

    for (auto const &frame_signal : group_signals)
    {
        int signal_size{ 0 };

        for (auto const &signal : signals)
        {
            if (signal.name == frame_signal.name)
            {
                signal_size = signal.size;
                break;
            }
        }

        if (frame_signal.offset < offset)
        {
            names.push_back(frame_signal.name);
        }
        offset = frame_signal.offset + signal_size;
    }

    if (!names.empty())
    {
        _log_error("Signal overlap", _to_string(names));
        return;
    }

    _log_ok();
}

}    // namespace lin::ldf::validate::signal::group
