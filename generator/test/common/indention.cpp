#include <sstream>

#include <gtest/gtest.h>

#include <lin/common/generator/indention.hpp>

TEST(test_lin_common_indention_generator, indent_default)
{
    using namespace lin::common;

    std::stringstream stream{};
    stream << indention_t::indent << "ABC\n" << indention_t::push;
    stream << indention_t::indent << "DEF\n";
    stream << indention_t::pop << indention_t::indent << "GHI\n";
    stream << indention_t::reset;
    EXPECT_EQ(
        stream.str(),
        "ABC\n"
        "    DEF\n"
        "GHI\n");
}

TEST(test_lin_common_indention_generator, indent_two)
{
    using namespace lin::common;

    std::stringstream stream{};
    stream << indention_width_t{ 2 };
    stream << indention_t::indent << "ABC\n" << indention_t::push;
    stream << indention_t::indent << "DEF\n" << indention_t::push;
    stream << indention_t::indent << "GHI\n";
    stream << indention_t::reset;
    EXPECT_EQ(
        stream.str(),
        "ABC\n"
        "  DEF\n"
        "    GHI\n");
}
