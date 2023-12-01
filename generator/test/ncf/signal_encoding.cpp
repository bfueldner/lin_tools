#include <sstream>

#include <gtest/gtest.h>

#include <lin/ncf/generator/signal_encoding.hpp>
#include <lin/ncf/signal_encoding.hpp>

/* 8.2.5.3 Signal encoding type definition */

TEST(test_lin_ncf_signal_encoding_generator, signal_encoding)
{
    using namespace lin::ncf::signal;

    encoding_t const encoding{ "position",
                               { encoding::physical_range_t{ 0, 199, 1.8, 0.0, "deg" } } };

    std::stringstream stream{};
    stream << encoding;
    EXPECT_EQ(
        stream.str(),
        "position {\n"
        "    physical_value, 0, 199, 1.8, 0, \"deg\";\n"
        "}\n");
}

TEST(test_lin_ncf_signal_encoding_generator, signal_encodings)
{
    using namespace lin::ncf::signal;

    encodings_t const encodings{ { "position",
                                   { encoding::physical_range_t{ 0, 199, 1.8, 0.0, "deg" } } },
                                 { "fault_enc",
                                   { encoding::logical_value_t{ 0, "no result" },
                                     encoding::logical_value_t{ 1, "failed" },
                                     encoding::logical_value_t{ 2, "passed" } } } };

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
