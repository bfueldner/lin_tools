#include <sstream>

#include <gtest/gtest.h>

#include <lin/ncf/frame.hpp>

#include <lin/ncf/generator/frame.hpp>

TEST(test_lin_ncf_frame_generator, frame_properties)
{
    using namespace lin::ncf;

    frame_properties_t const frame_properties{ 4, 10, 100 };

    std::stringstream stream{};
    stream << frame_properties;
    EXPECT_EQ(
        stream.str(),
        "length = 4;\n"
        "min_period = 10 ms;\n"
        "max_period = 100 ms;\n");
}

TEST(test_lin_ncf_frame_generator, frame_kind)
{
    using namespace lin::ncf::frame;

    frame_kind_t const frame_kind{ frame_kind_t::publish };

    std::stringstream stream{};
    stream << frame_kind;
    EXPECT_EQ(stream.str(), "publish");
}

TEST(test_lin_ncf_frame_generator, single_frame)
{
    using namespace lin::ncf::frame;

    single_frame_t const single_frame{ frame_kind_t::publish,
                                       "node_status",
                                       { 4, 10, 100 },
                                       { { "state", { 0, 8, 0 } },
                                         { "fault_state", { 0, 2, 9, "fault_enc" } } } };

    std::stringstream stream{};
    stream << single_frame;
    EXPECT_EQ(
        stream.str(),
        "publish node_status {\n"
        "    length = 4;\n"
        "    min_period = 10 ms;\n"
        "    max_period = 100 ms;\n"
        "    signals {\n"
        "        state {\n"
        "            init_value = 0;\n"
        "            size = 8;\n"
        "            offset = 0;\n"
        "        }\n"
        "        fault_state {\n"
        "            init_value = 0;\n"
        "            size = 2;\n"
        "            offset = 9;\n"
        "            fault_enc;\n"
        "        }\n"
        "    }\n"
        "}\n");
}

TEST(test_lin_ncf_frame_generator, frames)
{
    using namespace lin::ncf;

    frames_t const frames{
        { frame::frame_kind_t::publish,
          "node_status",
          { 4, 10, 100 },
          { { "state", { 0, 8, 0 } },
            { "fault_state", { 0, 2, 9, "fault_enc" } },
            { "error_bit", { 0, 1, 8 } },
            { "angle", { signal::init_value_array_t{ 0x22, 0x11 }, 16, 16 } } } },
        { frame::frame_kind_t::subscribe,
          "control",
          { 1, {}, 100 },
          { { "command", { 0, 8, 0, "position" } } } }
    };

    std::stringstream stream{};
    stream << frames;
    EXPECT_EQ(
        stream.str(),
        "frames {\n"
        "    publish node_status {\n"
        "        length = 4;\n"
        "        min_period = 10 ms;\n"
        "        max_period = 100 ms;\n"
        "        signals {\n"
        "            state {\n"
        "                init_value = 0;\n"
        "                size = 8;\n"
        "                offset = 0;\n"
        "            }\n"
        "            fault_state {\n"
        "                init_value = 0;\n"
        "                size = 2;\n"
        "                offset = 9;\n"
        "                fault_enc;\n"
        "            }\n"
        "            error_bit {\n"
        "                init_value = 0;\n"
        "                size = 1;\n"
        "                offset = 8;\n"
        "            }\n"
        "            angle {\n"
        "                init_value = { 0x22, 0x11 };\n"
        "                size = 16;\n"
        "                offset = 16;\n"
        "            }\n"
        "        }\n"
        "    }\n"
        "    subscribe control {\n"
        "        length = 1;\n"
        "        max_period = 100 ms;\n"
        "        signals {\n"
        "            command {\n"
        "                init_value = 0;\n"
        "                size = 8;\n"
        "                offset = 0;\n"
        "                position;\n"
        "            }\n"
        "        }\n"
        "    }\n"
        "}\n");
}
