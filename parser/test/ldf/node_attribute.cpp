#include <string>

#include <gtest/gtest.h>

#include <lin/ldf/node_attribute.hpp>
#include <lin/ldf/parser/node_attribute.hpp>

/* 9.2.2.2 Node attributes */

TEST(test_lin_ldf_node_parser, node_attribute_protocol_version)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "LIN_protocol = \"2.0\";" };
    node::attribute::protocol_version_t protocol_version{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::node_attribute_protocol_version,
        x3::ascii::space,
        protocol_version);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(protocol_version.c_str(), "2.0");
}

TEST(test_lin_ldf_node_parser, node_attribute_configured_nad)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "configured_NAD = 0x20;" };
    node::attribute::configured_nad_t configured_nad{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::node_attribute_configured_nad,
        x3::ascii::space,
        configured_nad);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(configured_nad, 0x20);
}

TEST(test_lin_ldf_node_parser, node_attribute_initial_nad)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "initial_NAD = 0x01;" };
    node::attribute::initial_nad_t initial_nad{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::node_attribute_initial_nad, x3::ascii::space, initial_nad);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(initial_nad, 0x01);
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_ldf_node_parser, node_attribute_product_id)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "product_id = 0x1234,1234,10;" };
    node::attribute::product_id_t product_id{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::node_attribute_product_id, x3::ascii::space, product_id);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(product_id.supplier, 0x1234);
    EXPECT_EQ(product_id.function, 1234);
    EXPECT_TRUE(product_id.variant.has_value());
    if (product_id.variant.has_value())
    {
        EXPECT_EQ(product_id.variant.value(), 10);
    }
}
// NOLINTEND(readability-function-cognitive-complexity)

TEST(test_lin_ldf_node_parser, node_attribute_response_error)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "response_error = RSMerror;" };
    node::attribute::response_error_t response_error{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::node_attribute_response_error,
        x3::ascii::space,
        response_error);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(response_error.c_str(), "RSMerror");
}

TEST(test_lin_ldf_node_parser, node_attribute_fault_state_signals)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "fault_state_signals = IntTest;" };
    node::attribute::fault_state_signals_t fault_state_signals{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::node_attribute_fault_state_signals,
        x3::ascii::space,
        fault_state_signals);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(fault_state_signals, node::attribute::fault_state_signals_t{ "IntTest" });
}

TEST(test_lin_ldf_node_parser, node_attribute_p2_min)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "P2_min = 150 ms;" };
    node::attribute::p2_min_t p2_min{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::node_attribute_p2_min, x3::ascii::space, p2_min);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(p2_min, 150.0);
}

TEST(test_lin_ldf_node_parser, node_attribute_st_min)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "ST_min = 50 ms;" };
    node::attribute::st_min_t st_min{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::node_attribute_st_min, x3::ascii::space, st_min);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(st_min, 50.0);
}

TEST(test_lin_ldf_node_parser, node_attribute_n_as_timeout)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "N_As_timeout = 1500 ms;" };
    node::attribute::n_as_timeout_t n_as_timeout{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::node_attribute_n_as_timeout, x3::ascii::space, n_as_timeout);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(n_as_timeout, 1500.0);
}

TEST(test_lin_ldf_node_parser, node_attribute_n_cr_timeout)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "N_Cr_timeout = 1500 ms;" };
    node::attribute::n_cr_timeout_t n_cr_timeout{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::node_attribute_n_cr_timeout, x3::ascii::space, n_cr_timeout);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(n_cr_timeout, 1500.0);
}

TEST(test_lin_ldf_node_parser, node_attribute_configurable_frame_20)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "CEM_Frm1 = 0x0001;" };
    node::attribute::configurable_frame_t configurable_frame{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::node_attribute_configurable_frame,
        x3::ascii::space,
        configurable_frame);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(configurable_frame.name.c_str(), "CEM_Frm1");
    ASSERT_TRUE(configurable_frame.id.has_value());
    if (configurable_frame.id.has_value())
    {
        EXPECT_EQ(configurable_frame.id.value(), 1);
    }
}

TEST(test_lin_ldf_node_parser, node_attribute_configurable_frame_21)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "Node_Status_Event;" };
    node::attribute::configurable_frame_t configurable_frame{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::node_attribute_configurable_frame,
        x3::ascii::space,
        configurable_frame);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(configurable_frame.name.c_str(), "Node_Status_Event");
    EXPECT_FALSE(configurable_frame.id.has_value());
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_ldf_node_parser, node_attribute_configurable_frames_20)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "configurable_frames {"
        "    Node_Status_Event=0x000; CEM_Frm1 = 0x0001; RSM_Frm1 = 0x0002;"
        "    RSM_Frm2 = 0x0003;"
        "}"
    };
    node::attribute::configurable_frames_t configurable_frames{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::node_attribute_configurable_frames,
        x3::ascii::space,
        configurable_frames);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(configurable_frames.size(), 4);
    // NOLINTBEGIN(readability-container-data-pointer)
    {
        auto *configurable_frame = &(configurable_frames[0]);
        EXPECT_STREQ(configurable_frame->name.c_str(), "Node_Status_Event");
        ASSERT_TRUE(configurable_frame->id.has_value());
        if (configurable_frame->id.has_value())
        {
            EXPECT_EQ(configurable_frame->id.value(), 0);
        }
    }
    {
        auto *configurable_frame = &(configurable_frames[1]);
        EXPECT_STREQ(configurable_frame->name.c_str(), "CEM_Frm1");
        ASSERT_TRUE(configurable_frame->id.has_value());
        if (configurable_frame->id.has_value())
        {
            EXPECT_EQ(configurable_frame->id.value(), 1);
        }
    }
    {
        auto *configurable_frame = &(configurable_frames[2]);
        EXPECT_STREQ(configurable_frame->name.c_str(), "RSM_Frm1");
        ASSERT_TRUE(configurable_frame->id.has_value());
        if (configurable_frame->id.has_value())
        {
            EXPECT_EQ(configurable_frame->id.value(), 2);
        }
    }
    {
        auto *configurable_frame = &(configurable_frames[3]);
        EXPECT_STREQ(configurable_frame->name.c_str(), "RSM_Frm2");
        ASSERT_TRUE(configurable_frame->id.has_value());
        if (configurable_frame->id.has_value())
        {
            EXPECT_EQ(configurable_frame->id.value(), 3);
        }
    }
    // NOLINTEND(readability-container-data-pointer)
}
// NOLINTEND(readability-function-cognitive-complexity)

TEST(test_lin_ldf_node_parser, node_attribute_configurable_frames_21)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "configurable_frames {"
        "    Node_Status_Event; CEM_Frm1; LSM_Frm1; LSM_Frm2;"
        "}"
    };
    node::attribute::configurable_frames_t configurable_frames{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::node_attribute_configurable_frames,
        x3::ascii::space,
        configurable_frames);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(configurable_frames.size(), 4);
    // NOLINTBEGIN(readability-container-data-pointer)
    {
        auto *configurable_frame = &(configurable_frames[0]);
        EXPECT_STREQ(configurable_frame->name.c_str(), "Node_Status_Event");
        EXPECT_FALSE(configurable_frame->id.has_value());
    }
    {
        auto *configurable_frame = &(configurable_frames[1]);
        EXPECT_STREQ(configurable_frame->name.c_str(), "CEM_Frm1");
        EXPECT_FALSE(configurable_frame->id.has_value());
    }
    {
        auto *configurable_frame = &(configurable_frames[2]);
        EXPECT_STREQ(configurable_frame->name.c_str(), "LSM_Frm1");
        EXPECT_FALSE(configurable_frame->id.has_value());
    }
    {
        auto *configurable_frame = &(configurable_frames[3]);
        EXPECT_STREQ(configurable_frame->name.c_str(), "LSM_Frm2");
        EXPECT_FALSE(configurable_frame->id.has_value());
    }
    // NOLINTEND(readability-container-data-pointer)
}

TEST(test_lin_ldf_node_parser, node_attribute_10)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "CEM {"
        "    configured_NAD = 0x01;"
        "    LIN_protocol = \"1.3\";"
        "}"
    };
    node::attribute_t node_attribute{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::node_attribute, x3::ascii::space, node_attribute);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(node_attribute.name.c_str(), "CEM");
    EXPECT_STREQ(node_attribute.protocol_version.c_str(), "1.3");
    EXPECT_EQ(node_attribute.configured_nad, 0x01);
    EXPECT_FALSE(node_attribute.initial_nad.has_value());
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_ldf_node_parser, node_attribute_20)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "RSM {"
        "    LIN_protocol = \"2.0\";"
        "    configured_NAD = 0x20;"
        "    product_id = 0x4E4E, 0x4553, 1;"
        "    response_error = RSMerror;"
        "    P2_min = 150 ms;"
        "    ST_min = 50 ms;"
        "    configurable_frames {"
        "        Node_Status_Event=0x000; CEM_Frm1 = 0x0001; RSM_Frm1 = 0x0002;"
        "        RSM_Frm2 = 0x0003;"
        "    }"
        "}"
    };
    node::attribute_t node_attribute{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::node_attribute, x3::ascii::space, node_attribute);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(node_attribute.name.c_str(), "RSM");
    EXPECT_STREQ(node_attribute.protocol_version.c_str(), "2.0");
    EXPECT_EQ(node_attribute.configured_nad, 0x20);
    EXPECT_FALSE(node_attribute.initial_nad.has_value());
    ASSERT_TRUE(node_attribute.product_id.has_value());
    if (node_attribute.product_id.has_value())
    {
        EXPECT_EQ(node_attribute.product_id.value().supplier, 0x4E4E);
        EXPECT_EQ(node_attribute.product_id.value().function, 0x4553);
        ASSERT_TRUE(node_attribute.product_id.value().variant.has_value());
        if (node_attribute.product_id.value().variant.has_value())
        {
            EXPECT_EQ(node_attribute.product_id.value().variant.value(), 1);
        }
    }
    ASSERT_TRUE(node_attribute.response_error.has_value());
    if (node_attribute.response_error.has_value())
    {
        EXPECT_STREQ(node_attribute.response_error.value().c_str(), "RSMerror");
    }
    EXPECT_EQ(node_attribute.fault_state_signals.size(), 0);
    EXPECT_EQ(node_attribute.p2_min, 150.0);
    EXPECT_EQ(node_attribute.st_min, 50.0);

    EXPECT_FALSE(node_attribute.n_as_timeout.has_value());
    EXPECT_FALSE(node_attribute.n_cr_timeout.has_value());
    ASSERT_EQ(node_attribute.configurable_frames.size(), 4);
    // NOLINTBEGIN(readability-container-data-pointer)
    {
        auto *configurable_frame = &(node_attribute.configurable_frames[0]);
        EXPECT_STREQ(configurable_frame->name.c_str(), "Node_Status_Event");
        ASSERT_TRUE(configurable_frame->id.has_value());
        if (configurable_frame->id.has_value())
        {
            EXPECT_EQ(configurable_frame->id.value(), 0);
        }
    }
    {
        auto *configurable_frame = &(node_attribute.configurable_frames[1]);
        EXPECT_STREQ(configurable_frame->name.c_str(), "CEM_Frm1");
        ASSERT_TRUE(configurable_frame->id.has_value());
        if (configurable_frame->id.has_value())
        {
            EXPECT_EQ(configurable_frame->id.value(), 1);
        }
    }
    {
        auto *configurable_frame = &(node_attribute.configurable_frames[2]);
        EXPECT_STREQ(configurable_frame->name.c_str(), "RSM_Frm1");
        ASSERT_TRUE(configurable_frame->id.has_value());
        if (configurable_frame->id.has_value())
        {
            EXPECT_EQ(configurable_frame->id.value(), 2);
        }
    }
    {
        auto *configurable_frame = &(node_attribute.configurable_frames[3]);
        EXPECT_STREQ(configurable_frame->name.c_str(), "RSM_Frm2");
        ASSERT_TRUE(configurable_frame->id.has_value());
        if (configurable_frame->id.has_value())
        {
            EXPECT_EQ(configurable_frame->id.value(), 3);
        }
    }
    // NOLINTEND(readability-container-data-pointer)
}
// NOLINTEND(readability-function-cognitive-complexity)

TEST(test_lin_ldf_node_parser, node_attributes)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "Node_attributes {"
        "    RSM {"
        "        LIN_protocol = \"2.0\";"
        "        configured_NAD = 0x20;"
        "    }"
        "    LSM {"
        "        LIN_protocol = \"2.2\";"
        "        configured_NAD = 0x21;"
        "        initial_NAD = 0x01;"
        "    }"
        "}"
    };
    node::attributes_t node_attributes{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::node_attributes, x3::ascii::space, node_attributes);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(node_attributes.size(), 2);
    EXPECT_STREQ(node_attributes[0].name.c_str(), "RSM");
    EXPECT_STREQ(node_attributes[0].protocol_version.c_str(), "2.0");
    EXPECT_EQ(node_attributes[0].configured_nad, 0x20);
    EXPECT_STREQ(node_attributes[1].name.c_str(), "LSM");
    EXPECT_STREQ(node_attributes[1].protocol_version.c_str(), "2.2");
    EXPECT_EQ(node_attributes[1].configured_nad, 0x21);
}
