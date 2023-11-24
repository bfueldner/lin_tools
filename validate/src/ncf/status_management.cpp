#include <map>
#include <vector>

#include <lin/ncf/frame.hpp>
#include <lin/ncf/status_management.hpp>
#include <lin/ncf/validate/status_management.hpp>

/* 8.2.6 Status management */

namespace lin::ncf::validate::status_management {

void response_error_t::run(
    const ncf::frames_t &frames,
    const ncf::status_management_t &status_management) const
{
    bool found{ false };
    for (auto const &frame : frames)
    {
        if (frame.kind != ncf::frame::kind_t::publish)
        {
            continue;
        }

        for (auto const &signal : frame.signals)
        {
            if (status_management.response_error == signal.name)
            {
                found = true;
                break;
            }
        }

        if (found)
        {
            break;
        }
    }

    if (!found)
    {
        _log_error("Not defined", status_management.response_error);
        return;
    }

    _log_ok();
}

void fault_state_signals_t::run(
    const frames_t &frames,
    const ncf::status_management_t &status_management) const
{
    std::map< std::string, unsigned int > signals{};

    for (auto const &name : status_management.fault_state_signals)
    {
        signals[name] = 0;
    }

    for (auto const &frame : frames)
    {
        if (frame.kind != ncf::frame::kind_t::publish)
        {
            continue;
        }

        for (auto const &signal : frame.signals)
        {
            for (auto const &name : status_management.fault_state_signals)
            {
                if (signal.name == name)
                {
                    signals[name]++;
                }
            }
        }
    }

    std::vector< std::string > missing_signals{};
    std::vector< std::string > duplicate_signals{};
    for (auto const &entry : signals)
    {
        if (entry.second == 0)
        {
            missing_signals.push_back(entry.first);
        }
        else if (entry.second > 1)
        {
            duplicate_signals.push_back(entry.first);
        }
    }

    if (!missing_signals.empty())
    {
        _log_error("Not defined", _to_string(missing_signals));
        return;
    }

    if (!duplicate_signals.empty())
    {
        _log_error("Duplicate entry", _to_string(duplicate_signals));
        return;
    }

    _log_ok();
}

}    // namespace lin::ncf::validate::status_management
