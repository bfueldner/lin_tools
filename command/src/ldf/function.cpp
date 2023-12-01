#include <algorithm>
#include <cctype>
#include <csignal>
#include <cstddef>
#include <iostream>
#include <iterator>
#include <limits>
#include <string>
#include <type_traits>
#include <variant>

#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/trim.hpp>
#include <boost/spirit/home/x3.hpp>

#include <lin/ldf/frame_diagnostic.hpp>
#include <lin/ldf/frame_unconditional.hpp>
#include <lin/ldf/lin_description_file.hpp>
#include <lin/ldf/node_attribute.hpp>
#include <lin/ldf/node_composition.hpp>
#include <lin/ldf/parser/lin_description_file.hpp>
#include <lin/ldf/signal_diagnostic.hpp>
#include <lin/ldf/signal_encoding.hpp>
#include <lin/ldf/signal_group.hpp>
#include <lin/ldf/signal_representation.hpp>
#include <lin/ldf/signal_standard.hpp>

namespace lin::ldf::command::function {

bool parse(lin::ldf::lin_description_file_t &lin_description_file, std::string &text)
{
    auto position = text.begin();
    try
    {
        namespace x3 = boost::spirit::x3;

        auto result = phrase_parse(
            position,
            text.end(),
            lin::ldf::parser::lin_description_file,
            x3::ascii::space,
            lin_description_file);

        if (!result)
        {
            std::cerr << "No valid node capability file.\n";
            return false;
        }
    }
    catch (
        const boost::spirit::x3::expectation_failure< std::string::iterator > &expectation_failure)
    {
        /* Find position of expectation_failure */
        auto position = expectation_failure.where();
        if (position != text.begin())
        {
            position--;
        }

        /* Reverse back to last character */
        while (position != text.begin() && ((*position == ' ') || (*position == '\t') ||
                                            (*position == '\n') || (*position == '\r')))
        {
            position--;
        }

        size_t line = 1;
        std::remove_reference_t< decltype(text) >::iterator start{};
        for (auto iter = text.begin(); iter != position; ++iter)
        {
            if (*iter == '\n')
            {
                start = iter;
                line++;
            }
        }
        auto character  = std::distance(start, position);
        auto error_line = std::string{ start, expectation_failure.where() };
        boost::algorithm::trim(error_line);

        std::cerr << "Parsing error: Expected " << expectation_failure.which() << " after '"
                  << error_line << "' in line " << line << " at character " << character << "\n";
        return false;
    }
    return true;
}

void sort(lin_description_file_t &lin_description_file)
{
    /* Sort slaves nodes by name */
    std::sort(lin_description_file.nodes.slaves.begin(), lin_description_file.nodes.slaves.end());

    /* Sort node_attributes by name */
    std::sort(
        lin_description_file.node_attributes.begin(),
        lin_description_file.node_attributes.end(),
        [](lin::ldf::node::attribute_t &lhs, lin::ldf::node::attribute_t &rhs) {
            return lhs.name < rhs.name;
        });

    /* Sort node_attribute.fault_state_signals by name */
    for (auto &node_attribute : lin_description_file.node_attributes)
    {
        std::sort(
            node_attribute.fault_state_signals.begin(), node_attribute.fault_state_signals.end());
    }

    /* Sort node_compositions by name */
    std::sort(
        lin_description_file.node_compositions.begin(),
        lin_description_file.node_compositions.end(),
        [](lin::ldf::node::composition::configuration_t &lhs,
           lin::ldf::node::composition::configuration_t &rhs) { return lhs.name < rhs.name; });

    for (auto &configurations : lin_description_file.node_compositions)
    {
        /* Sort node_compositions.configuration by name */
        std::sort(
            configurations.composites.begin(),
            configurations.composites.end(),
            [](lin::ldf::node::composition::configuration::composite_t &lhs,
               lin::ldf::node::composition::configuration::composite_t &rhs) {
                return lhs.name < rhs.name;
            });

        /* Sort node_compositions.configuration.nodes by name */
        for (auto &composite : configurations.composites)
        {
            std::sort(composite.nodes.begin(), composite.nodes.end());
        }
    }

    /* Sort standard_signals by name */
    std::sort(
        lin_description_file.standard_signals.begin(),
        lin_description_file.standard_signals.end(),
        [](lin::ldf::signal::standard_t &lhs, lin::ldf::signal::standard_t &rhs) {
            return lhs.name < rhs.name;
        });

    /* Sort standard_signals.subscribed_by by name */
    for (auto &signal : lin_description_file.standard_signals)
    {
        std::sort(signal.subscribed_by.begin(), signal.subscribed_by.end());
    }

    /* Sort diagnostic_signals by name */
    std::sort(
        lin_description_file.diagnostic_signals.begin(),
        lin_description_file.diagnostic_signals.end(),
        [](lin::ldf::signal::diagnostic_t &lhs, lin::ldf::signal::diagnostic_t &rhs) {
            return lhs.name < rhs.name;
        });

    /* Sort signal_groups by name */
    std::sort(
        lin_description_file.signal_groups.begin(),
        lin_description_file.signal_groups.end(),
        [](lin::ldf::signal::group_t &lhs, lin::ldf::signal::group_t &rhs) {
            return lhs.name < rhs.name;
        });

    /* Sort signal_groups.signals by offset */
    for (auto &signal_group : lin_description_file.signal_groups)
    {
        std::sort(
            signal_group.signals.begin(),
            signal_group.signals.end(),
            [](lin::ldf::signal::group::signal_t &lhs, lin::ldf::signal::group::signal_t &rhs) {
                return lhs.offset < rhs.offset;
            });
    }

    /* Sort unconditional_frames.signals by offset */
    for (auto &frame : lin_description_file.unconditional_frames)
    {
        std::sort(
            frame.signals.begin(),
            frame.signals.end(),
            [](lin::ldf::frame::unconditional::signal_t &lhs,
               lin::ldf::frame::unconditional::signal_t &rhs) { return lhs.offset < rhs.offset; });
    }

    /* Sort diagnostic_frames.signals by offset */
    for (auto &frame : lin_description_file.diagnostic_frames)
    {
        std::sort(
            frame.signals.begin(),
            frame.signals.end(),
            [](lin::ldf::frame::diagnostic::signal_t &lhs,
               lin::ldf::frame::diagnostic::signal_t &rhs) { return lhs.offset < rhs.offset; });
    }

    /* Sort signal_encodings by name */
    std::sort(
        lin_description_file.signal_encodings.begin(),
        lin_description_file.signal_encodings.end(),
        [](lin::ldf::signal::encoding_t &lhs, lin::ldf::signal::encoding_t &rhs) {
            return lhs.name < rhs.name;
        });

    auto get_offset = [](auto &&arg) {
        using T = std::decay_t< decltype(arg) >;
        if constexpr (std::is_same_v< T, lin::ldf::signal::encoding::logical_value_t >)
        {
            return arg.value;
        }
        else if constexpr (std::is_same_v< T, lin::ldf::signal::encoding::physical_range_t >)
        {
            return arg.min;
        }
        else if constexpr (std::is_same_v< T, lin::ldf::signal::encoding::ascii_value_t >)
        {
            return std::numeric_limits< int >::min();
        }
        else if constexpr (std::is_same_v< T, lin::ldf::signal::encoding::bcd_value_t >)
        {
            return std::numeric_limits< int >::min() + 1;
        }
        return 0;
    };

    /* Sort signal_encoding by min/value */
    for (auto &signal_encoding : lin_description_file.signal_encodings)
    {
        std::sort(
            signal_encoding.values.begin(),
            signal_encoding.values.end(),
            [&get_offset](
                lin::ldf::signal::encoding::value_t &a, lin::ldf::signal::encoding::value_t &b) {
                return std::visit(get_offset, a) < std::visit(get_offset, b);
            });
    }

    /* Sort signal_representations by name */
    std::sort(
        lin_description_file.signal_representations.begin(),
        lin_description_file.signal_representations.end(),
        [](lin::ldf::signal::representation_t &lhs, lin::ldf::signal::representation_t &rhs) {
            return lhs.name < rhs.name;
        });

    /* Sort signal_representation.signals by name */
    for (auto &signal_representation : lin_description_file.signal_representations)
    {
        std::sort(signal_representation.signals.begin(), signal_representation.signals.end());
    }
}

}    // namespace lin::ldf::command::function
