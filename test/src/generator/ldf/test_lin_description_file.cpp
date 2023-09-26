#include <sstream>

#include <gtest/gtest.h>

#include <lin/ldf/lin_description_file.hpp>
#include <lin/ldf/node.hpp>
#include <lin/ldf/schedule_table.hpp>
#include <lin/ldf/signal.hpp>

#include <lin/ldf/generator/lin_description_file.hpp>

/* 9.2 LIN description file definition */

TEST(test_lin_lexical_ldf, global)
{
    using namespace lin::ldf;

    lin_description_file_t const lin_description_file{
        "2.2",
        "2.2",
        19.2,
        "DB",
        { { "CEM", 5, 0.1 }, { "LSM", "RSM" } },
        {},
        { { "InternalLightsRequest", 2, 0, "CEM", { "LSM", "RSM" } },
          { "RightIntLightsSwitch", 8, 0, "RSM", { "CEM" } },
          { "LeftIntLightsSwitch", 8, 0, "LSM", { "CEM" } },
          { "LSMerror", 1, 0, "LSM", { "CEM" } },
          { "RSMerror", 1, 0, "RSM", { "CEM" } },
          { "IntTest", 2, 0, "LSM", { "CEM" } } },
        {},
        {
            { "CEM_Frm1", 0x01, "CEM", 1, { { "InternalLightsRequest", 0 } } },
            { "LSM_Frm1", 0x02, "LSM", 2, { { "LeftIntLightsSwitch", 8 } } },
            { "LSM_Frm2", 0x03, "LSM", 1, { { "LSMerror", 0 }, { "IntTest", 1 } } },
            { "RSM_Frm1", 0x04, "RSM", 2, { { "RightIntLightsSwitch", 8 } } },
            { "RSM_Frm2", 0x05, "RSM", 1, { { "RSMerror", 0 } } },
        },
        {},
        { { "Node_Status_Event", "Collision_resolver", 0x06, { "RSM_Frm1", "LSM_Frm1" } } },
        {},
        { {
              .node_name           = "RSM",
              .lin_protocol        = "2.0",
              .configured_nad      = 0x20,
              .product_id          = node::node_attribute::product_id_t{ 0x4e4e, 0x4553, 1 },
              .response_error      = "RSMerror",
              .p2_min              = 150,
              .st_min              = 50,
              .configurable_frames = { { "Node_Status_Event", 0 },
                                       { "CEM_Frm1", 1 },
                                       { "RSM_Frm1", 2 },
                                       { "RSM_Frm2", 3 } },
          },
          {
              .node_name           = "LSM",
              .lin_protocol        = "2.2",
              .configured_nad      = 0x21,
              .initial_nad         = 0x01,
              .product_id          = node::node_attribute::product_id_t{ 0x4a4f, 0x4841 },
              .response_error      = "LSMerror",
              .fault_state_signals = { "IntTest" },
              .p2_min              = 150,
              .st_min              = 50,
              .configurable_frames = { { "Node_Status_Event" },
                                       { "CEM_Frm1" },
                                       { "LSM_Frm1" },
                                       { "LSM_Frm2" } },
          } },
        { { "Configuration_Schedule",
            { { schedule_table::command::assign_nad_t{ "LSM" }, 15.0 },
              { schedule_table::command::assign_frame_id_range_t{ "LSM", 0 }, 15.0 },
              { schedule_table::command::assign_frame_id_t{ "RSM", "CEM_Frm1" }, 15.0 },
              { schedule_table::command::assign_frame_id_t{ "RSM", "RSM_Frm1" }, 15.0 },
              { schedule_table::command::assign_frame_id_t{ "RSM", "RSM_Frm2" }, 15.0 } } },
          { "Normal_Schedule",
            { { "CEM_Frm1", 15.0 },
              { "LSM_Frm2", 15.0 },
              { "RSM_Frm2", 15.0 },
              { "Node_Status_Event", 10.0 } } },
          { "MRF_schedule", { { schedule_table::command::master_req_t{}, 10.0 } } },
          { "SRF_schedule", { { schedule_table::command::slave_resp_t{}, 10.0 } } },
          { "Collision_resolver",
            { { "CEM_Frm1", 15.0 },
              { "LSM_Frm2", 15.0 },
              { "RSM_Frm2", 15.0 },
              { "RSM_Frm1", 10.0 },
              { "CEM_Frm1", 15.0 },
              { "LSM_Frm2", 15.0 },
              { "RSM_Frm2", 15.0 },
              { "LSM_Frm1", 10.0 } } } },
        {},
        { { "Dig2Bit",
            { signal::signal_encoding_type::logical_value_t{ 0, "off" },
              signal::signal_encoding_type::logical_value_t{ 1, "on" },
              signal::signal_encoding_type::logical_value_t{ 2, "error" },
              signal::signal_encoding_type::logical_value_t{ 3, "void" } } },
          { "ErrorEncoding",
            { signal::signal_encoding_type::logical_value_t{ 0, "OK" },
              signal::signal_encoding_type::logical_value_t{ 1, "error" } } },
          { "FaultStateEncoding",
            { signal::signal_encoding_type::logical_value_t{ 0, "No test result" },
              signal::signal_encoding_type::logical_value_t{ 1, "failed" },
              signal::signal_encoding_type::logical_value_t{ 2, "passed" },
              signal::signal_encoding_type::logical_value_t{ 3, "not used" } } },
          { "LightEncoding",
            { signal::signal_encoding_type::logical_value_t{ 0, "Off" },
              signal::signal_encoding_type::physical_range_t{ 1, 254, 1.0, 100.0, "lux" },
              signal::signal_encoding_type::logical_value_t{ 255, "error" } } } },
        { { "Dig2Bit", { "InternalLightsRequest" } },
          { "ErrorEncoding", { "RSMerror", "LSMerror" } },
          { "FaultStateEncoding", { "IntError" } },
          { "LightEncoding", { "RightIntLightsSwitch", "LefttIntLightsSwitch" } } }
    };

    std::stringstream stream{};
    stream << lin_description_file;
    EXPECT_EQ(
        stream.str(),
        "LIN_description_file;\n"
        "LIN_protocol_version = \"2.2\";\n"
        "LIN_language_version = \"2.2\";\n"
        "LIN_speed = 19.2 kbps;\n"
        "Channel_name = \"DB\";\n"
        "Nodes {\n"
        "    Master: CEM, 5 ms, 0.1 ms;\n"
        "    Slaves: LSM, RSM;\n"
        "}\n"
        "Signals {\n"
        "    InternalLightsRequest: 2, 0, CEM, LSM, RSM;\n"
        "    RightIntLightsSwitch: 8, 0, RSM, CEM;\n"
        "    LeftIntLightsSwitch: 8, 0, LSM, CEM;\n"
        "    LSMerror: 1, 0, LSM, CEM;\n"
        "    RSMerror: 1, 0, RSM, CEM;\n"
        "    IntTest: 2, 0, LSM, CEM;\n"
        "}\n"
        "Frames {\n"
        "    CEM_Frm1: 0x01, CEM, 1 {\n"
        "        InternalLightsRequest, 0;\n"
        "    }\n"
        "    LSM_Frm1: 0x02, LSM, 2 {\n"
        "        LeftIntLightsSwitch, 8;\n"
        "    }\n"
        "    LSM_Frm2: 0x03, LSM, 1 {\n"
        "        LSMerror, 0;\n"
        "        IntTest, 1;\n"
        "    }\n"
        "    RSM_Frm1: 0x04, RSM, 2 {\n"
        "        RightIntLightsSwitch, 8;\n"
        "    }\n"
        "    RSM_Frm2: 0x05, RSM, 1 {\n"
        "        RSMerror, 0;\n"
        "    }\n"
        "}\n"
        "Event_triggered_frames {\n"
        "    Node_Status_Event: Collision_resolver, 0x06, RSM_Frm1, LSM_Frm1;\n"
        "}\n"
        "Node_attributes {\n"
        "    RSM {\n"
        "        LIN_protocol = \"2.0\";\n"
        "        configured_NAD = 0x20;\n"
        "        product_id = 0x4e4e, 0x4553, 1;\n"
        "        response_error = RSMerror;\n"
        "        P2_min = 150 ms;\n"
        "        ST_min = 50 ms;\n"
        "        configurable_frames {\n"
        "            Node_Status_Event = 0x00;\n"
        "            CEM_Frm1 = 0x01;\n"
        "            RSM_Frm1 = 0x02;\n"
        "            RSM_Frm2 = 0x03;\n"
        "        }\n"
        "    }\n"
        "    LSM {\n"
        "        LIN_protocol = \"2.2\";\n"
        "        configured_NAD = 0x21;\n"
        "        initial_NAD = 0x01;\n"
        "        product_id = 0x4a4f, 0x4841;\n"
        "        response_error = LSMerror;\n"
        "        fault_state_signals = IntTest;\n"
        "        P2_min = 150 ms;\n"
        "        ST_min = 50 ms;\n"
        "        configurable_frames {\n"
        "            Node_Status_Event;\n"
        "            CEM_Frm1;\n"
        "            LSM_Frm1;\n"
        "            LSM_Frm2;\n"
        "        }\n"
        "    }\n"
        "}\n"
        "Schedule_tables {\n"
        "    Configuration_Schedule {\n"
        "        AssignNAD { LSM } delay 15 ms;\n"
        "        AssignFrameIdRange { LSM, 0 } delay 15 ms;\n"
        "        AssignFrameId { RSM, CEM_Frm1 } delay 15 ms;\n"
        "        AssignFrameId { RSM, RSM_Frm1 } delay 15 ms;\n"
        "        AssignFrameId { RSM, RSM_Frm2 } delay 15 ms;\n"
        "    }\n"
        "    Normal_Schedule {\n"
        "        CEM_Frm1 delay 15 ms;\n"
        "        LSM_Frm2 delay 15 ms;\n"
        "        RSM_Frm2 delay 15 ms;\n"
        "        Node_Status_Event delay 10 ms;\n"
        "    }\n"
        "    MRF_schedule {\n"
        "        MasterReq delay 10 ms;\n"
        "    }\n"
        "    SRF_schedule {\n"
        "        SlaveResp delay 10 ms;\n"
        "    }\n"
        "    Collision_resolver {\n"
        "        CEM_Frm1 delay 15 ms;\n"
        "        LSM_Frm2 delay 15 ms;\n"
        "        RSM_Frm2 delay 15 ms;\n"
        "        RSM_Frm1 delay 10 ms;\n"
        "        CEM_Frm1 delay 15 ms;\n"
        "        LSM_Frm2 delay 15 ms;\n"
        "        RSM_Frm2 delay 15 ms;\n"
        "        LSM_Frm1 delay 10 ms;\n"
        "    }\n"
        "}\n"
        "Signal_encoding_types {\n"
        "    Dig2Bit {\n"
        "        logical_value, 0, \"off\";\n"
        "        logical_value, 1, \"on\";\n"
        "        logical_value, 2, \"error\";\n"
        "        logical_value, 3, \"void\";\n"
        "    }\n"
        "    ErrorEncoding {\n"
        "        logical_value, 0, \"OK\";\n"
        "        logical_value, 1, \"error\";\n"
        "    }\n"
        "    FaultStateEncoding {\n"
        "        logical_value, 0, \"No test result\";\n"
        "        logical_value, 1, \"failed\";\n"
        "        logical_value, 2, \"passed\";\n"
        "        logical_value, 3, \"not used\";\n"
        "    }\n"
        "    LightEncoding {\n"
        "        logical_value, 0, \"Off\";\n"
        "        physical_value, 1, 254, 1, 100, \"lux\";\n"
        "        logical_value, 255, \"error\";\n"
        "    }\n"
        "}\n"
        "Signal_representation {\n"
        "    Dig2Bit: InternalLightsRequest;\n"
        "    ErrorEncoding: RSMerror, LSMerror;\n"
        "    FaultStateEncoding: IntError;\n"
        "    LightEncoding: RightIntLightsSwitch, LefttIntLightsSwitch;\n"
        "}\n");
}
