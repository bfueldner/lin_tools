#include <sstream>

#include <gtest/gtest.h>

#include <lin/ldf/generator/signal_representation.hpp>
#include <lin/ldf/signal_representation.hpp>

/* 9.2.6.2 Signal representation definition */

TEST(test_lin_ldf_signal_representation_generator, signal_representation)
{
    using namespace lin::ldf::signal;

    representation_t const signal_representation{
        "LightEncoding", { "RightIntLightsSwitch", "LefttIntLightsSwitch" }
    };

    std::stringstream stream{};
    stream << signal_representation;
    EXPECT_EQ(stream.str(), "LightEncoding: RightIntLightsSwitch, LefttIntLightsSwitch;\n");
}

TEST(test_lin_ldf_signal_representation_generator, signal_representations)
{
    using namespace lin::ldf::signal;

    representations_t const signal_representations{
        { "Dig2Bit", { "InternalLightsRequest" } },
        { "ErrorEncoding", { "RSMerror", "LSMerror" } },
        { "FaultStateEncoding", { "IntError" } },
        { "LightEncoding", { "RightIntLightsSwitch", "LefttIntLightsSwitch" } }
    };

    std::stringstream stream{};
    stream << signal_representations;
    EXPECT_EQ(
        stream.str(),
        "Signal_representation {\n"
        "    Dig2Bit: InternalLightsRequest;\n"
        "    ErrorEncoding: RSMerror, LSMerror;\n"
        "    FaultStateEncoding: IntError;\n"
        "    LightEncoding: RightIntLightsSwitch, LefttIntLightsSwitch;\n"
        "}\n");
}
