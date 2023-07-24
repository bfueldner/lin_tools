#include <gtest/gtest.h>

#include <lin/lexical/ncf/diagnostic.hpp>

TEST(test_lin_lexical_ncf_diagnostic, nad_range)
{
    using namespace lin::lexical::ncf::diagnostic;
    namespace x3 = boost::spirit::x3;

    std::string text{ "1 to 3" };
    nad_t nad{};

    auto position = text.begin();
    auto result = phrase_parse(position, text.end(), parser::nad_definition, x3::ascii::space, nad);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    auto *nad_range = std::get_if< nad::range_t >(&nad);
    EXPECT_NE(nad_range, nullptr);
    EXPECT_EQ(nad_range->begin, 1);
    EXPECT_EQ(nad_range->end, 3);
}

TEST(test_lin_lexical_ncf_diagnostic, nad_sequence)
{
    using namespace lin::lexical::ncf::diagnostic;
    namespace x3 = boost::spirit::x3;

    std::string text{ "1, 2, 3" };
    nad_t nad{};

    auto position = text.begin();
    auto result = phrase_parse(position, text.end(), parser::nad_definition, x3::ascii::space, nad);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    auto *nad_sequence = std::get_if< nad::sequence_t >(&nad);
    EXPECT_NE(nad_sequence, nullptr);
    EXPECT_EQ(*nad_sequence, (nad::sequence_t{ 1, 2, 3 }));
}

TEST(test_lin_lexical_ncf_diagnostic, diagnostic)
{
    using namespace lin::lexical::ncf;
    namespace x3 = boost::spirit::x3;

    std::string text{
        "diagnostic {"
        "    NAD = 1 to 3;"
        "    diagnostic_class = 2;"
        "    P2_min = 100 ms; ST_min = 40 ms;"
        "    max_message_length = 127;"
        "    support_sid { 0xB0, 0xB2, 0xB7 };"
        "}"
    };
    diagnostic_t diagnostic{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::diagnostic_definition, x3::ascii::space, diagnostic);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    auto *nad_range = std::get_if< diagnostic::nad::range_t >(&diagnostic.nad);
    EXPECT_NE(nad_range, nullptr);
    EXPECT_EQ(nad_range->begin, 1);
    EXPECT_EQ(nad_range->end, 3);
    EXPECT_EQ(diagnostic.diagnostic_class, 2);
    EXPECT_EQ(diagnostic.p2_min, 100.0);
    EXPECT_EQ(diagnostic.st_min, 40.0);
    EXPECT_EQ(diagnostic.n_as_timeout, 1000.0);
    EXPECT_EQ(diagnostic.n_cr_timeout, 1000.0);
    EXPECT_EQ(diagnostic.support_sid, (std::vector< int >{ 0xB0, 0xB2, 0xB7 }));
    EXPECT_EQ(diagnostic.max_message_length, 127);
}
