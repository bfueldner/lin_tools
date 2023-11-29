#pragma once

#include <algorithm>
#include <vector>

#include <lin/common/validate/check.hpp>
#include <lin/ldf/frame_diagnostic.hpp>
#include <lin/ldf/frame_event_triggered.hpp>
#include <lin/ldf/frame_sporadic.hpp>
#include <lin/ldf/frame_unconditional.hpp>
#include <lin/ldf/lin_description_file.hpp>
#include <lin/ldf/node_attribute.hpp>
#include <lin/ldf/node_composition.hpp>
#include <lin/ldf/nodes.hpp>
#include <lin/ldf/schedule_table.hpp>
#include <lin/ldf/signal_diagnostic.hpp>
#include <lin/ldf/signal_encoding.hpp>
#include <lin/ldf/signal_group.hpp>
#include <lin/ldf/signal_representation.hpp>
#include <lin/ldf/signal_standard.hpp>

namespace lin::ldf::validate {

template < typename T, std::string T::*member_, typename... U >
class check_node_name_t: public common::validate::check_t< T, U... >
{
  public:
    check_node_name_t(common::validate::logger_t &logger, const std::string &name):
        common::validate::check_t< T, U... >{ logger, name }
    {
    }

    void run(const U &...args, const T &element) const final
    {
        std::tuple< U... > store(args...);
        auto nodes = std::get< ldf::nodes_t >(store);

        auto found{ false };

        if (nodes.master.name == element.*member_)
        {
            found = true;
        }
        else
        {
            for (auto const &slave : nodes.slaves)
            {
                if (slave == element.*member_)
                {
                    found = true;
                    break;
                }
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

template < typename T, std::vector< std::string > T::*member_, typename... U >
class check_node_names_t: public common::validate::check_t< T, U... >
{
  public:
    check_node_names_t(common::validate::logger_t &logger, const std::string &name):
        common::validate::check_t< T, U... >{ logger, name }
    {
    }

    void run(const U &...args, const T &element) const final
    {
        if ((element.*member_).empty())
        {
            common::validate::check_t< T, U... >::_log_warning("Empty");
            return;
        }

        std::tuple< U... > store(args...);
        auto nodes = std::get< ldf::nodes_t >(store);

        std::map< std::string, unsigned int > present{};

        present[nodes.master.name] = 0;
        for (auto const &slave : nodes.slaves)
        {
            present[slave] = 0;
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

template < typename T, typename R, std::vector< R > T::*member_, typename... U >
class check_offsets_t: public common::validate::check_t< T, U... >
{
  public:
    check_offsets_t(common::validate::logger_t &logger, const std::string &name):
        common::validate::check_t< T, U... >{ logger, name }
    {
    }

    void run(const U &.../*unused*/, const T &element) const final
    {
        if ((element.*member_).empty())
        {
            common::validate::check_t< T, U... >::_log_warning("Empty");
            return;
        }

        auto offset_compare = [](const R &lhs, const R &rhs) { return lhs.offset < rhs.offset; };

        if (!std::is_sorted((element.*member_).cbegin(), (element.*member_).cend(), offset_compare))
        {
            common::validate::check_t< T, U... >::_log_warning("Not sorted");
            return;
        }

        common::validate::check_t< T, U... >::_log_ok();
    }
};

namespace check {

using lin_description_file_t = common::validate::check_t< ldf::lin_description_file_t >;
using nodes_t                = common::validate::check_t< ldf::nodes_t >;
using node_attribute_t =
    common::validate::check_t< ldf::node::attribute_t, ldf::signal::standards_t >;
using node_composition_configuration_t =
    common::validate::check_t< ldf::node::composition::configuration_t >;
using node_composition_configuration_composite_t =
    common::validate::check_t< ldf::node::composition::configuration::composite_t, ldf::nodes_t >;
using standard_signal_t   = common::validate::check_t< ldf::signal::standard_t, ldf::nodes_t >;
using diagnostic_signal_t = common::validate::check_t< ldf::signal::diagnostic_t >;
using signal_group_t = common::validate::check_t< ldf::signal::group_t, ldf::signal::standards_t >;
using unconditional_frame_t = common::validate::
    check_t< ldf::frame::unconditional_t, ldf::nodes_t, ldf::signal::standards_t >;
using unconditional_frame_signal_t =
    common::validate::check_t< ldf::frame::unconditional::signal_t, ldf::signal::standards_t >;
using sporadic_frame_t =
    common::validate::check_t< ldf::frame::sporadic_t, ldf::frame::unconditionals_t >;
using event_triggered_frame_t = common::validate::
    check_t< ldf::frame::event_triggered_t, ldf::schedule_tables_t, ldf::frame::unconditionals_t >;
using diagnostic_frame_t = common::validate::check_t< ldf::frame::diagnostic_t >;
using diagnostic_frame_signal_t =
    common::validate::check_t< ldf::frame::diagnostic::signal_t, ldf::signal::diagnostics_t >;
using schedule_table_entry_t = common::validate::check_t<
    ldf::schedule_table::entry_t,
    ldf::nodes_t,
    ldf::frame::unconditionals_t,
    ldf::frame::sporadics_t,
    ldf::frame::event_triggereds_t >;
using signal_encoding_t = common::validate::
    check_t< ldf::signal::encoding_t, ldf::signal::standards_t, ldf::signal::representations_t >;
using signal_representation_t = common::validate::
    check_t< ldf::signal::representation_t, ldf::signal::encodings_t, ldf::signal::standards_t >;

}    // namespace check

}    // namespace lin::ldf::validate
