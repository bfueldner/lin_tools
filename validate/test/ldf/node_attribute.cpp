#include <gtest/gtest.h>

#include <lin/common/validate/logger.hpp>
#include <lin/ldf/node_attribute.hpp>
#include <lin/ldf/validate/node_attribute.hpp>

/* 9.2.2.2 Node attributes */

class test_lin_ldf_node_attribute_validate: public testing::Test
{
  public:
    lin::common::validate::logger_t logger{ false, true };
};

TEST_F(test_lin_ldf_node_attribute_validate, protocol_version_1)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .protocol_version = "1.3" };

    validate::node::attribute::protocol_version_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "lin_protocol\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_node_attribute_validate, protocol_version_2)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .protocol_version = "2.2" };

    validate::node::attribute::protocol_version_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "lin_protocol\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_node_attribute_validate, protocol_version_error_not_supported)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .protocol_version = "2.4" };

    validate::node::attribute::protocol_version_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "lin_protocol: Protocol version not supported '2.4' (<= 2.2)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_node_attribute_validate, configured_nad)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .configured_nad = 1 };

    validate::node::attribute::configured_nad_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "configured_nad\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_node_attribute_validate, configured_nad_error_too_low)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .configured_nad = 0 };

    validate::node::attribute::configured_nad_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "configured_nad: Value too low '0' (1..125)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_node_attribute_validate, configured_nad_error_too_high)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .configured_nad = 126 };

    validate::node::attribute::configured_nad_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "configured_nad: Value too high '126' (1..125)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_node_attribute_validate, initial_nad)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .initial_nad = 1 };

    validate::node::attribute::initial_nad_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "initial_nad\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_node_attribute_validate, initial_nad_error_too_low)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .initial_nad = 0 };

    validate::node::attribute::initial_nad_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "initial_nad: Value too low '0' (1..125)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_node_attribute_validate, initial_nad_error_too_high)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .initial_nad = 126 };

    validate::node::attribute::initial_nad_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(), "initial_nad: Value too high '126' (1..125)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_node_attribute_validate, attributes_1x)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .protocol_version = "1.3" };

    validate::node::attribute::attributes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "attributes\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_node_attribute_validate, attributes_1x_error_product_id)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .protocol_version = "1.3",
                                       .product_id =
                                           node::attribute::product_id_t{ 0x1111, 0x2222, 0x33 } };

    validate::node::attribute::attributes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "attributes: LIN 1.x node has LIN 2.x attributes 'product_id'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_node_attribute_validate, attributes_1x_error_response_error)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .protocol_version = "1.3", .response_error = "signal" };

    validate::node::attribute::attributes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "attributes: LIN 1.x node has LIN 2.x attributes 'response_error'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_node_attribute_validate, attributes_1x_error_fault_state_signals)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .protocol_version    = "1.3",
                                       .fault_state_signals = { "signal1", "signal2" } };

    validate::node::attribute::attributes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "attributes: LIN 1.x node has LIN 2.x attributes 'fault_state_signals'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_node_attribute_validate, attributes_1x_error_timings_timeout)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .protocol_version = "1.3",
                                       .p2_min           = 50.0,
                                       .st_min           = 0.0,
                                       .n_as_timeout     = 1000.0,
                                       .n_cr_timeout     = 1000.0 };

    validate::node::attribute::attributes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "attributes: LIN 1.x node has LIN 2.x attributes 'p2_min, st_min, n_as_timeout, n_cr_timeout'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}


TEST_F(test_lin_ldf_node_attribute_validate, attributes_1x_error_configurable_frames)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{
        .protocol_version    = "1.3",
        .configurable_frames = { node::attribute::configurable_frame_t{ .name = "frame" } }
    };

    validate::node::attribute::attributes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "attributes: LIN 1.x node has LIN 2.x attributes 'configurable_frames'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_node_attribute_validate, attributes_2x)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .protocol_version = "2.0",
                                       .product_id =
                                           node::attribute::product_id_t{ 0x1111, 0x2222, 0x33 },
                                       .response_error = "signal" };

    validate::node::attribute::attributes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "attributes\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_node_attribute_validate, attributes_2x_error_missing_response_error)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .protocol_version = "2.0",
                                       .product_id =
                                           node::attribute::product_id_t{ 0x1111, 0x2222, 0x33 } };

    validate::node::attribute::attributes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "attributes: LIN 2.x attributes missing 'response_error' (product_id, response_error)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_node_attribute_validate, attributes_2x_error_missing_product_id)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .protocol_version = "2.0", .response_error = "signal" };

    validate::node::attribute::attributes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "attributes: LIN 2.x attributes missing 'product_id' (product_id, response_error)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_node_attribute_validate, attributes_2x_error_missing_all)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .protocol_version = "2.0" };

    validate::node::attribute::attributes_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "attributes: LIN 2.x attributes missing 'product_id, response_error' (product_id, response_error)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_node_attribute_validate, configurable_frames_10)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{
        .protocol_version = "1.0",
    };

    validate::node::attribute::configurable_frames_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_node_attribute_validate, configurable_frames_20)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{
        .protocol_version    = "2.0",
        .configurable_frames = { node::attribute::configurable_frame_t{ "frame", 0x10 } }
    };

    validate::node::attribute::configurable_frames_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "configurable_frames\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_node_attribute_validate, configurable_frames_20_error_without_message_id)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .protocol_version    = "2.0",
                                       .configurable_frames = {
                                           node::attribute::configurable_frame_t{ "frame1" },
                                           node::attribute::configurable_frame_t{ "frame2", 0x10 },
                                           node::attribute::configurable_frame_t{ "frame3" } } };

    validate::node::attribute::configurable_frames_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "configurable_frames: LIN 2.0 configurable frame without message_id 'frame1, frame3'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_node_attribute_validate, configurable_frames_20_error_message_id_out_of_range)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{
        .protocol_version    = "2.0",
        .configurable_frames = { node::attribute::configurable_frame_t{ "frame1", -1 },
                                 node::attribute::configurable_frame_t{ "frame2", 0x100 },
                                 node::attribute::configurable_frame_t{ "frame3", 0x20 } }
    };

    validate::node::attribute::configurable_frames_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "configurable_frames: LIN 2.0 configurable frame message_id out of range 'frame1, frame2' (0..255)\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}

TEST_F(test_lin_ldf_node_attribute_validate, configurable_frames_21)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .protocol_version    = "2.1",
                                       .configurable_frames = {
                                           node::attribute::configurable_frame_t{ "frame" } } };

    validate::node::attribute::configurable_frames_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(testing::internal::GetCapturedStdout(), "configurable_frames\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 0);
}

TEST_F(test_lin_ldf_node_attribute_validate, configurable_frames_21_error_with_message_id)
{
    using namespace lin::ldf;

    node::attribute_t const attribute{ .protocol_version    = "2.2",
                                       .configurable_frames = {
                                           node::attribute::configurable_frame_t{ "frame1" },
                                           node::attribute::configurable_frame_t{ "frame2", 0x10 },
                                           node::attribute::configurable_frame_t{ "frame3" } } };

    validate::node::attribute::configurable_frames_t const validator{ logger };

    testing::internal::CaptureStdout();
    validator.run(attribute);
    EXPECT_EQ(
        testing::internal::GetCapturedStdout(),
        "configurable_frames: LIN 2.1 configurable frame with message_id 'frame2'\n");
    EXPECT_EQ(logger.warnings(), 0);
    EXPECT_EQ(logger.errors(), 1);
}
