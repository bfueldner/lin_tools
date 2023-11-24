#include <string>

#include <gtest/gtest.h>

#include <lin/ldf/node_composition.hpp>
#include <lin/ldf/parser/node_composition.hpp>

/* 9.2.2.3 Node composition definition */

TEST(test_lin_ldf_node_parser, node_composition_composition)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "CSM {"
        "    RSM, LSM;"
        "}"
    };
    node::composition::configuration::composite_t composite{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::node_composite, x3::ascii::space, composite);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(composite.name.c_str(), "CSM");
    ASSERT_EQ(composite.nodes.size(), 2);
    EXPECT_STREQ(composite.nodes[0].c_str(), "RSM");
    EXPECT_STREQ(composite.nodes[1].c_str(), "LSM");
}

TEST(test_lin_ldf_node_parser, node_composition_configuration)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "configuration CFG {"
        "    CSM {"
        "        RSM, LSM;"
        "    }"
        "}"
    };
    node::composition::configuration_t configuration{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::node_configuration, x3::ascii::space, configuration);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(configuration.name.c_str(), "CFG");
    ASSERT_EQ(configuration.composites.size(), 1);
    EXPECT_STREQ(configuration.composites[0].name.c_str(), "CSM");
    ASSERT_EQ(configuration.composites[0].nodes.size(), 2);
    EXPECT_STREQ(configuration.composites[0].nodes[0].c_str(), "RSM");
    EXPECT_STREQ(configuration.composites[0].nodes[1].c_str(), "LSM");
}

TEST(test_lin_ldf_node_parser, node_composition)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "composite {"
        "    configuration CFG {"
        "        CSM {"
        "            RSM, LSM;"
        "        }"
        "    }"
        "}"
    };
    node::compositions_t compositions{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::node_compositions, x3::ascii::space, compositions);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(compositions.size(), 1);
    EXPECT_STREQ(compositions[0].name.c_str(), "CFG");
    ASSERT_EQ(compositions[0].composites.size(), 1);
    EXPECT_STREQ(compositions[0].composites[0].name.c_str(), "CSM");
    ASSERT_EQ(compositions[0].composites[0].nodes.size(), 2);
    EXPECT_STREQ(compositions[0].composites[0].nodes[0].c_str(), "RSM");
    EXPECT_STREQ(compositions[0].composites[0].nodes[1].c_str(), "LSM");
}
