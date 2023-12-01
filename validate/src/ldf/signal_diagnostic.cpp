#include <cmath>
#include <string>
#include <variant>

#include <lin/ldf/signal_diagnostic.hpp>
#include <lin/ldf/validate/signal_diagnostic.hpp>

/* 9.2.3.2 Diagnostic signals */

namespace lin::ldf::validate::signal::diagnostic {

void size_t::run(const ldf::signal::diagnostic_t &signal) const
{
    if (signal.size != 8)
    {
        _log_error("Size must be fixed to 8", _to_string(signal.size));
        return;
    }

    _log_ok();
}

void init_value_t::run(const ldf::signal::diagnostic_t &signal) const
{
    if (const auto *init_value =
            std::get_if< ldf::signal::diagnostic::init_value::scalar_t >(&signal.init_value))
    {
        if (*init_value != 0)
        {
            _log_error("Scalar init value must be zero", _to_string(*init_value));
            return;
        }
    }

    if (std::get_if< ldf::signal::diagnostic::init_value::array_t >(&signal.init_value) != nullptr)
    {
        _log_error("Array init value not allowed");
        return;
    }

    _log_ok();
}

}    // namespace lin::ldf::validate::signal::diagnostic
