#include <string>
#include <variant>
#include <vector>

#include <lin/ncf/diagnostic.hpp>
#include <lin/ncf/validate/diagnostic.hpp>

/* 8.2.4 Diagnostic definition */

namespace lin::ncf::validate::diagnostic {

void nad_t::run(const ncf::diagnostic_t &diagnostic) const
{
    std::visit([this](auto &&arg) { run(arg); }, diagnostic.nad);
}

void nad_t::run(const ncf::diagnostic::nad::range_t &nad_range) const
{
    if (nad_range.begin < min)
    {
        _log_error("Minimum value too low", _to_string(nad_range.begin), _range);
        return;
    }

    if (nad_range.end > max)
    {
        _log_error("Maximum value too high", _to_string(nad_range.end), _range);
        return;
    }

    if (nad_range.begin >= nad_range.end)
    {
        _log_error(
            "Range invalid",
            _to_string(nad_range.begin) + ".." + _to_string(nad_range.end),
            _range + " < " + _range);
        return;
    }

    _log_ok();
}

void nad_t::run(const ncf::diagnostic::nad::sequence_t &nad_sequence) const
{
    // NOLINTNEXTLINE(cppcoreguidelines-pro-type-const-cast)
    *const_cast< std::vector< int > * >(&_sequence) = nad_sequence;
    _nad_sequence_check.run(*this);
}

}    // namespace lin::ncf::validate::diagnostic
