#include <cmath>
#include <string>
#include <variant>
#include <vector>

#include <lin/ldf/nodes.hpp>
#include <lin/ldf/signal_standard.hpp>
#include <lin/ldf/validate/signal_standard.hpp>

/* 9.2.3.1 Standard signals */

namespace lin::ldf::validate::signal::standard {

void size_t::run(const nodes_t & /*unused*/, const ldf::signal::standard_t &signal) const
{
    if (std::get_if< ldf::signal::standard::init_value::scalar_t >(&signal.init_value) != nullptr)
    {
        std::string const range{ _to_string(min) + ".." + _to_string(max) };

        if (signal.size < min)
        {
            _log_error("Value too low", _to_string(signal.size), range);
            return;
        }

        if (signal.size > max)
        {
            _log_error("Value too high", _to_string(signal.size), range);
            return;
        }
    }

    if (const auto *init_value =
            std::get_if< ldf::signal::standard::init_value::array_t >(&signal.init_value))
    {
        if (signal.size != static_cast< int >(init_value->size() * 8))
        {
            _log_error(
                "Value not byte aligned",
                _to_string(signal.size),
                _to_string(static_cast< int >(init_value->size() * 8)));
            return;
        }
    }

    _log_ok();
}

void init_value_t::run(const nodes_t & /*unused*/, const ldf::signal::standard_t &signal) const
{
    if (const auto *init_value =
            std::get_if< ldf::signal::standard::init_value::scalar_t >(&signal.init_value))
    {
        int const init_value_max = static_cast< int >(std::pow(2, signal.size) - 1);
        std::string const range{ "0.." + _to_string(init_value_max) };

        if (*init_value < 0)
        {
            _log_error("Scalar value too low", _to_string(*init_value), range);
            return;
        }

        if (*init_value > init_value_max)
        {
            _log_error("Scalar value too high", _to_string(*init_value), range);
            return;
        }
    }

    if (const auto *init_value =
            std::get_if< ldf::signal::standard::init_value::array_t >(&signal.init_value))
    {
        /* Check size first */
        if (static_cast< int >(init_value->size() * 8) != signal.size)
        {
            int const bytes = (signal.size + 7) / 8;
            auto help       = *init_value;
            help.resize(bytes);

            _log_error(
                "Number of array values mismatch signal size",
                _to_string(*init_value),
                _to_string(help));
            return;
        }
    }

    _log_ok();
}

}    // namespace lin::ldf::validate::signal::standard
