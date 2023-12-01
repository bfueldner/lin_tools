#include <sstream>

#include <gtest/gtest.h>

#include <lin/ldf/generator/signal_standard.hpp>
#include <lin/ldf/signal_standard.hpp>

/* 9.2.3.1 Standard signals */

TEST(test_lin_ldf_signal_standard_generator, standard_signal)
{
    using namespace lin::ldf::signal;

    standard_t const standard_signal{ "InternalLightsRequest", 2, 0, "CEM", { "LSM", "RSM" } };

    std::stringstream stream{};
    stream << standard_signal;
    EXPECT_EQ(stream.str(), "InternalLightsRequest: 2, 0, CEM, LSM, RSM;\n");
}

TEST(test_lin_ldf_signal_standard_generator, standard_signals)
{
    using namespace lin::ldf::signal;

    standards_t const standard_signals{ { "LSMerror", 1, 0, "LSM" },
                                        { "RSMerror", 1, 1, "RSM", { "CEM" } } };

    std::stringstream stream{};
    stream << standard_signals;
    EXPECT_EQ(
        stream.str(),
        "Signals {\n"
        "    LSMerror: 1, 0, LSM;\n"
        "    RSMerror: 1, 1, RSM, CEM;\n"
        "}\n");
}
