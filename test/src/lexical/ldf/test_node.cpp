#include <gtest/gtest.h>

#include <lin/lexical/ldf/node.hpp>

/* 9.2.2 Node definition */

/* 9.2.2.1 Participating nodes */

TEST(test_lin_lexical_ldf_node, participating_nodes_master)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::node::participating_nodes;

    std::string text{ "Master: CEM, 5 ms, 0.1 ms;" };
    master_t master{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::master, x3::ascii::space, master);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_STREQ(master.node_name.c_str(), "CEM");
    EXPECT_EQ(master.time_base, 5.0);
    EXPECT_EQ(master.jitter, 0.1);
}

TEST(test_lin_lexical_ldf_node, participating_nodes_slaves)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::node::participating_nodes;

    std::string text{ "Slaves: LSM, RSM;" };
    slaves_t slaves{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::slaves, x3::ascii::space, slaves);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_EQ(slaves, (slaves_t{ "LSM", "RSM" }));
}

TEST(test_lin_lexical_ldf_node, node)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::node;

    std::string text{
        "Nodes {"
        "    Slaves: LSM, RSM ;"
        "    Master: CEM, 5 ms, 0.1 ms ;"
        "}"
    };
    participating_nodes_t participating_nodes;

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::participating_nodes, x3::ascii::space, participating_nodes);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_STREQ(participating_nodes.master.node_name.c_str(), "CEM");
    EXPECT_EQ(participating_nodes.master.time_base, 5.0);
    EXPECT_EQ(participating_nodes.master.jitter, 0.1);

    EXPECT_EQ(participating_nodes.slaves, (participating_nodes::slaves_t{ "LSM", "RSM" }));
}
