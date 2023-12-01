#include <string>

#include <gtest/gtest.h>

#include <lin/ldf/nodes.hpp>
#include <lin/ldf/parser/nodes.hpp>

/* 9.2.2.1 Participating nodes */

TEST(test_lin_ldf_nodes_parser, nodes_master)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "Master: CEM, 5 ms, 0.1 ms;" };
    nodes::master_t master{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::nodes_master, x3::ascii::space, master);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_STREQ(master.name.c_str(), "CEM");
    EXPECT_EQ(master.time_base, 5.0);
    EXPECT_EQ(master.jitter, 0.1);
}

TEST(test_lin_ldf_nodes_parser, nodes_slaves)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "Slaves: LSM, RSM;" };
    nodes::slaves_t slaves{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::nodes_slaves, x3::ascii::space, slaves);
    EXPECT_TRUE(result);
    EXPECT_EQ(position, text.end());

    EXPECT_EQ(slaves, (nodes::slaves_t{ "LSM", "RSM" }));
}

TEST(test_lin_ldf_nodes_parser, nodes)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

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

    EXPECT_STREQ(nodes.master.name.c_str(), "CEM");
    EXPECT_EQ(nodes.master.time_base, 5.0);
    EXPECT_EQ(nodes.master.jitter, 0.1);

    EXPECT_EQ(nodes.slaves, (nodes::slaves_t{ "LSM", "RSM" }));
}
