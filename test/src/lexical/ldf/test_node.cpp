#include <gtest/gtest.h>

#include <lin/lexical/ldf/node.hpp>

TEST(test_lin_lexical_ldf_node, nodes_master)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::nodes;

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

    using namespace lin::lexical::ldf::nodes;

    std::string text{ "Slaves: LSM, RSM;" };
    slaves_t slaves{};

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::slaves, x3::ascii::space, slaves);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_EQ(slaves, (slaves_t{ "LSM", "RSM" }));
}

TEST(test_lin_lexical_ldf_node, nodes)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf;

    std::string text{
        "Nodes {"
        "    Slaves: LSM, RSM ;"
        "    Master: CEM, 5 ms, 0.1 ms ;"
        "}"
    };
    nodes_t nodes;

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::nodes, x3::ascii::space, nodes);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_STREQ(nodes.master.node_name.c_str(), "CEM");
    EXPECT_EQ(nodes.master.time_base, 5.0);
    EXPECT_EQ(nodes.master.jitter, 0.1);

    EXPECT_EQ(nodes.slaves, (nodes::slaves_t{ "LSM", "RSM" }));
}
