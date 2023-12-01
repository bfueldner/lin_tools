#include <string>

#include <lin/ldf/frame_diagnostic.hpp>
#include <lin/ldf/signal_diagnostic.hpp>
#include <lin/ldf/validate/frame_diagnostic.hpp>

/* 9.2.4.4 Diagnostic frames */

namespace lin::ldf::validate::frame::diagnostic::signal {

void offset_t::run(
    const ldf::signal::diagnostics_t & /*unused*/,
    const ldf::frame::diagnostic::signal_t &signal) const
{
    std::string const range{ _to_string(min) + ".." + _to_string(max) };

    if (signal.offset < min)
    {
        _log_error("Value too low", _to_string(signal.offset), range);
        return;
    }

    if (signal.offset > max)
    {
        _log_error("Value too high", _to_string(signal.offset), range);
        return;
    }

    if ((signal.offset & 0x7) != 0)
    {
        _log_error(
            "Value not byte aligned", _to_string(signal.offset), _to_string(signal.offset & ~0x7));
        return;
    }

    _log_ok();
}

}    // namespace lin::ldf::validate::frame::diagnostic::signal
