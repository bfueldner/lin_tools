#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <boost/program_options/errors.hpp>

#include <lin/ncf/command/command_line.hpp>
#include <lin/test/main.hpp>

TEST(test_lin_ncf_command_line, help)
{
    using namespace lin::ncf::command;

    std::vector< const char * > args{ "ncf_tool", "--help" };

    testing::internal::CaptureStdout();
    auto const result = command_line::parse(static_cast< int >(args.size()), args.data());
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "NCF tool 0.4.0\n"
        "Usage:\n"
        "  ncf_tool <command> [options] <input-file>\n"
        "\n"
        "Commands:\n"
        "  prettify              Prettify file\n"
        "  validate              Validate file\n"
        "\n"
        "Generic options:\n"
        "  -h [ --help ]         Show help text\n"
        "  -v [ --verbose ]      Verbose output\n"
        "  --version             Show program version\n"
        "\n"
        "To get help for a specific command:\n"
        "  ncf_tool <command> --help\n"
        "\n");
    EXPECT_TRUE(result);
}

TEST(test_lin_ncf_command_line, version)
{
    using namespace lin::ncf::command;

    std::vector< const char * > args{ "ncf_tool", "--version" };

    testing::internal::CaptureStdout();
    auto const result = command_line::parse(static_cast< int >(args.size()), args.data());
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "NCF tool 0.4.0\n");
    EXPECT_TRUE(result);
}

TEST(test_lin_ncf_command_line, prettify_help)
{
    using namespace lin::ncf::command;

    std::vector< const char * > args{ "ncf_tool", "prettify", "--help" };

    testing::internal::CaptureStdout();
    auto const result = command_line::parse(static_cast< int >(args.size()), args.data());
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "NCF tool 0.4.0\n"
        "Usage:\n"
        "  ncf_tool prettify [options] <input-file>\n"
        "\n"
        "Generic options:\n"
        "  -h [ --help ]         Show help text\n"
        "  -v [ --verbose ]      Verbose output\n"
        "  --version             Show program version\n"
        "\n"
        "Prettify options:\n"
        "  -i [ --indent ] arg (=4) Indent characters\n"
        "  -o [ --output ] arg      Output file\n"
        "\n");
    EXPECT_TRUE(result);
}

TEST(test_lin_ncf_command_line, prettify_default)
{
    using namespace lin::ncf::command;


    //std::ifstream input(lin::test::binary_path.parent_path() / "example.ncf", std::ifstream::in);
    //ASSERT_TRUE(input.good());
    //
    //std::string text(std::istreambuf_iterator< char >{ input }, {});
    //auto position = text.begin();
    //auto result   = phrase_parse(
    //    position, text.end(), parser::node_capability_file, x3::ascii::space, node_capability_file);
    //ASSERT_TRUE(result);
    //ASSERT_EQ(position, text.end());

    auto input_file =
        (lin::test::binary_path.parent_path() / "example_prettify_input.ncf").string();
    auto output_file =
        (lin::test::binary_path.parent_path() / "example_prettify_output.ncf").string();
    auto generated_file =
        (std::filesystem::temp_directory_path() / "example_prettify.ncf").string();

    std::vector< const char * > args{ "ncf_tool",        "prettify",
                                      "--indent",        "3",
                                      "--output",        generated_file.c_str(),
                                      input_file.c_str() };

    testing::internal::CaptureStdout();
    auto const result = command_line::parse(static_cast< int >(args.size()), args.data());
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "NCF tool 0.4.0\n");

    std::ifstream output(output_file, std::ifstream::in);
    std::ifstream generated(generated_file, std::ifstream::in);
    ASSERT_FALSE(output.fail());
    ASSERT_FALSE(generated.fail());

    std::string const output_text(std::istreambuf_iterator< char >{ output }, {});
    std::string const generated_text(std::istreambuf_iterator< char >{ generated }, {});
    EXPECT_EQ(output_text, generated_text);
    EXPECT_TRUE(result);
}

TEST(test_lin_ncf_command_line, validate_help)
{
    using namespace lin::ncf::command;

    std::vector< const char * > args{ "ncf_tool", "validate", "--help" };

    testing::internal::CaptureStdout();
    auto const result = command_line::parse(static_cast< int >(args.size()), args.data());
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "NCF tool 0.4.0\n"
        "Usage:\n"
        "  ncf_tool validate [options] <input-file>\n"
        "\n"
        "Generic options:\n"
        "  -h [ --help ]         Show help text\n"
        "  -v [ --verbose ]      Verbose output\n"
        "  --version             Show program version\n"
        "\n"
        "Validate options:\n"
        "  -S [ --no-symbols ]          Don't show unicode symbols\n"
        "  -w [ --warnings-as-errors ]  Handle warnings as errors\n"
        "\n");
    EXPECT_TRUE(result);
}

TEST(test_lin_ncf_command_line, validate_default)
{
    using namespace lin::ncf::command;

    auto input_file = (lin::test::binary_path.parent_path() / "example_validate.ncf").string();
    std::vector< const char * > args{ "ncf_tool", "validate", "--no-symbols", input_file.c_str() };

    testing::internal::CaptureStdout();
    auto const result = command_line::parse(static_cast< int >(args.size()), args.data());
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "NCF tool 0.4.0\n"
        "node[step_motor].general.bitrate: Member order '19.2 kbps, 9.6 kbps, 4.8 kbps' (4.8 kbps, 9.6 kbps, 19.2 kbps)\n"
        "node[step_motor].diagnostic.nad: Member order '4, 1, 3, 2' (1, 2, 3, 4)\n"
        "node[step_motor].diagnostic.support_sid: Member order '183, 178, 176' (176, 178, 183)\n"
        "node[step_motor].frame[node_status].signal_offsets: Not sorted\n");
    EXPECT_TRUE(result);
}

TEST(test_lin_ncf_command_line, unknown_help)
{
    using namespace lin::ncf::command;

    std::vector< const char * > args{ "ncf_tool", "unknown", "--help" };

    EXPECT_THROW(
        command_line::parse(static_cast< int >(args.size()), args.data()),
        boost::program_options::invalid_option_value);
}
