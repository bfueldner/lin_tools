#include <map>
#include <string>
#include <vector>

#include <lin/ncf/frame.hpp>
#include <lin/ncf/signal.hpp>
#include <lin/ncf/signal_encoding.hpp>
#include <lin/ncf/validate/signal_encoding.hpp>

/* 8.2.5.3 Signal encoding type definition */

namespace lin::ncf::validate::signal_encoding {

void usage_t::run(const ncf::frames_t &frames, const ncf::signal::encodings_t &signal_encodings)
    const
{
    std::map< std::string, unsigned int > usage{};
    std::map< std::string, unsigned int > missing{};

    for (auto const &encoding : signal_encodings)
    {
        usage[encoding.name] = 0;
    }

    for (auto const &frame : frames)
    {
        for (auto const &signal : frame.signals)
        {
            if (!signal.encoding.empty())
            {
                if (usage.contains(signal.encoding))
                {
                    usage[signal.encoding]++;
                }
                else
                {
                    missing[signal.encoding]++;
                }
            }
        }
    }

    std::vector< std::string > names{};
    for (auto const &entry : missing)
    {
        if (entry.second > 0)
        {
            names.push_back(entry.first);
        }
    }

    if (!names.empty())
    {
        _log_error("Not defined", _to_string(names));
        return;
    }

    for (auto const &entry : usage)
    {
        if (entry.second == 0)
        {
            names.push_back(entry.first);
        }
    }

    if (!names.empty())
    {
        _log_warning("Not used", _to_string(names));
        return;
    }

    _log_ok();
}

}    // namespace lin::ncf::validate::signal_encoding
