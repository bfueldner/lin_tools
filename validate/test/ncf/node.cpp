#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>
#include <lin/ncf/frame.hpp>
#include <lin/ncf/node.hpp>
#include <lin/ncf/signal_encoding.hpp>
#include <lin/ncf/validate/node.hpp>

/* 8.2.2 Node definition */

class test_lin_ncf_node_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ncf_node_validate, frame_names)
{
    using namespace lin::ncf;

    node_t const node{ .frames = { frame_t{ .name = "abc" }, frame_t{ .name = "def" } } };

    validate::node::frame_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(node);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "frame_names\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_node_validate, frame_names_error_not_unique)
{
    using namespace lin::ncf;

    node_t const node{ .frames = { frame_t{ .name = "abc" }, frame_t{ .name = "abc" } } };

    validate::node::frame_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(node);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "frame_names: Names not unique 'abc'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ncf_node_validate, encoding_names)
{
    using namespace lin::ncf;

    node_t const node{ .signal_encodings = { signal::encoding_t{ .name = "abc" },
                                             signal::encoding_t{ .name = "def" } } };

    validate::node::signal_encoding_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(node);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "signal_encoding_names\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ncf_node_validate, encoding_names_error_not_unique)
{
    using namespace lin::ncf;

    node_t const node{ .signal_encodings = { signal::encoding_t{ .name = "def" },
                                             signal::encoding_t{ .name = "def" } } };

    validate::node::signal_encoding_names_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(node);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "signal_encoding_names: Names not unique 'def'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}
