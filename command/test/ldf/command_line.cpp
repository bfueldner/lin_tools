#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <boost/program_options/errors.hpp>

#include <lin/ldf/command/command_line.hpp>
#include <lin/test/main.hpp>

TEST(test_lin_ldf_command_line, help)
{
    using namespace lin::ldf::command;

    std::vector< const char * > args{ "ldf_tool", "--help" };

    testing::internal::CaptureStdout();
    auto const result = command_line::parse(static_cast< int >(args.size()), args.data());
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "LDF tool 0.4.0\n"
        "Usage:\n"
        "  ldf_tool <command> [options] <input-file>\n"
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
        "  ldf_tool <command> --help\n"
        "\n");
    EXPECT_TRUE(result);
}

TEST(test_lin_ldf_command_line, version)
{
    using namespace lin::ldf::command;

    std::vector< const char * > args{ "ldf_tool", "--version" };

    testing::internal::CaptureStdout();
    auto const result = command_line::parse(static_cast< int >(args.size()), args.data());
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "LDF tool 0.4.0\n");
    EXPECT_TRUE(result);
}

TEST(test_lin_ldf_command_line, prettify_help)
{
    using namespace lin::ldf::command;

    std::vector< const char * > args{ "ldf_tool", "prettify", "--help" };

    testing::internal::CaptureStdout();
    auto const result = command_line::parse(static_cast< int >(args.size()), args.data());
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "LDF tool 0.4.0\n"
        "Usage:\n"
        "  ldf_tool prettify [options] <input-file>\n"
        "\n"
        "Generic options:\n"
        "  -h [ --help ]         Show help text\n"
        "  -v [ --verbose ]      Verbose output\n"
        "  --version             Show program version\n"
        "\n"
        "Prettify options:\n"
        "  -i [ --indent ] arg (=4) Indent characters\n"
        "  -s [ --sort ]            Sort elements\n"
        "  -o [ --output ] arg      Output file\n"
        "\n");
    EXPECT_TRUE(result);
}

TEST(test_lin_ldf_command_line, prettify_default)
{
    using namespace lin::ldf::command;

    auto input_file = (lin::test::binary_path.parent_path() / "test_prettify.ldf").string();
    auto output_file =
        (lin::test::binary_path.parent_path() / "test_prettify_output_4.ldf").string();
    auto generated_file = (std::filesystem::temp_directory_path() / "test_prettify.ldf").string();

    std::vector< const char * > args{
        "ldf_tool", "prettify", "--output", generated_file.c_str(), input_file.c_str()
    };

    testing::internal::CaptureStdout();
    auto const result = command_line::parse(static_cast< int >(args.size()), args.data());
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "LDF tool 0.4.0\n");

    std::ifstream output(output_file, std::ifstream::in);
    std::ifstream generated(generated_file, std::ifstream::in);
    ASSERT_FALSE(output.fail());
    ASSERT_FALSE(generated.fail());

    std::string const output_text(std::istreambuf_iterator< char >{ output }, {});
    std::string const generated_text(std::istreambuf_iterator< char >{ generated }, {});
    EXPECT_EQ(output_text, generated_text);
    EXPECT_TRUE(result);
}

TEST(test_lin_ldf_command_line, prettify_indent)
{
    using namespace lin::ldf::command;

    auto input_file = (lin::test::binary_path.parent_path() / "test_prettify.ldf").string();
    auto output_file =
        (lin::test::binary_path.parent_path() / "test_prettify_output_2.ldf").string();
    auto generated_file = (std::filesystem::temp_directory_path() / "test_prettify.ldf").string();

    std::vector< const char * > args{ "ldf_tool",        "prettify",
                                      "--output",        generated_file.c_str(),
                                      "--indent",        "2",
                                      input_file.c_str() };

    testing::internal::CaptureStdout();
    auto const result = command_line::parse(static_cast< int >(args.size()), args.data());
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "LDF tool 0.4.0\n");

    std::ifstream output(output_file, std::ifstream::in);
    std::ifstream generated(generated_file, std::ifstream::in);
    ASSERT_FALSE(output.fail());
    ASSERT_FALSE(generated.fail());

    std::string const output_text(std::istreambuf_iterator< char >{ output }, {});
    std::string const generated_text(std::istreambuf_iterator< char >{ generated }, {});
    EXPECT_EQ(output_text, generated_text);
    EXPECT_TRUE(result);
}

TEST(test_lin_ldf_command_line, prettify_sort)
{
    using namespace lin::ldf::command;

    auto input_file = (lin::test::binary_path.parent_path() / "test_prettify.ldf").string();
    auto output_file =
        (lin::test::binary_path.parent_path() / "test_prettify_output_4_sort.ldf").string();
    auto generated_file = (std::filesystem::temp_directory_path() / "test_prettify.ldf").string();

    std::vector< const char * > args{
        "ldf_tool", "prettify", "--sort", "--output", generated_file.c_str(), input_file.c_str()
    };

    testing::internal::CaptureStdout();
    auto const result = command_line::parse(static_cast< int >(args.size()), args.data());
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "LDF tool 0.4.0\n");

    std::ifstream output(output_file, std::ifstream::in);
    std::ifstream generated(generated_file, std::ifstream::in);
    ASSERT_FALSE(output.fail());
    ASSERT_FALSE(generated.fail());

    std::string const output_text(std::istreambuf_iterator< char >{ output }, {});
    std::string const generated_text(std::istreambuf_iterator< char >{ generated }, {});
    EXPECT_EQ(output_text, generated_text);
    EXPECT_TRUE(result);
}

TEST(test_lin_ldf_command_line, validate_help)
{
    using namespace lin::ldf::command;

    std::vector< const char * > args{ "ldf_tool", "validate", "--help" };

    testing::internal::CaptureStdout();
    auto const result = command_line::parse(static_cast< int >(args.size()), args.data());
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "LDF tool 0.4.0\n"
        "Usage:\n"
        "  ldf_tool validate [options] <input-file>\n"
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

TEST(test_lin_ldf_command_line, validate_default)
{
    using namespace lin::ldf::command;

    auto input_file = (lin::test::binary_path.parent_path() / "test_validate.ldf").string();
    std::vector< const char * > args{ "ldf_tool", "validate", "--no-symbols", input_file.c_str() };

    testing::internal::CaptureStdout();
    auto const result = command_line::parse(static_cast< int >(args.size()), args.data());
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "LDF tool 0.4.0\n");
    EXPECT_TRUE(result);
}

TEST(test_lin_ldf_command_line, unknown_help)
{
    using namespace lin::ldf::command;

    std::vector< const char * > args{ "ldf_tool", "unknown", "--help" };

    EXPECT_THROW(
        command_line::parse(static_cast< int >(args.size()), args.data()),
        boost::program_options::invalid_option_value);
}
