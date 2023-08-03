#include <gtest/gtest.h>

#include <lin/lexical/ncf/node_capability_file.hpp>
#include <lin/test/main.hpp>

#include <fstream>

TEST(test_lin_lexical_ncf_node, node_capability_file_definition)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ncf;

    node_capability_file_t node_capability_file{};

    std::ifstream input(lin::test::binary_path.parent_path() / "example.ncf", std::ifstream::in);
    ASSERT_TRUE(input.good());

    std::string text(std::istreambuf_iterator< char >{ input }, {});
    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::node_capability_file_definition,
        x3::ascii::space,
        node_capability_file);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(node_capability_file.language_version.c_str(), "2.2");
    ASSERT_EQ(node_capability_file.node.size(), 1);
    EXPECT_STREQ(node_capability_file.node[0].node_name.c_str(), "step_motor");

    EXPECT_STREQ(
        node_capability_file.node[0].free_text.c_str(),
        "step_motor signal values outside 0 - 199 are ignored");
}
