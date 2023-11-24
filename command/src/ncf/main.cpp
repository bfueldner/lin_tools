#include <algorithm>
#include <cstdint>
#include <cstdlib>
#include <exception>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <map>
#include <ostream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <tuple>
#include <type_traits>
#include <variant>
#include <vector>

#include <boost/algorithm/string.hpp>
#include <boost/program_options.hpp>
#include <boost/spirit/home/x3.hpp>

#include <version.hpp>

#include <lin/ncf/frame.hpp>
#include <lin/ncf/node.hpp>
#include <lin/ncf/node_capability_file.hpp>
#include <lin/ncf/signal.hpp>

#include <lin/ncf/parser/node_capability_file.hpp>

#include <lin/ncf/command/function.hpp>
#include <lin/ncf/command/type.hpp>
#include <lin/ncf/command/type_io.hpp>

#include <lin/common/signal_encoding_type.hpp>

using entry_t = std::tuple<
    std::string_view,
    const boost::program_options::options_description &,
    const boost::program_options::options_description & >;

// NOLINTBEGIN(readability-function-cognitive-complexity)
int main(const int argc, const char **argv)
{
    using namespace lin::ncf::command;

    const std::filesystem::path filename(
        argv[0]);    // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

    boost::program_options::options_description empty_options("Empty options");
    boost::program_options::positional_options_description const empty_positional_options{};


    /* Common positionals stuff */
    boost::program_options::options_description input_file_options;
    /* clang-format off */
    input_file_options.add_options()
        ("input-file", boost::program_options::value< std::filesystem::path >(), "Input file")
    ;
    /* clang-format on */

    boost::program_options::positional_options_description input_file_positional;
    input_file_positional.add("input-file", 1);


    /* Compress command */
    boost::program_options::options_description compress_options_help("Compress options");
    /* clang-format off */
    compress_options_help.add_options()
        ("binary", "Binary compression")
        ("text", "Text compression")
        ("output,o", boost::program_options::value< std::filesystem::path >(), "Output file")
    ;
    /* clang-format on */

    boost::program_options::options_description compress_options;
    compress_options.add(compress_options_help);    //.add(input_files_options);


    /* Extract command */
    boost::program_options::options_description export_options_help("Extract options");
    /* clang-format off */
    export_options_help.add_options()
        ("type,t", boost::program_options::value< type_t >(), "Type of export (frame, signal)")
        ("node", boost::program_options::value< std::string >(), "NCF node name")
        ("namespace,n", boost::program_options::value< std::string >(), "C++ namespace")
        ("indent,i", boost::program_options::value< unsigned int >()->default_value(4), "Indent characters")
        ("output,o", boost::program_options::value< std::filesystem::path >(), "Output file")
    ;
    /* clang-format on */

    boost::program_options::options_description export_options;
    export_options.add(export_options_help);


    /* Prettify command */
    boost::program_options::options_description prettify_options_help("Prettify options");
    /* clang-format off */
    prettify_options_help.add_options()
        ("indent,i", boost::program_options::value< unsigned int >()->default_value(4), "Indent characters")
        ("output,o", boost::program_options::value< std::filesystem::path >(), "Output file")
    ;
    /* clang-format on */

    boost::program_options::options_description prettify_options;
    prettify_options.add(prettify_options_help);


    /* Command map */
    const std::map< command_t, entry_t > commands{
        /* clang-format off */
        { command_t::export_,  { "Export file", export_options, export_options_help } },
        { command_t::validate, { "Validate file", empty_options, empty_options } },
        { command_t::prettify, { "Generate prettified file", prettify_options, prettify_options_help } },
        /* clang-format on */
    };

    std::cout << "NCF tool " << version::string << '\n';
    try
    {
        /* Generic */
        boost::program_options::options_description generic_options("Generic options");
        /* clang-format off */
        generic_options.add_options()
            ("help,h", "Show help text")
            ("verbose,v", "Verbose output")
        ;
        /* clang-format on */

        command_t command{};
        std::vector< std::string > subargs{};
        boost::program_options::options_description command_options("Command options");
        /* clang-format off */
        command_options.add_options()
            ("command", boost::program_options::value< command_t >(&command), "Subcommand")
            ("input-file", boost::program_options::value< std::filesystem::path >(), "Input file")
            ("subargs", boost::program_options::value< std::vector<std::string> >(&subargs), "Arguments for subcommand")
        ;
        /* clang-format on */

        boost::program_options::options_description all_options("All options");
        all_options.add(generic_options).add(command_options);

        boost::program_options::positional_options_description positional_options;
        positional_options.add("command", 1).add("input-file", 1).add("subargs", -1);

        boost::program_options::variables_map variables_map;
        auto command_line_parser = boost::program_options::command_line_parser(argc, argv)
                                       .options(all_options)
                                       .positional(positional_options)
                                       .allow_unregistered()
                                       .run();
        boost::program_options::store(command_line_parser, variables_map);
        boost::program_options::notify(variables_map);

        /* Display general help */
        if ((variables_map.count("help") > 0) && (variables_map.count("command") == 0))
        {
            std::cout << "Usage:\n  " << filename.filename().string()
                      << " <command> [options] <input-file>\n\n";

            std::cout << "Commands:\n";
            for (const auto &[key, entry] : commands)
            {
                std::cout << "  " << std::left
                          << std::setw(
                                 static_cast< int >(generic_options.get_option_column_width()) - 2)
                          << key << std::get< std::string_view >(entry) << '\n';
            }
            std::cout << '\n';

            std::cout << generic_options << '\n';

            std::cout << "To get help for a specific command:\n";
            std::cout << "  " << filename.filename().string() << " <command> --help\n\n";
            return EXIT_SUCCESS;
        }

        /* Extract command */
        if (variables_map.count("command") == 0)
        {
            throw boost::program_options::required_option("command");
        }
        auto subcommand = commands.at(command);

        std::vector< std::string > options = boost::program_options::collect_unrecognized(
            command_line_parser.options, boost::program_options::include_positional);
        options.erase(options.begin());

        boost::program_options::store(
            boost::program_options::command_line_parser(options)
                .options(std::get< 1 >(subcommand))
                .run(),
            variables_map);
        boost::program_options::notify(variables_map);

        /* Display command help */
        if (variables_map.count("help") > 0)
        {
            std::cout << "Usage:\n";
            std::cout << "  " << filename.filename().string() << " " << command
                      << " [options] <input-file>\n\n";

            std::cout << generic_options << '\n';

            auto options = std::get< 2 >(subcommand);
            if (!options.options().empty())
            {
                std::cout << options << '\n';
            }

            return EXIT_SUCCESS;
        }

        /* Extract general options/parameters */
        const bool verbose = variables_map.count("verbose") > 0;
        if (variables_map.count("input-file") == 0)
        {
            throw boost::program_options::required_option("input-file");
        }
        auto input_file = variables_map["input-file"].as< std::filesystem::path >();

        /* Parse given input file as NCF */

        //using namespace lin::ncf;
        lin::ncf::node_capability_file_t node_capability_file{};

        std::ifstream input(input_file, std::ifstream::in);
        if (input.fail())
        {
            std::cerr << "Can not open " << input_file << " for reading.\n";
            return EXIT_FAILURE;
        }

        std::string text(std::istreambuf_iterator< char >{ input }, {});
        auto position = text.begin();
        try
        {
            namespace x3 = boost::spirit::x3;

            auto result = phrase_parse(
                position,
                text.end(),
                lin::ncf::parser::node_capability_file_definition,
                x3::ascii::space,
                node_capability_file);

            if (!result)
            {
                std::cerr << "No valid node capability file.\n";
                return EXIT_FAILURE;
            }
        }
        catch (const boost::spirit::x3::expectation_failure< std::string::iterator >
                   &expectation_failure)
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
            decltype(text)::iterator start{};
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
                      << error_line << "' in line " << line << " at character " << character
                      << "\n";
            return EXIT_FAILURE;
        }

        /* TODO: Sort baudrate sequence */
        /* TODO: Sort diagnostic NAD sequence */
        /* TODO: Sort SID sequence */

        /* Sort nodes by name */
        std::sort(
            node_capability_file.node.begin(),
            node_capability_file.node.end(),
            [](lin::ncf::node_t &a, lin::ncf::node_t &b) { return a.node_name < b.node_name; });

        /* Sort frames by name */
        for (auto &node : node_capability_file.node)
        {
            std::sort(
                node.frames.begin(),
                node.frames.end(),
                [](lin::ncf::frame::single_frame_t &a, lin::ncf::frame::single_frame_t &b) {
                    if (static_cast< uint8_t >(a.frame_kind) < static_cast< uint8_t >(b.frame_kind))
                    {
                        return true;
                    }
                    return a.frame_name < b.frame_name;
                });

            for (auto &frame : node.frames)
            {
                /* Sort signals by offset */
                std::sort(
                    frame.signal_definition.begin(),
                    frame.signal_definition.end(),
                    [](lin::ncf::signal_t &a, lin::ncf::signal_t &b) {
                        return a.signal_properties.offset < b.signal_properties.offset;
                    });
            }

            /* Sort encoding by name */
            std::sort(
                node.encodings.begin(),
                node.encodings.end(),
                [](lin::ncf::signal_encoding_type::encoding_t &a,
                   lin::ncf::signal_encoding_type::encoding_t &b) {
                    return a.encoding_name < b.encoding_name;
                });

            auto get_offset = [](auto &&arg) {
                using T = std::decay_t< decltype(arg) >;
                if constexpr (std::is_same_v< T, lin::ncf::signal_encoding_type::logical_value_t >)
                {
                    return arg.signal_value;
                }
                else if constexpr (std::is_same_v<
                                       T,
                                       lin::ncf::signal_encoding_type::physical_range_t >)
                {
                    return arg.min_value;
                }
                else if constexpr (std::is_same_v<
                                       T,
                                       lin::ncf::signal_encoding_type::ascii_value_t >)
                {
                    return std::numeric_limits< int >::min();
                }
                else if constexpr (std::is_same_v< T, lin::ncf::signal_encoding_type::bcd_value_t >)
                {
                    return std::numeric_limits< int >::min() + 1;
                }
                return 0;
            };

            for (auto &encoding : node.encodings)
            {
                std::sort(
                    encoding.value.begin(),
                    encoding.value.end(),
                    [&get_offset](
                        lin::common::signal_encoding_type::value_t &a,
                        lin::common::signal_encoding_type::value_t &b) {
                        return std::visit(get_offset, a) < std::visit(get_offset, b);
                    });
            }
        }


        /* Subcommands */
        bool result = false;
        switch (command)
        {
            case command_t::validate:
            {
                result = lin::ncf::command::validate(node_capability_file, verbose);
                break;
            }

            case command_t::prettify:
            {
                if (variables_map.count("output") == 0)
                {
                    throw boost::program_options::required_option("output");
                }

                auto indent      = variables_map["indent"].as< unsigned int >();
                auto output_file = variables_map["output"].as< std::filesystem::path >();

                result =
                    lin::ncf::command::prettify(node_capability_file, indent, output_file, verbose);
                break;
            }

            case command_t::export_:
            {
                if (node_capability_file.node.empty())
                {
                    throw std::out_of_range("No nodes in NCF file.");
                }

                if ((node_capability_file.node.size() > 1) && (variables_map.count("node") == 0))
                {
                    throw std::runtime_error("Multiple nodes in NCF file, but none specified.");
                }

                if (variables_map.count("type") == 0)
                {
                    throw boost::program_options::required_option("type");
                }

                if (variables_map.count("output") == 0)
                {
                    throw boost::program_options::required_option("output");
                }

                std::string namespace_{};    // NOLINT(readability-identifier-naming)
                if (variables_map.count("namespace") != 0)
                {
                    namespace_ = variables_map["namespace"].as< std::string >();
                }

                auto type        = variables_map["type"].as< type_t >();
                auto indent      = variables_map["indent"].as< unsigned int >();
                auto output_file = variables_map["output"].as< std::filesystem::path >();

                lin::ncf::node_t *selected_node{ nullptr };
                if (node_capability_file.node.size() == 1)
                {
                    selected_node = node_capability_file.node.data();
                }
                else
                {
                    auto node_name = variables_map["node"].as< std::string >();
                    for (auto &node : node_capability_file.node)
                    {
                        if (node.node_name == node_name)
                        {
                            selected_node = &node;
                            break;
                        }
                    }

                    if (selected_node == nullptr)
                    {
                        throw std::out_of_range("Selected node not found.");
                    }
                }


                result = lin::ncf::command::export_(
                    selected_node, type, namespace_, indent, output_file, verbose);
                break;
            }
        }

        if (!result)
        {
            return EXIT_FAILURE;
        }
    }
    catch (boost::program_options::invalid_option_value &error)
    {
        if (error.get_option_name() == "--command")
        {
            error.set_prefix(0);
        }
        std::cerr << error.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (boost::program_options::error &error)
    {
        std::cerr << error.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (std::exception &error)
    {
        std::cerr << error.what() << '\n';
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
// NOLINTEND(readability-function-cognitive-complexity)
