#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>
#include <lin/ldf/nodes.hpp>
#include <lin/ldf/signal_standard.hpp>
#include <lin/ldf/validate/signal_standard.hpp>

/* 9.2.3.1 Standard signals */

class test_lin_ldf_signal_standard_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ldf_signal_standard_validate, signal_size_scalar)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standard_t const signal{ .size       = 4,
                                     .init_value = signal::standard::init_value::scalar_t{ 1 } };

    validate::signal::standard::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "size\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_standard_validate, signal_size_array)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standard_t const signal{ .size       = 16,
                                     .init_value = signal::standard::init_value::array_t{ 0, 0 } };

    validate::signal::standard::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "size\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_standard_validate, signal_size_error_too_low)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standard_t const signal{ .size = 0 };

    validate::signal::standard::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "size: Value too low '0' (1..64)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_signal_standard_validate, signal_size_error_not_aligned)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standard_t const signal{ .size       = 7,
                                     .init_value = signal::standard::init_value::array_t{ 0 } };

    validate::signal::standard::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "size: Value not byte aligned '7' (8)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_signal_standard_validate, signal_size_error_too_high)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standard_t const signal{ .size = 65 };

    validate::signal::standard::size_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "size: Value too high '65' (1..64)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_signal_standard_validate, init_value_scalar)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standard_t const signal{ .size       = 4,
                                     .init_value = signal::standard::init_value::scalar_t{ 1 } };

    validate::signal::standard::init_value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "init_value\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_standard_validate, init_value_scalar_error_too_low)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standard_t const signal{ .size       = 4,
                                     .init_value = signal::standard::init_value::scalar_t{ -1 } };

    validate::signal::standard::init_value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signal);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "init_value: Scalar value too low '-1' (0..15)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_signal_standard_validate, init_value_scalar_error_too_high)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standard_t const signal{ .size       = 4,
                                     .init_value = signal::standard::init_value::scalar_t{ 16 } };

    validate::signal::standard::init_value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signal);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "init_value: Scalar value too high '16' (0..15)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_signal_standard_validate, init_value_array)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standard_t const signal{ .size       = 16,
                                     .init_value = signal::standard::init_value::array_t{ 2, 0 } };

    validate::signal::standard::init_value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "init_value\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_standard_validate, init_value_array_error_size)
{
    using namespace lin::ldf;

    nodes_t const nodes{};
    signal::standard_t const signal{ .size       = 4,
                                     .init_value = signal::standard::init_value::array_t{ 2, 0 } };

    validate::signal::standard::init_value_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signal);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "init_value: Number of array values mismatch signal size '2, 0' (2)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_signal_standard_validate, published_by_master)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .master{ "master" } };
    signal::standard_t const signal{ .published_by = "master" };

    validate::signal::standard::published_by_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "published_by\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_standard_validate, published_by_slave)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .slaves = { "slave" } };
    signal::standard_t const signal{ .published_by = "slave" };

    validate::signal::standard::published_by_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "published_by\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_standard_validate, published_by_error_not_defined_1)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .master{ "master" } };
    signal::standard_t const signal{ .published_by = "slave" };

    validate::signal::standard::published_by_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "published_by: Not defined 'slave'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_signal_standard_validate, published_by_error_not_defined_2)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .slaves = { "slave" } };
    signal::standard_t const signal{ .published_by = "master" };

    validate::signal::standard::published_by_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "published_by: Not defined 'master'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_signal_standard_validate, subscribed_by)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .master{ "master" }, .slaves = { "slave" } };
    signal::standard_t const signal{ .subscribed_by = { "master", "slave" } };

    validate::signal::standard::subscribed_by_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "subscribed_by\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_signal_standard_validate, subscribed_by_error_not_defined)
{
    using namespace lin::ldf;

    nodes_t const nodes{ .master{ "master" }, .slaves = { "slave1" } };
    signal::standard_t const signal{ .subscribed_by = { "master", "slave2" } };

    validate::signal::standard::subscribed_by_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(nodes, signal);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "subscribed_by: Not defined 'slave2'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}
