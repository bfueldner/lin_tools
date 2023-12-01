#include <sstream>

#include <gtest/gtest.h>

#include <lin/ncf/free_text.hpp>
#include <lin/ncf/generator/free_text.hpp>

/* 8.2.7 Free text definition */

TEST(test_lin_ncf_free_text_generator, free_text_definition)
{
    using namespace lin::ncf;

    free_text_t const free_text{ "step_motor signal values outside 0 - 199 are ignored" };

    std::stringstream stream{};
    stream << free_text;
    EXPECT_EQ(
        stream.str(),
        "free_text {\n"
        "    \"step_motor signal values outside 0 - 199 are ignored\"\n"
        "}\n");
}
