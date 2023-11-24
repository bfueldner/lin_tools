#include <sstream>

#include <gtest/gtest.h>

#include <lin/ldf/generator/signal_encoding.hpp>
#include <lin/ldf/signal_encoding.hpp>

/* 9.2.6.1 Signal encoding type definition */

TEST(test_lin_ldf_signal_encoding_generator, signal_encoding)
{
    using namespace lin::ldf::signal;

    encoding_t const signal_encoding{ "LightEncoding",
                                      { encoding::logical_value_t{ 0, "Off" },
                                        encoding::physical_range_t{ 1, 254, 1.0, 100.0, "lux" },
                                        encoding::logical_value_t{ 255, "error" } } };

    std::stringstream stream{};
    stream << signal_encoding;
    EXPECT_EQ(
        stream.str(),
        "LightEncoding {\n"
        "    logical_value, 0, \"Off\";\n"
        "    physical_value, 1, 254, 1, 100, \"lux\";\n"
        "    logical_value, 255, \"error\";\n"
        "}\n");
}

TEST(test_lin_ldf_signal_encoding_generator, signal_encodings)
{
    using namespace lin::ldf::signal;

    encodings_t const signal_encodings{ { "Dig2Bit",
                                          { encoding::logical_value_t{ 0, "off" },
                                            encoding::logical_value_t{ 1, "on" },
                                            encoding::logical_value_t{ 2, "error" },
                                            encoding::logical_value_t{ 3, "void" } } },
                                        { "LightEncoding",
                                          { encoding::logical_value_t{ 0, "Off" },
                                            encoding::physical_range_t{ 1, 254, 1.0, 100.0, "lux" },
                                            encoding::logical_value_t{ 255, "error" } } } };

    std::stringstream stream{};
    stream << signal_encodings;
    EXPECT_EQ(
        stream.str(),
        "Signal_encoding_types {\n"
        "    Dig2Bit {\n"
        "        logical_value, 0, \"off\";\n"
        "        logical_value, 1, \"on\";\n"
        "        logical_value, 2, \"error\";\n"
        "        logical_value, 3, \"void\";\n"
        "    }\n"
        "    LightEncoding {\n"
        "        logical_value, 0, \"Off\";\n"
        "        physical_value, 1, 254, 1, 100, \"lux\";\n"
        "        logical_value, 255, \"error\";\n"
        "    }\n"
        "}\n");
}
