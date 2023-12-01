#include <sstream>

#include <gtest/gtest.h>

#include <lin/ncf/generator/signal.hpp>
#include <lin/ncf/signal.hpp>

/* 8.2.5.2 Signal definition */

TEST(test_lin_ncf_signal_generator, signal)
{
    using namespace lin::ncf;

    signal_t const signal{ "state", 0, 2, 9, "fault_enc" };

    std::stringstream stream{};
    stream << signal;
    EXPECT_EQ(
        stream.str(),
        "state {\n"
        "    init_value = 0;\n"
        "    size = 2;\n"
        "    offset = 9;\n"
        "    fault_enc;\n"
        "}\n");
}

TEST(test_lin_ncf_signal_generator, signals)
{
    using namespace lin::ncf;

    signals_t const signals{ { "state", 0, 8, 0 },
                             { "fault_state", 0, 2, 9, "fault_enc" },
                             { "error_bit", 0, 1, 8 },
                             { "angle", signal::init_value::array_t{ 0x22, 0x11 }, 16, 16 } };

    std::stringstream stream{};
    stream << signals;
    EXPECT_EQ(
        stream.str(),
        "signals {\n"
        "    state {\n"
        "        init_value = 0;\n"
        "        size = 8;\n"
        "        offset = 0;\n"
        "    }\n"
        "    fault_state {\n"
        "        init_value = 0;\n"
        "        size = 2;\n"
        "        offset = 9;\n"
        "        fault_enc;\n"
        "    }\n"
        "    error_bit {\n"
        "        init_value = 0;\n"
        "        size = 1;\n"
        "        offset = 8;\n"
        "    }\n"
        "    angle {\n"
        "        init_value = { 0x22, 0x11 };\n"
        "        size = 16;\n"
        "        offset = 16;\n"
        "    }\n"
        "}\n");
}
