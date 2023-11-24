#include <iostream>
#include <string>

#include <lin/common/validate/logger.hpp>

namespace lin::common::validate {

void logger_t::log(
    result_t result,
    const std::string &name,
    const std::string &message,
    const std::string &value,
    const std::string &help)
{
    /* Skip output if unverbose and no warning/error */
    if (!_verbose && result == result_t::ok)
    {
        return;
    }

    if (_symbol)
    {
        switch (result)
        {
            default:
            case result_t::ok:
            {
                std::cout << "\u2705";
                break;
            }

            case result_t::warning:
            {
                std::cout << "\u2757";
                break;
            }

            case result_t::error:
            {
                std::cout << "\u274C";
                break;
            }
        }
        std::cout << ' ';
    }

    switch (result)
    {
        case result_t::warning:
        {
            _warnings++;
            break;
        }

        case result_t::error:
        {
            _errors++;
            break;
        }

        default:
        {
            break;
        }
    }

    for (auto const &section : _sections)
    {
        std::cout << section << '.';
    }

    std::cout << name;

    if (!message.empty())
    {
        std::cout << ": " << message;
    }

    if (!value.empty())
    {
        std::cout << " '" << value << '\'';
    }

    if (!help.empty())
    {
        std::cout << " (" << help << ')';
    }
    std::cout << '\n';
}

void logger_t::push_section(const std::string &section, const std::string &name)
{
    if (name.empty())
    {
        _sections.push_back(section);
    }
    else
    {
        _sections.push_back(section + '[' + name + ']');
    }
}

}    // namespace lin::common::validate
