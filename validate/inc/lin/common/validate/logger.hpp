#pragma once

#include <cstdint>
#include <string>
#include <vector>

namespace lin::common::validate {

class logger_t
{
  public:
    enum class result_t : std::uint8_t
    {
        ok,
        warning,
        error,
    };

    explicit logger_t(bool symbol, bool verbose):
        _symbol{ symbol },
        _verbose{ verbose }
    {
    }

    void log(
        result_t result,
        const std::string &name,
        const std::string &message,
        const std::string &value,
        const std::string &help);

    void push_section(const std::string &section, const std::string &name = {});
    void pop_section()
    {
        if (!_sections.empty())
        {
            _sections.pop_back();
        }
    }

    [[nodiscard]] unsigned int warnings() const { return _warnings; }
    [[nodiscard]] unsigned int errors() const { return _errors; }

  private:
    bool _symbol;
    bool _verbose;
    unsigned int _warnings{};
    unsigned int _errors{};
    std::vector< std::string > _sections{};
};

}    // namespace lin::common::validate
