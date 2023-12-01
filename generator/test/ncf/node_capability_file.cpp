#include <ios>
#include <sstream>

#include <gtest/gtest.h>

#include <lin/ncf/diagnostic.hpp>
#include <lin/ncf/frame.hpp>
#include <lin/ncf/general.hpp>
#include <lin/ncf/generator/node_capability_file.hpp>
#include <lin/ncf/node_capability_file.hpp>
#include <lin/ncf/signal.hpp>
#include <lin/ncf/signal_encoding.hpp>

/* 8.2.2 Node definition */

TEST(test_lin_ncf_generator, node_capability_file)
{
    using namespace lin::ncf;

    node_capability_file_t const node_capability_file{
        "2.2",
        { { "step_motor",
            { "2.2",
              0x05,
              0x20,
              1,
              general::bitrate::automatic_t{ general::bitrate::kbps_t{ 10 },
                                             general::bitrate::kbps_t{ 20 } },
              true },
            { diagnostic::nad::range_t{ 1, 3 }, 2, 100, 40, {}, {}, { 0xb0, 0xb2, 0xb7 } },
            { { frame::kind_t::publish,
                "node_status",
                4,
                10,
                100,
                {},
                { { "state", 0, 8, 0 },
                  { "fault_state", 0, 2, 9, "fault_enc" },
                  { "error_bit", 0, 1, 8 },
                  { "angle", signal::init_value::array_t{ 0x22, 0x11 }, 16, 16 } } },
              { frame::kind_t::subscribe,
                "control",
                1,
                {},
                100,
                {},
                { { "command", 0, 8, 0, "position" } } } },
            { { "position", { signal::encoding::physical_range_t{ 0, 199, 1.8, 0.0, "deg" } } },
              { "fault_enc",
                { signal::encoding::logical_value_t{ 0, "no result" },
                  signal::encoding::logical_value_t{ 1, "failed" },
                  signal::encoding::logical_value_t{ 2, "passed" } } } },
            { "error_bit", { "fault_state" } },
            { "step_motor signal values outside 0 - 199 are ignored" } } }
    };

    std::stringstream stream{};
    stream << std::uppercase << node_capability_file;
    EXPECT_EQ(
        stream.str(),
        "node_capability_file;\n"
        "LIN_language_version = \"2.2\";\n"
        "node step_motor {\n"
        "    general {\n"
        "        LIN_protocol_version = \"2.2\";\n"
        "        supplier = 0x0005;\n"
        "        function = 0x0020;\n"
        "        variant = 1;\n"
        "        bitrate = automatic min 10 kbps max 20 kbps;\n"
        "        sends_wake_up_signal = \"yes\";\n"
        "    }\n"
        "    diagnostic {\n"
        "        NAD = 1 to 3;\n"
        "        diagnostic_class = 2;\n"
        "        P2_min = 100 ms;\n"
        "        ST_min = 40 ms;\n"
        "        support_sid { 0xB0, 0xB2, 0xB7 };\n"
        "    }\n"
        "    frames {\n"
        "        publish node_status {\n"
        "            length = 4;\n"
        "            min_period = 10 ms;\n"
        "            max_period = 100 ms;\n"
        "            signals {\n"
        "                state {\n"
        "                    init_value = 0;\n"
        "                    size = 8;\n"
        "                    offset = 0;\n"
        "                }\n"
        "                fault_state {\n"
        "                    init_value = 0;\n"
        "                    size = 2;\n"
        "                    offset = 9;\n"
        "                    fault_enc;\n"
        "                }\n"
        "                error_bit {\n"
        "                    init_value = 0;\n"
        "                    size = 1;\n"
        "                    offset = 8;\n"
        "                }\n"
        "                angle {\n"
        "                    init_value = { 0x22, 0x11 };\n"
        "                    size = 16;\n"
        "                    offset = 16;\n"
        "                }\n"
        "            }\n"
        "        }\n"
        "        subscribe control {\n"
        "            length = 1;\n"
        "            max_period = 100 ms;\n"
        "            signals {\n"
        "                command {\n"
        "                    init_value = 0;\n"
        "                    size = 8;\n"
        "                    offset = 0;\n"
        "                    position;\n"
        "                }\n"
        "            }\n"
        "        }\n"
        "    }\n"
        "    encoding {\n"
        "        position {\n"
        "            physical_value, 0, 199, 1.8, 0, \"deg\";\n"
        "        }\n"
        "        fault_enc {\n"
        "            logical_value, 0, \"no result\";\n"
        "            logical_value, 1, \"failed\";\n"
        "            logical_value, 2, \"passed\";\n"
        "        }\n"
        "    }\n"
        "    status_management {\n"
        "        response_error = error_bit;\n"
        "        fault_state_signals = fault_state;\n"
        "    }\n"
        "    free_text {\n"
        "        \"step_motor signal values outside 0 - 199 are ignored\"\n"
        "    }\n"
        "}\n");
}
