#include <sstream>

#include <gtest/gtest.h>

#include <lin/ncf/diagnostic.hpp>

#include <lin/ncf/generator/diagnostic.hpp>

/* 8.2.4 Diagnostic definition */

TEST(test_lin_ncf_diagnostic_generator, nad_sequence)
{
    using namespace lin::ncf::diagnostic::nad;

    sequence_t const sequence{ 1, 2, 3 };

    std::stringstream stream{};
    stream << sequence;
    EXPECT_EQ(stream.str(), "1, 2, 3");
}

TEST(test_lin_ncf_diagnostic_generator, nad_range)
{
    using namespace lin::ncf::diagnostic::nad;

    range_t const range{ 1, 3 };

    std::stringstream stream{};
    stream << range;
    EXPECT_EQ(stream.str(), "1 to 3");
}

TEST(test_lin_ncf_diagnostic_generator, diagnostic)
{
    using namespace lin::ncf;

    diagnostic_t const diagnostic{
        diagnostic::nad::range_t{ 1, 3 }, 2, 100, 40, {}, {}, { 0xB0, 0xB2, 0xB7 }, 127
    };

    std::stringstream stream{};
    stream << diagnostic;
    EXPECT_EQ(
        stream.str(),
        "diagnostic {\n"
        "    NAD = 1 to 3;\n"
        "    diagnostic_class = 2;\n"
        "    P2_min = 100 ms;\n"
        "    ST_min = 40 ms;\n"
        "    support_sid { 0xb0, 0xb2, 0xb7 };\n"
        "    max_message_length = 127;\n"
        "}\n");
}
