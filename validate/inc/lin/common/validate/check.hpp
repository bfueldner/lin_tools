#pragma once

#include <array>
#include <charconv>
#include <map>
#include <optional>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

#include <lin/common/bitrate.hpp>
#include <lin/common/bnf.hpp>
#include <lin/common/signal_encoding.hpp>
#include <lin/common/validate/logger.hpp>
#include <lin/common/validate/version.hpp>

namespace lin::common::validate {

template < typename T, typename... U >
class check_t
{
  public:
    using result_t = common::validate::logger_t::result_t;

    check_t(common::validate::logger_t &logger, std::string name):
        _logger{ logger },
        _name{ std::move(name) }
    {
    }
    virtual ~check_t() = default;

    virtual void run(const U &...elements, const T &element) const = 0;

  protected:
    [[nodiscard]] std::string _to_string(unsigned long value) const
    {
        return std::to_string(value);
    };
    [[nodiscard]] std::string _to_string(int value) const { return std::to_string(value); };
    [[nodiscard]] std::string _to_string(double value) const
    {
        std::array< char, 16 > buffer{};
        auto result = std::to_chars(buffer.begin(), buffer.end(), value);
        return { buffer.data(), result.ptr };
    }
    [[nodiscard]] std::string _to_string(const common::bitrate::kbps_t &value) const
    {
        return _to_string(static_cast< common::bnf::real_or_integer_t >(value)) + " kbps";
    }
    [[nodiscard]] std::string _to_string(const std::string &value) const { return value; };
    template < typename V >
    [[nodiscard]] std::string _to_string(const std::vector< V > &value) const
    {
        std::stringstream stream{};
        for (auto iter = value.begin(); iter != value.end(); ++iter)
        {
            if (iter != value.begin())
            {
                stream << ", ";
            }
            stream << _to_string(*iter);
        }
        return stream.str();
    }

    void _log_ok() const { _log(result_t::ok, "", "", ""); }
    void _log_warning(
        const std::string &message,
        const std::string &value = {},
        const std::string &help  = {}) const
    {
        _log(result_t::warning, message, value, help);
    }
    void _log_error(
        const std::string &message,
        const std::string &value = {},
        const std::string &help  = {}) const
    {
        _log(result_t::error, message, value, help);
    }
    void _log(
        result_t result,
        const std::string &message,
        const std::string &value,
        const std::string &help) const
    {
        _logger.log(result, _name, message, value, help);
    }

  private:
    common::validate::logger_t
        &_logger;    // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
    std::string _name;
};

template < typename T, typename... U >
class check_language_version_t: public check_t< T, U... >
{
  public:
    check_language_version_t(common::validate::logger_t &logger, const std::string &name):
        check_t< T >{ logger, name }
    {
    }

    void run(const U &.../*unused*/, const T &element) const final
    {
        common::validate::version_t version{};

        try
        {
            version = common::validate::version::from_string(element.language_version);
        }
        catch (...)
        {
            check_t< T, U... >::_log_error(
                "Language version format invalid", element.language_version, "0..99).(0..99");
            return;
        }

        if (version.high == 1)
        {
            check_t< T, U... >::_log_warning(
                "Language version supported, but deprecated", element.language_version);
            return;
        }

        if ((version.high == 2) && (version.low <= 2))
        {
            check_t< T, U... >::_log_ok();
            return;
        }

        check_t< T, U... >::_log_error(
            "Language version not supported", element.language_version, "<= 2.2");
    }
};

template < typename T, typename... U >
class check_protocol_version_t: public check_t< T, U... >
{
  public:
    check_protocol_version_t(common::validate::logger_t &logger, const std::string &name):
        check_t< T, U... >{ logger, name }
    {
    }

    void run(const U &.../*unused*/, const T &element) const final
    {
        common::validate::version_t version{};

        try
        {
            version = common::validate::version::from_string(element.protocol_version);
        }
        catch (...)
        {
            check_t< T, U... >::_log_error(
                "Protocol version format invalid", element.protocol_version, "0..99).(0..99");
            return;
        }

        if ((version.high == 1) || ((version.high == 2) && (version.low <= 2)))
        {
            check_t< T, U... >::_log_ok();
            return;
        }

        check_t< T, U... >::_log_error(
            "Protocol version not supported", element.protocol_version, "<= 2.2");
    }
};

template < typename T, std::string T::*member_, size_t index_, typename... U >
class check_name_t: public common::validate::check_t< T, U... >
{
  public:
    check_name_t(common::validate::logger_t &logger, const std::string &name):
        common::validate::check_t< T, U... >{ logger, name }
    {
    }

    void run(const U &...args, const T &element) const final
    {
        std::tuple< U... > store(args...);
        auto list = std::get< index_ >(store);

        auto found{ false };

        for (auto const &entry : list)
        {
            if (entry.name == element.*member_)
            {
                found = true;
                break;
            }
        }

        if (!found)
        {
            common::validate::check_t< T, U... >::_log_error("Not defined", element.*member_);
            return;
        }

        common::validate::check_t< T, U... >::_log_ok();
    }
};

template < typename T, std::vector< std::string > T::*member_, size_t index_, typename... U >
class check_names_t: public common::validate::check_t< T, U... >
{
  public:
    check_names_t(common::validate::logger_t &logger, const std::string &name):
        common::validate::check_t< T, U... >{ logger, name }
    {
    }

    void run(const U &...args, const T &element) const final
    {
        std::tuple< U... > store(args...);
        auto list = std::get< index_ >(store);

        if ((element.*member_).empty())
        {
            common::validate::check_t< T, U... >::_log_warning("Empty");
            return;
        }

        std::map< std::string, unsigned int > present{};

        for (auto const &entry : list)
        {
            present[entry.name] = 0;
        }

        std::vector< std::string > missing{};

        for (auto const &name : element.*member_)
        {
            if (present.contains(name))
            {
                present[name]++;
            }
            else
            {
                missing.emplace_back(name);
            }
        }

        if (!missing.empty())
        {
            common::validate::check_t< T, U... >::_log_error(
                "Not defined", common::validate::check_t< T, U... >::_to_string(missing));
            return;
        }

        std::vector< std::string > duplicate{};

        for (auto const &entry : present)
        {
            if (entry.second > 1)
            {
                duplicate.push_back(entry.first);
            }
        }

        if (!duplicate.empty())
        {
            common::validate::check_t< T, U... >::_log_error(
                "Duplicate entry", common::validate::check_t< T, U... >::_to_string(duplicate));
            return;
        }

        common::validate::check_t< T, U... >::_log_ok();
    }
};

template < typename T, typename R, R T::*member_, auto min_, typename... U >
class check_min_t: public check_t< T, U... >
{
  public:
    check_min_t(common::validate::logger_t &logger, const std::string &name):
        check_t< T, U... >{ logger, name }
    {
    }

    void run(const U &.../*unused*/, const T &element) const final
    {
        if (element.*member_ <= min_)
        {
            check_t< T, U... >::_log_error(
                "Value too low",
                check_t< T, U... >::_to_string(element.*member_),
                "> " + check_t< T, U... >::_to_string(min_));
            return;
        }

        check_t< T, U... >::_log_ok();
    }
};

template < typename T, typename R, R T::*member_, auto min_, typename... U >
class check_min_equal_t: public check_t< T, U... >
{
  public:
    check_min_equal_t(common::validate::logger_t &logger, const std::string &name):
        check_t< T, U... >{ logger, name }
    {
    }

    void run(const U &.../*unused*/, const T &element) const final
    {
        if (element.*member_ < min_)
        {
            check_t< T, U... >::_log_error(
                "Value too low",
                check_t< T, U... >::_to_string(element.*member_),
                ">= " + check_t< T, U... >::_to_string(min_));
            return;
        }

        check_t< T, U... >::_log_ok();
    }
};

template < typename T, typename R, R T::*member_, auto min_, auto max_, typename... U >
class check_min_max_t: public check_t< T, U... >
{
  public:
    check_min_max_t(common::validate::logger_t &logger, const std::string &name):
        check_t< T, U... >{ logger, name }
    {
    }

    void run(const U &.../*unused*/, const T &element) const final
    {
        std::string const range{ check_t< T, U... >::_to_string(min_) + ".." +
                                 check_t< T, U... >::_to_string(max_) };
        if (element.*member_ < min_)
        {
            check_t< T, U... >::_log_error(
                "Value too low", check_t< T, U... >::_to_string(element.*member_), range);
            return;
        }

        if (element.*member_ > max_)
        {
            check_t< T, U... >::_log_error(
                "Value too high", check_t< T, U... >::_to_string(element.*member_), range);
            return;
        }

        check_t< T, U... >::_log_ok();
    }
};

template <
    typename T,
    typename R,
    std::vector< R > T::*member_,
    auto min_,
    auto max_,
    typename... U >
class check_vector_t: public check_t< T, U... >
{
  public:
    using vector_t = std::vector< R >;

    check_vector_t(common::validate::logger_t &logger, const std::string &name):
        check_t< T, U... >{ logger, name }
    {
    }

    void run(const U &.../*unused*/, const T &element) const final
    {
        std::string const range{ check_t< T, U... >::_to_string(min_) + ".." +
                                 check_t< T, U... >::_to_string(max_) };

        vector_t error_elements{};
        for (auto const &entry : element.*member_)
        {
            if ((entry < min_) || (entry > max_))
            {
                error_elements.push_back(entry);
            }
        }

        if (!error_elements.empty())
        {
            check_t< T, U... >::_log_error(
                "Member out of range", check_t< T, U... >::_to_string(error_elements), range);
            return;
        }

        R last{ 0 };
        error_elements.clear();
        for (auto const &entry : element.*member_)
        {
            if (last == entry)
            {
                error_elements.push_back(entry);
            }
            last = entry;
        }

        if (!error_elements.empty())
        {
            check_t< T, U... >::_log_error(
                "Member equal", check_t< T, U... >::_to_string(error_elements));
            return;
        }

        if (!std::is_sorted((element.*member_).begin(), (element.*member_).end()))
        {
            auto sorted_elements = element.*member_;
            std::sort(sorted_elements.begin(), sorted_elements.end());
            check_t< T, U... >::_log_warning(
                "Member order",
                check_t< T, U... >::_to_string(element.*member_),
                check_t< T, U... >::_to_string(sorted_elements));
            return;
        }

        check_t< T, U... >::_log_ok();
    }
};

template < typename T, typename R, std::optional< R > T::*member_, auto min_, typename... U >
class check_optional_min_t: public check_t< T, U... >
{
  public:
    check_optional_min_t(common::validate::logger_t &logger, const std::string &name):
        check_t< T, U... >{ logger, name }
    {
    }

    void run(const U &.../*unused*/, const T &element) const final
    {
        if (element.*member_)
        {
            // NOLINTBEGIN(bugprone-unchecked-optional-access)
            if ((element.*member_).value() < min_)
            {
                check_t< T, U... >::_log_error(
                    "Value too low",
                    check_t< T, U... >::_to_string((element.*member_).value()),
                    ">= " + check_t< T, U... >::_to_string(min_));
                return;
            }
            // NOLINTEND(bugprone-unchecked-optional-access)

            check_t< T, U... >::_log_ok();
        }
    }
};

template <
    typename T,
    typename R,
    std::optional< R > T::*member_,
    auto min_,
    auto max_,
    typename... U >
class check_optional_min_max_t: public check_t< T, U... >
{
  public:
    check_optional_min_max_t(common::validate::logger_t &logger, const std::string &name):
        check_t< T, U... >{ logger, name }
    {
    }

    void run(const U &.../*unused*/, const T &element) const final
    {
        if (element.*member_)
        {
            std::string const range{ check_t< T, U... >::_to_string(min_) + ".." +
                                     check_t< T, U... >::_to_string(max_) };

            // NOLINTBEGIN(bugprone-unchecked-optional-access)
            if ((element.*member_).value() < min_)
            {
                check_t< T, U... >::_log_error(
                    "Value too low",
                    check_t< T, U... >::_to_string((element.*member_).value()),
                    range);
                return;
            }
            // NOLINTEND(bugprone-unchecked-optional-access)

            // NOLINTBEGIN(bugprone-unchecked-optional-access)
            if ((element.*member_).value() > max_)
            {
                check_t< T, U... >::_log_error(
                    "Value too high",
                    check_t< T, U... >::_to_string((element.*member_).value()),
                    range);
                return;
            }
            // NOLINTEND(bugprone-unchecked-optional-access)

            check_t< T, U... >::_log_ok();
        }
    }
};

template < typename T, typename R, std::vector< R > T::*member_, typename... U >
class check_vector_name_t: public check_t< T, U... >
{
  public:
    check_vector_name_t(common::validate::logger_t &logger, const std::string &name):
        check_t< T, U... >{ logger, name }
    {
    }

    void run(const U &.../*unused*/, const T &element) const final
    {
        std::map< std::string, unsigned int > names{};    // NOLINT(misc-const-correctness)

        for (auto const &entry : element.*member_)
        {
            names[entry.name]++;
        }

        std::vector< std::string > error_names{};
        for (auto const &entry : names)
        {
            if (entry.second > 1)
            {
                error_names.push_back(entry.first);
            }
        }

        if (!error_names.empty())
        {
            check_t< T, U... >::_log_error(
                "Names not unique", check_t< T, U... >::_to_string(error_names));
            return;
        }

        check_t< T, U... >::_log_ok();
    }
};

template < typename T, common::bnf::integer_t T::*member_, common::bnf::integer_t min_ >
using check_int_min_t = check_min_t< T, common::bnf::integer_t, member_, min_ >;

template < typename T, common::bnf::integer_t T::*member_, common::bnf::integer_t min_ >
using check_int_min_equal_t = check_min_equal_t< T, common::bnf::integer_t, member_, min_ >;

template <
    typename T,
    common::bnf::integer_t T::*member_,
    common::bnf::integer_t min_,
    common::bnf::integer_t max_,
    typename... U >
using check_int_min_max_t = check_min_max_t< T, common::bnf::integer_t, member_, min_, max_, U... >;

template <
    typename T,
    std::vector< common::bnf::integer_t > T::*member_,
    common::bnf::integer_t min_,
    common::bnf::integer_t max_,
    typename... U >
using check_int_vector_t = check_vector_t< T, common::bnf::integer_t, member_, min_, max_, U... >;

template <
    typename T,
    std::vector< common::bnf::real_or_integer_t > T::*member_,
    common::bnf::integer_t min_,
    common::bnf::integer_t max_,
    typename... U >
using check_double_vector_t =
    check_vector_t< T, common::bnf::integer_t, member_, min_, max_, U... >;

template <
    typename T,
    std::optional< common::bnf::integer_t > T::*member_,
    common::bnf::integer_t min_,
    typename... U >
using check_optional_int_min_t =
    check_optional_min_t< T, common::bnf::integer_t, member_, min_, U... >;

template <
    typename T,
    std::optional< common::bnf::integer_t > T::*member_,
    common::bnf::integer_t min_,
    common::bnf::integer_t max_,
    typename... U >
using check_optional_int_min_max_t =
    check_optional_min_max_t< T, common::bnf::integer_t, member_, min_, max_, U... >;

template <
    typename T,
    std::optional< common::bnf::real_or_integer_t > T::*member_,
    common::bnf::integer_t min_,
    typename... U >
using check_optional_double_min_t =
    check_optional_min_t< T, common::bnf::real_or_integer_t, member_, min_, U... >;

namespace check {

using signal_encoding_t       = check_t< lin::common::signal::encoding_t >;
using signal_encoding_value_t = check_t< lin::common::signal::encoding::value_t >;

}    // namespace check

}    // namespace lin::common::validate
