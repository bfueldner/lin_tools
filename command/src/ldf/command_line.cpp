#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <sstream>
#include <string>
#include <vector>

#include <lin/common/command/type.hpp>
#include <lin/common/command/type_io.hpp>
#include <lin/common/generator/indention.hpp>
#include <lin/common/validate/logger.hpp>
#include <lin/ldf/command/command_line.hpp>
#include <lin/ldf/command/function.hpp>
#include <lin/ldf/generator/lin_description_file.hpp>
#include <lin/ldf/lin_description_file.hpp>
#include <lin/ldf/validate/lin_description_file.hpp>

#include <version.hpp>

namespace lin::ldf::command::command_line {

prettify_t::prettify_t():
    command_t{ lin::common::command::type_t::prettify, "Prettify file", "Prettify options" }
{
    /* clang-format off */
    _options.add_options()
        ("indent,i", boost::program_options::value< unsigned int >()->default_value(4), "Indent characters")
        ("sort,s", "Sort elements")
        ("output,o", boost::program_options::value< std::filesystem::path >(), "Output file")
    ;
    /* clang-format on */
}

bool prettify_t::run(
    boost::program_options::variables_map &variables_map,
    lin_description_file_t &lin_description_file,
    bool verbose)
{
    if (variables_map.count("output") == 0)
    {
        throw boost::program_options::required_option("output");
    }

    auto indent      = variables_map["indent"].as< unsigned int >();
    auto sort        = variables_map.count("sort") > 0;
    auto output_file = variables_map["output"].as< std::filesystem::path >();

    /* Sort elements */
    if (sort)
    {
        function::sort(lin_description_file);
    }

    std::ofstream output(output_file, std::ofstream::out);
    if (output.fail())
    {
        std::cerr << "Error writing to " << output_file << "\n.";
        return false;
    }

    std::stringstream stream{};
    stream << lin::common::indention_width_t{ static_cast< unsigned int >(indent) };
    stream << std::uppercase << lin_description_file;

    output << stream.str();

    if (verbose)
    {
        std::cerr << "Prettified content written to " << output_file << ".\n";
    }
    return true;
}

validate_t::validate_t():
    command_t{ lin::common::command::type_t::validate, "Validate file", "Validate options" }
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
    lin_description_file_t &lin_description_file,
    bool verbose)
{
    const bool no_symbols         = variables_map.count("no-symbols") > 0;
    const bool warnings_as_errors = variables_map.count("warnings-as-errors") > 0;

    common::validate::logger_t logger{ !no_symbols, verbose };
    validate::lin_description_file_t const validator{ logger };

    validator.run(lin_description_file);

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

    std::map< common::command::type_t, command_t & > commands{
        { common::command::type_t::prettify, prettify },
        { common::command::type_t::validate, validate }
    };

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

    common::command::type_t command_type{};
    std::vector< std::string > subargs{};
    boost::program_options::options_description command_options("Command options");
    /* clang-format off */
    command_options.add_options()
        ("command", boost::program_options::value< common::command::type_t >(&command_type), "Subcommand")
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

    std::cout << "LDF tool " << version::string << "\n";

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

    /* Parse given input file as LDF */
    std::ifstream input(input_file, std::ifstream::in);
    if (input.fail())
    {
        std::cerr << "Can not open " << input_file << " for reading.\n";
        return false;
    }

    std::string text(std::istreambuf_iterator< char >{ input }, {});

    lin_description_file_t lin_description_file{};
    function::parse(lin_description_file, text);

    /* Run subcommand */
    return command.run(variables_map, lin_description_file, verbose);
}

}    // namespace lin::ldf::command::command_line
