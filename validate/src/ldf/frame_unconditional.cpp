#include <algorithm>
#include <string>
#include <unordered_set>
#include <vector>

#include <lin/ldf/frame_unconditional.hpp>
#include <lin/ldf/nodes.hpp>
#include <lin/ldf/signal_standard.hpp>
#include <lin/ldf/validate/frame_unconditional.hpp>

/* 9.2.4.1 Unconditional frames */

namespace lin::ldf::validate::frame::unconditional {

void signal_published_by_t::run(
    const ldf::nodes_t & /*unused*/,
    const ldf::signal::standards_t &standard_signals,
    const ldf::frame::unconditional_t &frame) const
{
    std::unordered_set< std::string > publishers{};

    for (auto const &signal : frame.signals)
    {
        for (auto const &standard_signal : standard_signals)
        {
            if (standard_signal.name == signal.name)
            {
                if (standard_signal.published_by != frame.published_by)
                {
                    publishers.insert(standard_signal.published_by);
                }
                break;
            }
        }
    }

    if (!publishers.empty())
    {
        std::vector< std::string > const nodes{ publishers.begin(), publishers.end() };

        _log_error("Wrong node", _to_string(nodes));
        return;
    }

    _log_ok();
}

void signal_sizes_t::run(
    const ldf::nodes_t & /*unused*/,
    const ldf::signal::standards_t &signals,
    const ldf::frame::unconditional_t &frame) const
{
    if (frame.signals.empty())
    {
        return;
    }

    auto offset_compare = [](const ldf::frame::unconditional::signal_t &lhs,
                             const ldf::frame::unconditional::signal_t &rhs) {
        return lhs.offset < rhs.offset;
    };

    auto frame_signals = frame.signals;
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

    auto difference = frame.size * 8 - size;

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

void signal_offsets_t::run(
    const ldf::nodes_t & /*unused*/,
    const ldf::signal::standards_t &signals,
    const ldf::frame::unconditional_t &frame) const
{
    if (frame.signals.empty())
    {
        return;
    }

    auto offset_compare = [](const ldf::frame::unconditional::signal_t &lhs,
                             const ldf::frame::unconditional::signal_t &rhs) {
        return lhs.offset < rhs.offset;
    };

    auto frame_signals = frame.signals;
    std::sort(frame_signals.begin(), frame_signals.end(), offset_compare);

    int offset{ 0 };
    std::vector< std::string > names{};

    for (auto const &frame_signal : frame_signals)
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

}    // namespace lin::ldf::validate::frame::unconditional
