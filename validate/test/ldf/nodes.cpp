#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>
#include <lin/ldf/nodes.hpp>
#include <lin/ldf/validate/nodes.hpp>

/* 9.2.2 Node definition */

class test_lin_ldf_nodes_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ldf_nodes_validate, master_time_base)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .master = { .time_base = 10 } };

    validate::nodes::master_time_base_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "master.time_base\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_nodes_validate, master_time_base_error_too_low)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .master = { .time_base = 0.0 } };

    validate::nodes::master_time_base_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "master.time_base: Value too low '0' (> 0)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_nodes_validate, master_jitter)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .master = { .jitter = 0.1 } };

    validate::nodes::master_jitter_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "master.jitter\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_nodes_validate, master_jitter_error_too_low)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .master = { .jitter = -0.1 } };

    validate::nodes::master_jitter_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "master.jitter: Value too low '-0.1' (> 0)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_nodes_validate, node_names)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .master = { .name = "MST" }, .slaves = { "SLV1", "SLV2" } };

    validate::nodes::node_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "node_names\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_nodes_validate, node_names_error_not_unique_master)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .master = { .name = "MST" }, .slaves = { "MST", "SLV" } };

    validate::nodes::node_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "node_names: Names not unique 'MST'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_nodes_validate, node_names_error_not_unique_slave)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .master = { .name = "MST" }, .slaves = { "SLV", "SLV" } };

    validate::nodes::node_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "node_names: Names not unique 'SLV'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}
