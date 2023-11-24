#include <algorithm>
#include <cctype>
#include <filesystem>
#include <fstream>
#include <ios>
#include <iostream>
#include <limits>
#include <sstream>
#include <string>
#include <variant>

#include <boost/algorithm/string/replace.hpp>

#include <lin/ncf/command/type.hpp>
#include <lin/ncf/command/type_io.hpp>
#include <lin/ncf/node.hpp>
#include <lin/ncf/node_capability_file.hpp>
#include <lin/ncf/signal.hpp>

#include <lin/common/generator/indention.hpp>

#include <lin/ncf/generator/node_capability_file.hpp>

#include <lin/ncf/command/function.hpp>

#include <version.hpp>

namespace lin::ncf::command {

bool validate(node_capability_file_t & /*file*/, bool /*verbose*/)
{
    return false;
}

bool prettify(
    node_capability_file_t &node_capability_file,
    unsigned int indent,
    std::filesystem::path &output,
    bool verbose)
{
    std::stringstream stream{};
    stream << lin::common::indention_width_t{ static_cast< unsigned int >(indent) };
    stream << std::uppercase << node_capability_file;

    std::ofstream out(output, std::ofstream::out);
    if (out.fail())
    {
        std::cerr << "Error writing to " << output << "\n.";
        return false;
    }

    out << stream.str();
    if (verbose)
    {
        std::cerr << "Prettified content written to " << output << ".\n";
    }
    return true;
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
    for (auto &encoding : node->encodings)
    {
        int size          = 0;
        int min           = std::numeric_limits< int >::max();
        int max           = std::numeric_limits< int >::min();
        bool has_logical  = false;
        bool has_physical = false;
        for (auto const &value : encoding.value)
        {
            if (auto const *logical_value =
                    std::get_if< lin::ncf::signal_encoding_type::logical_value_t >(&value))
            {
                size = std::max(size, logical_value->signal_value);

                has_logical = true;
            }
            else if (
                auto const *physical_range =
                    std::get_if< lin::ncf::signal_encoding_type::physical_range_t >(&value))
            {
                min = std::min(min, physical_range->min_value);
                max = std::max(max, physical_range->max_value);

                has_physical = true;
            }
        }

        auto encoding_name = encoding.encoding_name;
        std::transform(
            encoding_name.begin(),
            encoding_name.end(),
            encoding_name.begin(),
            [](unsigned char ch) { return std::tolower(ch); });

        if (verbose)
        {
            std::cerr << "Export encoding " << encoding_name << "_t\n";
        }

        out << "/* Encoding " << encoding.encoding_name << " */\n";
        if (has_logical)
        {
            out << "enum class " << encoding_name << "_t : " << bits_to_type(size) << '\n';
            out << "{\n" << common::indention_t::push;
            for (auto const &value : encoding.value)
            {
                if (auto const *logical_value =
                        std::get_if< lin::ncf::signal_encoding_type::logical_value_t >(&value))
                {
                    auto value_name = logical_value->text_info;
                    std::transform(
                        value_name.begin(),
                        value_name.end(),
                        value_name.begin(),
                        [](unsigned char ch) { return std::tolower(ch); });
                    boost::replace_all(value_name, " ", "_");
                    out << common::indention_t::indent << value_name << " = "
                        << logical_value->signal_value << ",\n";
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
        auto frame_name = frame.frame_name;
        std::transform(
            frame_name.begin(), frame_name.end(), frame_name.begin(), [](unsigned char ch) {
                return std::tolower(ch);
            });

        if (verbose)
        {
            std::cerr << "Export frame " << frame_name << "_t\n";
        }

        out << "/* Frame " << frame.frame_name << " */\n";
        out << "struct " << frame_name << "_t\n";
        out << "{\n" << common::indention_t::push;

        std::string const base = bits_to_type(frame.frame_properties.length * 8);

        int offset = 0;
        int index  = 1;
        for (auto const &signal : frame.signal_definition)
        {
            if (signal.signal_properties.offset > offset)
            {
                out << common::indention_t::indent << base << " _" << index << " : "
                    << (signal.signal_properties.offset - offset) << ";\n";
                index++;
            }
            out << common::indention_t::indent << base << " " << signal.signal_name << " : "
                << signal.signal_properties.size << ";\n";
            offset = signal.signal_properties.offset + signal.signal_properties.size;
        }

        out << common::indention_t::pop << "};\n";
        out << "static_assert(sizeof(" << frame_name << "_t) == " << frame.frame_properties.length
            << ");\n\n";
    }
}

bool export_(
    node_t *node,
    lin::ncf::command::type_t type,
    const std::string &namespace_,    // NOLINT(readability-identifier-naming)
    unsigned int indent,
    std::filesystem::path &output,
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
        std::cerr << "Export " << type << "(s) for node '" << node->node_name << "'\n";
    }

    out << common::indention_width_t(indent);
    out << "/*\n";
    out << " * " << type << "(s) for node '" << node->node_name << "'\n";
    out << " * Automatic generated file by ncf_tool " << version::string << "\n";
    out << " */\n";
    out << "#pragma once\n\n";

    if (!namespace_.empty())
    {
        out << "namespace " << namespace_ << " {\n\n";
    }

    switch (type)
    {
        case lin::ncf::command::type_t::frame:
        {
            export_encoding(node, out, verbose);
            export_frame(node, out, verbose);
            break;
        }

        case type_t::signal:
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

}    // namespace lin::ncf::command
