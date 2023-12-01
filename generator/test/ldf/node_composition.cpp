#include <sstream>

#include <gtest/gtest.h>

#include <lin/ldf/generator/node_composition.hpp>
#include <lin/ldf/node_composition.hpp>

/* 9.2.2.3 Node composition definition */

TEST(test_lin_ldf_node_composition_generator, node_composition_confitguration_composite)
{
    using namespace lin::ldf::node::composition::configuration;

    composite_t const composite{ "CSM", { "RSM", "LSM" } };

    std::stringstream stream{};
    stream << composite;
    EXPECT_EQ(
        stream.str(),
        "CSM {\n"
        "    RSM, LSM;\n"
        "}\n");
}

TEST(test_lin_ldf_node_composition_generator, node_composition_configuration)
{
    using namespace lin::ldf::node::composition;

    configuration_t const configuration{ "CFG", { { "CSM", { "RSM", "LSM" } } } };

    std::stringstream stream{};
    stream << configuration;
    EXPECT_EQ(
        stream.str(),
        "configuration CFG {\n"
        "    CSM {\n"
        "        RSM, LSM;\n"
        "    }\n"
        "}\n");
}

TEST(test_lin_ldf_node_composition_generator, node_composition)
{
    using namespace lin::ldf::node;

    compositions_t const node_composition{ { "CFG", { { "CSM", { "RSM", "LSM" } } } } };

    std::stringstream stream{};
    stream << node_composition;
    EXPECT_EQ(
        stream.str(),
        "composite {\n"
        "    configuration CFG {\n"
        "        CSM {\n"
        "            RSM, LSM;\n"
        "        }\n"
        "    }\n"
        "}\n");
}
