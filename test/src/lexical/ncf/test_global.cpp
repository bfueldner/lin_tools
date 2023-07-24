#include <gtest/gtest.h>

#include <lin/lexical/ncf/global.hpp>

TEST(test_lin_lexical_ncf_global, language_version)
{
    using namespace lin::lexical::ncf::global;
    namespace x3 = boost::spirit::x3;

    std::string text{ "LIN_language_version = \"2.2\" ;" };
    language_version_t language_version;

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::language_version, x3::ascii::space, language_version);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_STREQ(language_version.c_str(), "2.2");
}
