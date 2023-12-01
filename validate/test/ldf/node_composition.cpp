#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>
#include <lin/ldf/node_composition.hpp>
#include <lin/ldf/nodes.hpp>
#include <lin/ldf/validate/node_composition.hpp>

/* 9.2.2.3 Node composition definition */

class test_lin_ldf_node_composition_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ldf_node_composition_validate, composite_names)
{
    using namespace lin::ldf;

    node::composition::configuration_t const configuration{
        .composites = { node::composition::configuration::composite_t{ .name = "abc" },
                        node::composition::configuration::composite_t{ .name = "def" } }
    };

    validate::node::composition::composite_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(configuration);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "composite_names\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_node_composition_validate, composite_names_error_not_unique)
{
    using namespace lin::ldf;

    node::composition::configuration_t const configuration{
        .composites = { node::composition::configuration::composite_t{ .name = "abc" },
                        node::composition::configuration::composite_t{ .name = "def" },
                        node::composition::configuration::composite_t{ .name = "abc" } }
    };

    validate::node::composition::composite_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(configuration);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "composite_names: Names not unique 'abc'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_node_composition_validate, configuration_composite_nodes)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .slaves = { "RSM", "LSM" } };
    node::composition::configuration::composite_t const composite{ .nodes = { "LSM", "RSM" } };

    validate::node::composition::configuration::composite_nodes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, composite);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "composite_nodes\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_node_composition_validate, configuration_composite_nodes_warning_empty)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    node::composition::configuration::composite_t const composite{};

    validate::node::composition::configuration::composite_nodes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, composite);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "composite_nodes: Empty\n");
    EXPECT_EQ(logger.warnings(), 1);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_node_composition_validate, configuration_composite_nodes_error_not_defined)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .slaves = { "RSM" } };
    node::composition::configuration::composite_t const composite{ .nodes = { "RSM", "LSM" } };

    validate::node::composition::configuration::composite_nodes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, composite);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "composite_nodes: Not defined 'LSM'\n");
    EXPECT_EQ(logger.warnings(), 0);
}

TEST_F(test_lin_ldf_node_composition_validate, configuration_composite_nodes_error_not_unique)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .slaves = { "RSM", "LSM" } };
    node::composition::configuration::composite_t const composite{ .nodes = { "LSM", "LSM" } };

    validate::node::composition::configuration::composite_nodes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, composite);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "composite_nodes: Duplicate entry 'LSM'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}
