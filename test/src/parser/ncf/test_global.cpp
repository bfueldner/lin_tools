#include <string>

#include <gtest/gtest.h>

#include <lin/ncf/global.hpp>

#include <lin/ncf/parser/global.hpp>

TEST(test_lin_ncf_global_parser, language_version)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf::global;

    std::string text{ "LIN_language_version = \"2.2\" ;" };
    language_version_t language_version;

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::language_version, x3::ascii::space, language_version);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(language_version.c_str(), "2.2");
}
