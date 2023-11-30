#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <lin/common/signal_encoding.hpp>
#include <lin/ldf/command/function.hpp>
#include <lin/ldf/lin_description_file.hpp>

class test_lin_ldf_function_command: public testing::Test
{
  public:
    lin::ldf::lin_description_file_t ldf{
        "2.2",
        "2.2",
        { 19.2 },
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
              .name                = "RSM",
              .protocol_version    = "2.0",
              .configured_nad      = 0x20,
              .product_id          = lin::ldf::node::attribute::product_id_t{ 0x4e4e, 0x4553, 1 },
              .response_error      = "RSMerror",
              .p2_min              = 150,
              .st_min              = 50,
              .configurable_frames = { { "Node_Status_Event", 0 },
                                       { "CEM_Frm1", 1 },
                                       { "RSM_Frm1", 2 },
                                       { "RSM_Frm2", 3 } },
          },
          {
              .name                = "LSM",
              .protocol_version    = "2.2",
              .configured_nad      = 0x21,
              .initial_nad         = 0x01,
              .product_id          = lin::ldf::node::attribute::product_id_t{ 0x4a4f, 0x4841 },
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
            { { lin::ldf::schedule_table::command::assign_nad_t{ "LSM" }, 15.0 },
              { lin::ldf::schedule_table::command::assign_frame_id_range_t{ "LSM", 0 }, 15.0 },
              { lin::ldf::schedule_table::command::assign_frame_id_t{ "RSM", "CEM_Frm1" }, 15.0 },
              { lin::ldf::schedule_table::command::assign_frame_id_t{ "RSM", "RSM_Frm1" }, 15.0 },
              { lin::ldf::schedule_table::command::assign_frame_id_t{ "RSM", "RSM_Frm2" },
                15.0 } } },
          { "Normal_Schedule",
            { { "CEM_Frm1", 15.0 },
              { "LSM_Frm2", 15.0 },
              { "RSM_Frm2", 15.0 },
              { "Node_Status_Event", 10.0 } } },
          { "MRF_schedule", { { lin::ldf::schedule_table::command::master_req_t{}, 10.0 } } },
          { "SRF_schedule", { { lin::ldf::schedule_table::command::slave_resp_t{}, 10.0 } } },
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
        { { "FaultStateEncoding",
            { lin::ldf::signal::encoding::logical_value_t{ 0, "No test result" },
              lin::ldf::signal::encoding::logical_value_t{ 1, "failed" },
              lin::ldf::signal::encoding::logical_value_t{ 2, "passed" },
              lin::ldf::signal::encoding::logical_value_t{ 3, "not used" } } },
          { "Dig2Bit",
            { lin::ldf::signal::encoding::logical_value_t{ 0, "off" },
              lin::ldf::signal::encoding::logical_value_t{ 1, "on" },
              lin::ldf::signal::encoding::logical_value_t{ 2, "error" },
              lin::ldf::signal::encoding::logical_value_t{ 3, "void" } } },
          { "ErrorEncoding",
            { lin::ldf::signal::encoding::logical_value_t{ 0, "OK" },
              lin::ldf::signal::encoding::logical_value_t{ 1, "error" } } },
          { "LightEncoding",
            { lin::ldf::signal::encoding::logical_value_t{ 0, "Off" },
              lin::ldf::signal::encoding::physical_range_t{ 1, 254, 1.0, 100.0, "lux" },
              lin::ldf::signal::encoding::logical_value_t{ 255, "error" } } } },
        { { "Dig2Bit", { "InternalLightsRequest" } },
          { "ErrorEncoding", { "RSMerror", "LSMerror" } },
          { "FaultStateEncoding", { "IntError" } },
          { "LightEncoding", { "RightIntLightsSwitch", "LefttIntLightsSwitch" } } }
    };
};

namespace lin::common::signal::encoding {

bool operator==(const logical_value_t &value1, const logical_value_t &value2)
{
    return (value1.value == value2.value) && (value1.text_info == value2.text_info);
}

bool operator==(const physical_range_t &range1, const physical_range_t &range2)
{
    return (range1.min == range2.min) && (range1.max == range2.max) &&
           (range1.offset == range2.offset) && (range1.scale == range2.scale) &&
           (range1.text_info == range2.text_info);
}

bool operator==(const bcd_value_t & /*unused*/, const bcd_value_t & /*unused*/)
{
    return true;
}

bool operator==(const ascii_value_t & /*unused*/, const ascii_value_t & /*unused*/)
{
    return true;
}

}    // namespace lin::common::signal::encoding

namespace lin::ldf {

bool operator==(const signal_t &signal1, const signal_t &signal2)
{
    return (signal1.name == signal2.name) &&
           (signal1.init_value.index() == signal2.init_value.index()) &&
           (signal1.size == signal2.size) && (signal1.offset == signal2.offset) &&
           (signal1.encoding == signal2.encoding);
}

}    // namespace lin::ldf

TEST_F(test_lin_ldf_function_command, sort)
{
    using namespace lin::ldf::command;

    function::sort(ldf);

    ASSERT_EQ(ldf.nodes.size(), 1);

    auto &node = ldf.nodes[0];
    ASSERT_EQ(node.general.bitrate.index(), 1);
    auto *bitrate = std::get_if< lin::ldf::general::bitrate::select_t >(&node.general.bitrate);
    EXPECT_THAT(*bitrate, testing::ElementsAre(4.8, 9.6, 19.2));

    ASSERT_EQ(node.diagnostic.nad.index(), 1);
    auto *nad = std::get_if< lin::ldf::diagnostic::nad::sequence_t >(&node.diagnostic.nad);
    EXPECT_THAT(*nad, testing::ElementsAre(1, 2, 3, 4));

    EXPECT_THAT(node.diagnostic.support_sids, testing::ElementsAre(0xb0, 0xb2, 0xb7));

    ASSERT_EQ(node.frames.size(), 2);

    auto &frame = node.frames[0];
    EXPECT_THAT(
        frame.signals,
        testing::ElementsAreArray(
            { lin::ldf::signal_t{ "state", 0, 8, 0 },
              lin::ldf::signal_t{ "error_bit", 0, 1, 8 },
              lin::ldf::signal_t{ "fault_state", 0, 2, 9, "fault_enc" },
              lin::ldf::signal_t{
                  "angle", lin::ldf::signal::init_value::array_t{ 0x22, 0x11 }, 16, 16 } }));

    ASSERT_EQ(node.signal_encodings.size(), 2);
    EXPECT_STREQ(node.signal_encodings[0].name.c_str(), "fault_enc");
    EXPECT_STREQ(node.signal_encodings[1].name.c_str(), "position");

    auto &signal_encoding = node.signal_encodings[0];
    EXPECT_THAT(
        signal_encoding.values,
        testing::ElementsAreArray({
            lin::ldf::signal::encoding::logical_value_t{ 0, "no result" },
            lin::ldf::signal::encoding::logical_value_t{ 1, "failed" },
            lin::ldf::signal::encoding::logical_value_t{ 2, "passed" },
        }));
}
