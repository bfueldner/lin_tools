#include <sstream>

#include <gtest/gtest.h>

#include <lin/ncf/signal.hpp>

#include <lin/ncf/generator/signal.hpp>

/* 8.2.5.2 Signal definition */

TEST(test_lin_ncf_signal_generator, init_value_scalar)
{
    using namespace lin::ncf::signal;

    init_value_t const init_value{ 1 };

    std::stringstream stream{};
    stream << init_value;
    EXPECT_EQ(stream.str(), "1");
}

TEST(test_lin_ncf_signal_generator, init_value_array)
{
    using namespace lin::ncf::signal;

    init_value_t const init_value{ init_value_array_t{ 0x22, 0x11 } };

    std::stringstream stream{};
    stream << init_value;
    EXPECT_EQ(stream.str(), "{ 0x22, 0x11 }");
}

TEST(test_lin_ncf_signal_generator, signal_properties)
{
    using namespace lin::ncf::signal;

    signal_properties_t const signal_properties{ 0, 2, 9, "fault_enc" };

    std::stringstream stream{};
    stream << signal_properties;
    EXPECT_EQ(
        stream.str(),
        "init_value = 0;\n"
        "size = 2;\n"
        "offset = 9;\n"
        "fault_enc;\n");
}

TEST(test_lin_ncf_signal_generator, signal)
{
    using namespace lin::ncf;

    signal_t const signal{ "state", { 0, 8, 0 } };

    std::stringstream stream{};
    stream << signal;
    EXPECT_EQ(
        stream.str(),
        "state {\n"
        "    init_value = 0;\n"
        "    size = 8;\n"
        "    offset = 0;\n"
        "}\n");
}

TEST(test_lin_ncf_signal_generator, signals)
{
    using namespace lin::ncf;

    signals_t const signals{ { "state", { 0, 8, 0 } },
                             { "fault_state", { 0, 2, 9, "fault_enc" } },
                             { "error_bit", { 0, 1, 8 } },
                             { "angle", { signal::init_value_array_t{ 0x22, 0x11 }, 16, 16 } } };

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

/* 8.2.5.3 Signal encoding type definition */

TEST(test_lin_ncf_signal_encoding_type_parser, encoding)
{
    using namespace lin::ncf::signal_encoding_type;

    encoding_t const encoding{ "position", { physical_range_t{ 0, 199, 1.8, 0.0, "deg" } } };

    std::stringstream stream{};
    stream << encoding;
    EXPECT_EQ(
        stream.str(),
        "position {\n"
        "    physical_value, 0, 199, 1.8, 0, \"deg\";\n"
        "}\n");
}

TEST(test_lin_ncf_signal_encoding_type_parser, encoding_definition)
{
    using namespace lin::ncf::signal_encoding_type;

    encodings_t const encodings{ { "position", { physical_range_t{ 0, 199, 1.8, 0.0, "deg" } } },
                                 { "fault_enc",
                                   { logical_value_t{ 0, "no result" },
                                     logical_value_t{ 1, "failed" },
                                     logical_value_t{ 2, "passed" } } } };

    std::stringstream stream{};
    stream << encodings;
    EXPECT_EQ(
        stream.str(),
        "encoding {\n"
        "    position {\n"
        "        physical_value, 0, 199, 1.8, 0, \"deg\";\n"
        "    }\n"
        "    fault_enc {\n"
        "        logical_value, 0, \"no result\";\n"
        "        logical_value, 1, \"failed\";\n"
        "        logical_value, 2, \"passed\";\n"
        "    }\n"
        "}\n");
}
