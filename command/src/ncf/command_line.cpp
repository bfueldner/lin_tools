#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include <lin/common/generator/indention.hpp>
#include <lin/common/validate/logger.hpp>
#include <lin/ncf/command/command_line.hpp>
#include <lin/ncf/command/function.hpp>
#include <lin/ncf/command/type.hpp>
#include <lin/ncf/command/type_io.hpp>
#include <lin/ncf/generator/node_capability_file.hpp>
#include <lin/ncf/node.hpp>
#include <lin/ncf/node_capability_file.hpp>
#include <lin/ncf/validate/node_capability_file.hpp>

#include <version.hpp>

namespace lin::ncf::command::command_line {

export_t::export_t():
    command_t{ lin::ncf::command::type_t::export_, "Export file", "Export options" }
{
    /* clang-format off */
    _options.add_options()
        ("type,t", boost::program_options::value< export_type_t >(), "Type of export (frame, signal)")
        ("node", boost::program_options::value< std::string >(), "NCF node name")
        ("namespace,n", boost::program_options::value< std::string >(), "C++ namespace")
        ("indent,i", boost::program_options::value< unsigned int >()->default_value(4), "Indent characters")
        ("output,o", boost::program_options::value< std::filesystem::path >(), "Output file")
    ;
    /* clang-format on */
}

bool export_t::run(
    boost::program_options::variables_map &variables_map,
    node_capability_file_t &node_capability_file,
    bool /*verbose*/)
{
    if (node_capability_file.nodes.empty())
    {
        throw std::out_of_range("No nodes in NCF file.");
    }

    if ((node_capability_file.nodes.size() > 1) && (variables_map.count("node") == 0))
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

    auto type = variables_map["type"].as< export_t >();
    //auto indent      = variables_map["indent"].as< unsigned int >();
    auto output_file = variables_map["output"].as< std::filesystem::path >();

    lin::ncf::node_t *selected_node{ nullptr };
    if (node_capability_file.nodes.size() == 1)
    {
        //selected_node = node_capability_file.nodes.data();
    }
    else
    {
        auto node_name = variables_map["node"].as< std::string >();
        for (auto &node : node_capability_file.nodes)
        {
            if (node.name == node_name)
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

    //result = lin::ncf::command::export_(
    //    selected_node, type, namespace_, indent, output_file, verbose);
    return false;
}

prettify_t::prettify_t():
    command_t{ lin::ncf::command::type_t::prettify, "Prettify file", "Prettify options" }
{
    /* clang-format off */
    _options.add_options()
        ("indent,i", boost::program_options::value< unsigned int >()->default_value(4), "Indent characters")
        ("output,o", boost::program_options::value< std::filesystem::path >(), "Output file")
    ;
    /* clang-format on */
}

bool prettify_t::run(
    boost::program_options::variables_map &variables_map,
    node_capability_file_t &node_capability_file,
    bool verbose)
{
    if (variables_map.count("output") == 0)
    {
        throw boost::program_options::required_option("output");
    }

    auto indent      = variables_map["indent"].as< unsigned int >();
    auto output_file = variables_map["output"].as< std::filesystem::path >();

    /* Sort elements */
    function::sort(node_capability_file);

    std::ofstream output(output_file, std::ofstream::out);
    if (output.fail())
    {
        std::cerr << "Error writing to " << output_file << "\n.";
        return false;
    }

    std::stringstream stream{};
    stream << lin::common::indention_width_t{ static_cast< unsigned int >(indent) };
    stream << std::uppercase << node_capability_file;

    output << stream.str();

    if (verbose)
    {
        std::cerr << "Prettified content written to " << output_file << ".\n";
    }
    return true;
}

validate_t::validate_t():
    command_t{ lin::ncf::command::type_t::validate, "Validate file", "Validate options" }
{
    /* clang-format off */
    _options.add_options()
        ("no-symbols,S", "Don't show unicode symbols")
        ("warnings-as-errors,w", "Handle warnings as errors")
    ;
    /* clang-format on */
}

bool validate_t::run(
    boost::program_options::variables_map &variables_map,
    node_capability_file_t &node_capability_file,
    bool verbose)
{
    const bool no_symbols         = variables_map.count("no-symbols") > 0;
    const bool warnings_as_errors = variables_map.count("warnings-as-errors") > 0;

    common::validate::logger_t logger{ !no_symbols, verbose };
    validate::node_capability_file_t const validator{ logger };

    validator.run(node_capability_file);

    if (logger.errors() > 0)
    {
        return false;
    }

    if (warnings_as_errors && (logger.warnings() > 0))
    {
        return false;
    }

    return true;
}

bool parse(const int argc, const char **argv)
{
    prettify_t prettify;
    validate_t validate;

    std::map< type_t, command_t & > commands{ { type_t::prettify, prettify },
                                              { type_t::validate, validate } };

    std::filesystem::path const filename(
        argv[0]);    // NOLINT(cppcoreguidelines-pro-bounds-pointer-arithmetic)

    /* Generic */
    boost::program_options::options_description generic_options("Generic options");
    // clang-format off
    generic_options.add_options()
        ("help,h", "Show help text")
        ("verbose,v", "Verbose output")
        ("version", "Show program version")
    ;
    // clang-format on

    type_t command_type{};
    std::vector< std::string > subargs{};
    boost::program_options::options_description command_options("Command options");
    /* clang-format off */
    command_options.add_options()
        ("command", boost::program_options::value< type_t >(&command_type), "Subcommand")
        ("subargs", boost::program_options::value< std::vector<std::string> >(&subargs), "Arguments for subcommand")
    ;
    /* clang-format on */

    boost::program_options::options_description all_options("All options");
    all_options.add(generic_options).add(command_options);

    boost::program_options::positional_options_description positional_options;
    positional_options.add("command", 1).add("subargs", -1);

    boost::program_options::variables_map variables_map;
    auto command_line_parser = boost::program_options::command_line_parser(argc, argv)
                                   .options(all_options)
                                   .positional(positional_options)
                                   .allow_unregistered()
                                   .run();
    boost::program_options::store(command_line_parser, variables_map);
    boost::program_options::notify(variables_map);

    std::cout << "NCF tool " << version::string << "\n";

    /* Display general help */
    if ((variables_map.count("help") > 0) && (variables_map.count("command") == 0))
    {
        std::cout << "Usage:\n  " << filename.filename().string()
                  << " <command> [options] <input-file>\n\n";

        std::cout << "Commands:\n";
        for (const auto &[key, command] : commands)
        {
            std::cout << "  " << std::left
                      << std::setw(
                             static_cast< int >(generic_options.get_option_column_width()) - 2)
                      << key << command << '\n';
        }
        std::cout << '\n';

        std::cout << generic_options << '\n';

        std::cout << "To get help for a specific command:\n";
        std::cout << "  " << filename.filename().string() << " <command> --help\n\n";
        return true;
    }

    /* Show program version */
    if (variables_map.count("version") > 0)
    {
        return true;
    }

    /* Extract command */
    if (variables_map.count("command") == 0)
    {
        throw boost::program_options::required_option("command");
    }
    auto &command = commands.at(command_type);

    /* Collect unrecognized arguments and remove */
    std::vector< std::string > options = boost::program_options::collect_unrecognized(
        command_line_parser.options, boost::program_options::include_positional);
    options.erase(options.begin());

    boost::program_options::options_description input_file_options("Input file options");
    /* clang-format off */
    input_file_options.add_options()
        ("input-file", boost::program_options::value< std::filesystem::path >(), "Input file")
    ;
    /* clang-format on */

    boost::program_options::options_description subcommand_options("Subcommand options");
    subcommand_options.add(command.options()).add(input_file_options);

    boost::program_options::positional_options_description input_file_positional;
    input_file_positional.add("input-file", 1);

    boost::program_options::store(
        boost::program_options::command_line_parser(options)
            .options(subcommand_options)
            .positional(input_file_positional)
            .run(),
        variables_map);
    boost::program_options::notify(variables_map);

    /* Display command help */
    if (variables_map.count("help") > 0)
    {
        std::cout << "Usage:\n";
        std::cout << "  " << filename.filename().string() << " " << command_type
                  << " [options] <input-file>\n\n";

        std::cout << generic_options << '\n';

        auto options = command.options();
        if (!options.options().empty())
        {
            std::cout << options << '\n';
        }

        return true;
    }

    /* Extract general options/parameters */
    const bool verbose = variables_map.count("verbose") > 0;
    if (variables_map.count("input-file") == 0)
    {
        throw boost::program_options::required_option("input-file");
    }
    auto input_file = variables_map["input-file"].as< std::filesystem::path >();

    /* Parse given input file as NCF */
    std::ifstream input(input_file, std::ifstream::in);
    if (input.fail())
    {
        std::cerr << "Can not open " << input_file << " for reading.\n";
        return false;
    }

    std::string text(std::istreambuf_iterator< char >{ input }, {});

    node_capability_file_t node_capability_file{};
    function::parse(node_capability_file, text);

    /* Run subcommand */
    return command.run(variables_map, node_capability_file, verbose);
}

}    // namespace lin::ncf::command::command_line
