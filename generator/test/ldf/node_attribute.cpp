#include <sstream>

#include <gtest/gtest.h>

#include <lin/ldf/generator/node_attribute.hpp>
#include <lin/ldf/node_attribute.hpp>

/* 9.2.2.2 Node attributes */

TEST(test_lin_ldf_node_attribute_generator, node_attribute_product_id)
{
    using namespace lin::ldf::node::attribute;

    product_id_t const product_id{ 0x1234, 0xabcd, 10 };

    std::stringstream stream{};
    stream << product_id;
    EXPECT_EQ(stream.str(), "product_id = 0x1234, 0xabcd, 10;");
}

TEST(test_lin_ldf_node_attribute_generator, node_attribute_configurable_frame_20)
{
    using namespace lin::ldf::node::attribute;

    configurable_frame_t const configurable_frame{ "Node_Status_Event", 1 };

    std::stringstream stream{};
    stream << configurable_frame;
    EXPECT_EQ(stream.str(), "Node_Status_Event = 0x01;\n");
}

TEST(test_lin_ldf_node_attribute_generator, node_attribute_configurable_frame_21)
{
    using namespace lin::ldf::node::attribute;

    configurable_frame_t const configurable_frame{ "Node_Status_Event" };

    std::stringstream stream{};
    stream << configurable_frame;
    EXPECT_EQ(stream.str(), "Node_Status_Event;\n");
}

TEST(test_lin_ldf_node_attribute_generator, node_attribute_configurable_frames_20)
{
    using namespace lin::ldf::node::attribute;

    configurable_frames_t const configurable_frames{
        { "Node_Status_Event", 0 }, { "CEM_Frm1", 1 }, { "RSM_Frm1", 2 }, { "RSM_Frm2", 3 }
    };

    std::stringstream stream{};
    stream << configurable_frames;
    EXPECT_EQ(
        stream.str(),
        "configurable_frames {\n"
        "    Node_Status_Event = 0x00;\n"
        "    CEM_Frm1 = 0x01;\n"
        "    RSM_Frm1 = 0x02;\n"
        "    RSM_Frm2 = 0x03;\n"
        "}\n");
}

TEST(test_lin_ldf_node_attribute_generator, node_attribute_configurable_frames_21)
{
    using namespace lin::ldf::node::attribute;

    configurable_frames_t const configurable_frames{
        { "Node_Status_Event" }, { "CEM_Frm1" }, { "RSM_Frm1" }, { "RSM_Frm2" }
    };

    std::stringstream stream{};
    stream << configurable_frames;
    EXPECT_EQ(
        stream.str(),
        "configurable_frames {\n"
        "    Node_Status_Event;\n"
        "    CEM_Frm1;\n"
        "    RSM_Frm1;\n"
        "    RSM_Frm2;\n"
        "}\n");
}

TEST(test_lin_ldf_node_attribute_generator, node_attribute_13)
{
    using namespace lin::ldf::node;

    attribute_t const attribute{ "CEM", "1.3", 0x01 };

    std::stringstream stream{};
    stream << attribute;
    EXPECT_EQ(
        stream.str(),
        "CEM {\n"
        "    LIN_protocol = \"1.3\";\n"
        "    configured_NAD = 0x01;\n"
        "}\n");
}

TEST(test_lin_ldf_node_attribute_generator, node_attribute_20)
{
    using namespace lin::ldf::node;

    attribute_t const attribute{
        .name                = "RSM",
        .protocol_version    = "2.0",
        .configured_nad      = 0x20,
        .product_id          = attribute::product_id_t{ 0x4e4e, 0x4553, 1 },
        .response_error      = "RSMerror",
        .p2_min              = 150,
        .st_min              = 50,
        .configurable_frames = { { "Node_Status_Event", 0 },
                                 { "CEM_Frm1", 1 },
                                 { "RSM_Frm1", 2 },
                                 { "RSM_Frm2", 3 } },
    };

    std::stringstream stream{};
    stream << attribute;
    EXPECT_EQ(
        stream.str(),
        "RSM {\n"
        "    LIN_protocol = \"2.0\";\n"
        "    configured_NAD = 0x20;\n"
        "    product_id = 0x4e4e, 0x4553, 1;\n"
        "    response_error = RSMerror;\n"
        "    P2_min = 150 ms;\n"
        "    ST_min = 50 ms;\n"
        "    configurable_frames {\n"
        "        Node_Status_Event = 0x00;\n"
        "        CEM_Frm1 = 0x01;\n"
        "        RSM_Frm1 = 0x02;\n"
        "        RSM_Frm2 = 0x03;\n"
        "    }\n"
        "}\n");
}

TEST(test_lin_ldf_node_attribute_generator, node_attributes)
{
    using namespace lin::ldf::node;

    attributes_t const attributes{ { "RSM", "2.0", 0x20 }, { "LSM", "2.2", 0x21, 1 } };

    std::stringstream stream{};
    stream << attributes;
    EXPECT_EQ(
        stream.str(),
        "Node_attributes {\n"
        "    RSM {\n"
        "        LIN_protocol = \"2.0\";\n"
        "        configured_NAD = 0x20;\n"
        "    }\n"
        "    LSM {\n"
        "        LIN_protocol = \"2.2\";\n"
        "        configured_NAD = 0x21;\n"
        "        initial_NAD = 0x01;\n"
        "    }\n"
        "}\n");
}
