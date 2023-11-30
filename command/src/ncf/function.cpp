#include <algorithm>
#include <cctype>
#include <csignal>
#include <cstddef>
#include <filesystem>
#include <fstream>
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

#include <lin/common/command/type.hpp>
#include <lin/common/command/type_io.hpp>
#include <lin/common/generator/indention.hpp>
#include <lin/ncf/command/function.hpp>
#include <lin/ncf/diagnostic.hpp>
#include <lin/ncf/frame.hpp>
#include <lin/ncf/general.hpp>
#include <lin/ncf/node.hpp>
#include <lin/ncf/node_capability_file.hpp>
#include <lin/ncf/parser/node_capability_file.hpp>
#include <lin/ncf/signal.hpp>
#include <lin/ncf/signal_encoding.hpp>

#include <version.hpp>

namespace lin::ncf::command::function {

bool parse(lin::ncf::node_capability_file_t &node_capability_file, std::string &text)
{
    auto position = text.begin();
    try
    {
        namespace x3 = boost::spirit::x3;

        auto result = phrase_parse(
            position,
            text.end(),
            lin::ncf::parser::node_capability_file,
            x3::ascii::space,
            node_capability_file);

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

void sort(node_capability_file_t &node_capability_file)
{
    /* Sort nodes by name */
    std::sort(
        node_capability_file.nodes.begin(),
        node_capability_file.nodes.end(),
        [](lin::ncf::node_t &a, lin::ncf::node_t &b) { return a.name < b.name; });

    /* Sort frames by name */
    for (auto &node : node_capability_file.nodes)
    {
        /* Sort baudrate sequence */
        if (auto *bitrate =
                std::get_if< lin::ncf::general::bitrate::select_t >(&node.general.bitrate))
        {
            std::sort(bitrate->begin(), bitrate->end());
        }

        /* Sort diagnostic NAD sequence */
        if (auto *nad = std::get_if< lin::ncf::diagnostic::nad::sequence_t >(&node.diagnostic.nad))
        {
            std::sort(nad->begin(), nad->end());
        }

        /* Sort diagnostic SID sequence */
        std::sort(node.diagnostic.support_sids.begin(), node.diagnostic.support_sids.end());

        for (auto &frame : node.frames)
        {
            /* Sort signals by offset */
            std::sort(
                frame.signals.begin(),
                frame.signals.end(),
                [](lin::ncf::signal_t &a, lin::ncf::signal_t &b) { return a.offset < b.offset; });
        }

        /* Sort encoding by name */
        std::sort(
            node.signal_encodings.begin(),
            node.signal_encodings.end(),
            [](lin::ncf::signal::encoding_t &a, lin::ncf::signal::encoding_t &b) {
                return a.name < b.name;
            });

        auto get_offset = [](auto &&arg) {
            using T = std::decay_t< decltype(arg) >;
            if constexpr (std::is_same_v< T, lin::ncf::signal::encoding::logical_value_t >)
            {
                return arg.value;
            }
            else if constexpr (std::is_same_v< T, lin::ncf::signal::encoding::physical_range_t >)
            {
                return arg.min;
            }
            else if constexpr (std::is_same_v< T, lin::ncf::signal::encoding::ascii_value_t >)
            {
                return std::numeric_limits< int >::min();
            }
            else if constexpr (std::is_same_v< T, lin::ncf::signal::encoding::bcd_value_t >)
            {
                return std::numeric_limits< int >::min() + 1;
            }
            return 0;
        };

        for (auto &signal_encoding : node.signal_encodings)
        {
            std::sort(
                signal_encoding.values.begin(),
                signal_encoding.values.end(),
                [&get_offset](
                    lin::ncf::signal::encoding::value_t &a,
                    lin::ncf::signal::encoding::value_t &b) {
                    return std::visit(get_offset, a) < std::visit(get_offset, b);
                });
        }
    }
}


std::string bits_to_type(unsigned int value)
{
    if (value <= 8)
    {
        return "std::uint8_t";
    }

    if (value <= 16)
    {
        return "std::uint16_t";
    }

    if (value <= 32)
    {
        return "std::uint32_t";
    }

    return "std::uint64_t";
}

void export_encoding(node_t *node, std::ostream &out, bool verbose)
{
    for (auto &signal_encoding : node->signal_encodings)
    {
        int size          = 0;
        int min           = std::numeric_limits< int >::max();
        int max           = std::numeric_limits< int >::min();
        bool has_logical  = false;
        bool has_physical = false;
        for (auto const &value : signal_encoding.values)
        {
            if (auto const *logical_value =
                    std::get_if< lin::ncf::signal::encoding::logical_value_t >(&value))
            {
                size = std::max(size, logical_value->value);

                has_logical = true;
            }
            else if (
                auto const *physical_range =
                    std::get_if< lin::ncf::signal::encoding::physical_range_t >(&value))
            {
                min = std::min(min, physical_range->min);
                max = std::max(max, physical_range->max);

                has_physical = true;
            }
        }

        auto encoding_name = signal_encoding.name;
        std::transform(
            encoding_name.begin(),
            encoding_name.end(),
            encoding_name.begin(),
            [](unsigned char ch) { return std::tolower(ch); });

        if (verbose)
        {
            std::cerr << "Export encoding " << encoding_name << "_t\n";
        }

        out << "/* Encoding " << signal_encoding.name << " */\n";
        if (has_logical)
        {
            out << "enum class " << encoding_name << "_t : " << bits_to_type(size) << '\n';
            out << "{\n" << common::indention_t::push;
            for (auto const &value : signal_encoding.values)
            {
                if (auto const *logical_value =
                        std::get_if< lin::ncf::signal::encoding::logical_value_t >(&value))
                {
                    auto value_name = logical_value->text_info;
                    std::transform(
                        value_name.begin(),
                        value_name.end(),
                        value_name.begin(),
                        [](unsigned char ch) { return std::tolower(ch); });
                    boost::replace_all(value_name, " ", "_");
                    out << common::indention_t::indent << value_name << " = "
                        << logical_value->value << ",\n";
                }
            }
            out << common::indention_t::pop << "};\n\n";
        }

        if (has_physical)
        {
            out << "// pysical_t " << min << ", " << max << "\n\n";
        }
    }
}

void export_frame(node_t *node, std::ostream &out, bool verbose)
{
    for (auto &frame : node->frames)
    {
        auto frame_name = frame.name;
        std::transform(
            frame_name.begin(), frame_name.end(), frame_name.begin(), [](unsigned char ch) {
                return std::tolower(ch);
            });

        if (verbose)
        {
            std::cerr << "Export frame " << frame_name << "_t\n";
        }

        out << "/* Frame " << frame.name << " */\n";
        out << "struct " << frame_name << "_t\n";
        out << "{\n" << common::indention_t::push;

        std::string const base = bits_to_type(frame.size * 8);

        int offset = 0;
        int index  = 1;
        for (auto const &signal : frame.signals)
        {
            if (signal.offset > offset)
            {
                out << common::indention_t::indent << base << " _" << index << " : "
                    << (signal.offset - offset) << ";\n";
                index++;
            }
            out << common::indention_t::indent << base << " " << signal.name << " : " << signal.size
                << ";\n";
            offset = signal.offset + signal.size;
        }

        out << common::indention_t::pop << "};\n";
        out << "static_assert(sizeof(" << frame_name << "_t) == " << frame.size << ");\n\n";
    }
}

bool export_(
    node_t *node,
    common::command::export_type_t type,
    const std::string &namespace_,    // NOLINT(readability-identifier-naming)
    std::filesystem::path &output,
    unsigned int indent,
    bool verbose)
{
    std::ofstream out(output, std::ofstream::out);
    if (out.fail())
    {
        std::cerr << "Error writing to " << output << "\n.";
        return false;
    }

    if (verbose)
    {
        std::cerr << "Export " << type << "(s) for node '" << node->name << "'\n";
    }

    out << common::indention_width_t(indent);
    out << "/*\n";
    out << " * " << type << "(s) for node '" << node->name << "'\n";
    out << " * Automatic generated file by ncf_tool " << version::string << "\n";
    out << " */\n";
    out << "#pragma once\n\n";

    if (!namespace_.empty())
    {
        out << "namespace " << namespace_ << " {\n\n";
    }

    switch (type)
    {
        case lin::common::command::export_type_t::frame:
        {
            export_encoding(node, out, verbose);
            export_frame(node, out, verbose);
            break;
        }

        case lin::common::command::export_type_t::signal:
        {
            break;
        }
    }

    if (!namespace_.empty())
    {
        out << "}    // namespace " << namespace_ << "\n\n";
    }

    if (verbose)
    {
        std::cerr << "Exported content written to " << output << ".\n";
    }
    return true;
}

}    // namespace lin::ncf::command::function
