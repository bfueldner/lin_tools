#include <sstream>

#include <gtest/gtest.h>

#include <lin/ldf/generator/nodes.hpp>
#include <lin/ldf/nodes.hpp>

/* 9.2.2.1 Participating nodes */

TEST(test_lin_ldf_nodes_generator, nodes_master)
{
    using namespace lin::ldf::nodes;

    master_t const master{ "CEM", 5, 0.1 };

    std::stringstream stream{};
    stream << master;
    EXPECT_EQ(stream.str(), "Master: CEM, 5 ms, 0.1 ms;\n");
}

TEST(test_lin_ldf_nodes_generator, nodes_slaves)
{
    using namespace lin::ldf::nodes;

    slaves_t const slaves{ "LSM", "RSM" };

    std::stringstream stream{};
    stream << slaves;
    EXPECT_EQ(stream.str(), "Slaves: LSM, RSM;\n");
}

TEST(test_lin_ldf_nodes_generator, nodes)
{
    using namespace lin::ldf;

    nodes_t const nodes{ { "CEM", 5, 0.1 }, { "LSM", "RSM" } };

    std::stringstream stream{};
    stream << nodes;
    EXPECT_EQ(
        stream.str(),
        "Nodes {\n"
        "    Master: CEM, 5 ms, 0.1 ms;\n"
        "    Slaves: LSM, RSM;\n"
        "}\n");
}
