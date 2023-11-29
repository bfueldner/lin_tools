#include <variant>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <lin/common/signal_encoding.hpp>
#include <lin/ncf/command/function.hpp>
#include <lin/ncf/diagnostic.hpp>
#include <lin/ncf/frame.hpp>
#include <lin/ncf/free_text.hpp>
#include <lin/ncf/general.hpp>
#include <lin/ncf/node.hpp>
#include <lin/ncf/node_capability_file.hpp>
#include <lin/ncf/signal.hpp>
#include <lin/ncf/signal_encoding.hpp>
#include <lin/ncf/status_management.hpp>

class test_lin_ncf_function_command: public testing::Test
{
  public:
    //using namespace lin::ncf;

    lin::ncf::node_capability_file_t
        ncf{ .language_version = "2.2",
             .nodes            = lin::ncf::nodes_t{ lin::ncf::node_t{
                            .name    = "step_motor",
                            .general = lin::ncf::general_t{ .protocol_version = "2.2",
                                                            .supplier         = 0x05,
                                                            .function         = 0x20,
                                                            .variant          = 1,
                                                            .bitrate =
                                                     lin::ncf::general::bitrate::select_t{
                                                         lin::ncf::general::bitrate::kbps_t{ 19.2 },
                                                         lin::ncf::general::bitrate::kbps_t{ 9.6 },
                                                         lin::ncf::general::bitrate::kbps_t{ 4.8 },
                                                     },
                                                            .sends_wake_up_signal = true },
                            .diagnostic =
                     lin::ncf::diagnostic_t{
                                    .nad              = lin::ncf::diagnostic::nad::sequence_t{ 4, 1, 3, 2 },
                                    .diagnostic_class = 2,
                                    .p2_min           = 100,
                                    .st_min           = 40,
                                    .support_sids     = { 0xb7, 0xb2, 0xb0 } },
                            .frames =
                     lin::ncf::frames_t{
                         lin::ncf::frame_t{
                                        .kind       = lin::ncf::frame::kind_t::publish,
                                        .name       = "node_status",
                                        .size       = 4,
                                        .min_period = 10,
                                        .max_period = 100,
                                        .signals    = { lin::ncf::signal_t{ "state", 0, 8, 0 },
                                                        lin::ncf::signal_t{ "fault_state", 0, 2, 9, "fault_enc" },
                                                        lin::ncf::signal_t{ "error_bit", 0, 1, 8 },
                                                        lin::ncf::signal_t{
                                              "angle",
                                              lin::ncf::signal::init_value::array_t{ 0x22, 0x11 },
                                              16,
                                              16 }, } },
                         lin::ncf::frame_t{ .kind       = lin::ncf::frame::kind_t::subscribe,
                                                       .name       = "control",
                                                       .size       = 1,
                                                       .max_period = 100,
                                                       .signals    = { lin::ncf::signal_t{ "command",
                                                                             0,
                                                                             8,
                                                                             0,
                                                                             "position" } } } },
                            .signal_encodings =
                     lin::ncf::signal::encodings_t{
                         lin::ncf::signal::encoding_t{
                                        .name   = "position",
                                        .values = { lin::ncf::signal::encoding::
                                                        physical_range_t{ 0, 199, 1.8, 0.0, "deg" } } },
                         lin::ncf::signal::encoding_t{
                                        .name   = "fault_enc",
                                        .values = { lin::ncf::signal::encoding::logical_value_t{ 1, "failed" },
                                                    lin::ncf::signal::encoding::logical_value_t{ 0,"no result" },
                                                    lin::ncf::signal::encoding::logical_value_t{ 2, "passed" }, } } },
                            .status_management =
                     lin::ncf::status_management_t{ .response_error      = "error_bit",
                                                               .fault_state_signals = { "fault_state" } },
                            .free_text =
                     lin::ncf::free_text_t{
                         "step_motor signal values outside 0 - 199 are ignored" } } }

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

namespace lin::ncf {

bool operator==(const signal_t &signal1, const signal_t &signal2)
{
    return (signal1.name == signal2.name) &&
           (signal1.init_value.index() == signal2.init_value.index()) &&
           (signal1.size == signal2.size) && (signal1.offset == signal2.offset) &&
           (signal1.encoding == signal2.encoding);
}

}    // namespace lin::ncf

TEST_F(test_lin_ncf_function_command, sort)
{
    using namespace lin::ncf::command;

    function::sort(ncf);

    ASSERT_EQ(ncf.nodes.size(), 1);

    auto &node = ncf.nodes[0];
    ASSERT_EQ(node.general.bitrate.index(), 1);
    auto *bitrate = std::get_if< lin::ncf::general::bitrate::select_t >(&node.general.bitrate);
    EXPECT_THAT(*bitrate, testing::ElementsAre(4.8, 9.6, 19.2));

    ASSERT_EQ(node.diagnostic.nad.index(), 1);
    auto *nad = std::get_if< lin::ncf::diagnostic::nad::sequence_t >(&node.diagnostic.nad);
    EXPECT_THAT(*nad, testing::ElementsAre(1, 2, 3, 4));

    EXPECT_THAT(node.diagnostic.support_sids, testing::ElementsAre(0xb0, 0xb2, 0xb7));

    ASSERT_EQ(node.frames.size(), 2);

    auto &frame = node.frames[0];
    EXPECT_THAT(
        frame.signals,
        testing::ElementsAreArray(
            { lin::ncf::signal_t{ "state", 0, 8, 0 },
              lin::ncf::signal_t{ "error_bit", 0, 1, 8 },
              lin::ncf::signal_t{ "fault_state", 0, 2, 9, "fault_enc" },
              lin::ncf::signal_t{
                  "angle", lin::ncf::signal::init_value::array_t{ 0x22, 0x11 }, 16, 16 } }));

    ASSERT_EQ(node.signal_encodings.size(), 2);
    EXPECT_STREQ(node.signal_encodings[0].name.c_str(), "fault_enc");
    EXPECT_STREQ(node.signal_encodings[1].name.c_str(), "position");

    auto &signal_encoding = node.signal_encodings[0];
    EXPECT_THAT(
        signal_encoding.values,
        testing::ElementsAreArray({
            lin::ncf::signal::encoding::logical_value_t{ 0, "no result" },
            lin::ncf::signal::encoding::logical_value_t{ 1, "failed" },
            lin::ncf::signal::encoding::logical_value_t{ 2, "passed" },
        }));
}
