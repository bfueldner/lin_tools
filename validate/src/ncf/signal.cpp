#include <cmath>
#include <string>
#include <variant>

#include <lin/ncf/signal.hpp>

#include <lin/ncf/validate/signal.hpp>

/* 8.2.5.2 Signal definition */

namespace lin::ncf::validate::signal {

void init_value_t::run(const ncf::signal_t &signal) const
{
    if (const auto *init_value =
            std::get_if< ncf::signal::init_value::scalar_t >(&signal.init_value))
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
            std::get_if< ncf::signal::init_value::array_t >(&signal.init_value))
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

void size_t::run(const ncf::signal_t &signal) const
{
    if (std::get_if< ncf::signal::init_value::scalar_t >(&signal.init_value) != nullptr)
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
            std::get_if< ncf::signal::init_value::array_t >(&signal.init_value))
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

void offset_t::run(const ncf::signal_t &signal) const
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

    if ((std::get_if< ncf::signal::init_value::array_t >(&signal.init_value) != nullptr) &&
        (signal.offset & 0x7) != 0)
    {
        _log_error(
            "Value not byte aligned", _to_string(signal.offset), _to_string(signal.offset & ~0x7));
        return;
    }

    _log_ok();
}

}    // namespace lin::ncf::validate::signal
