#include <sstream>

#include <gtest/gtest.h>

#include <lin/ldf/frame_unconditional.hpp>
#include <lin/ldf/generator/frame_unconditional.hpp>

/* 9.2.4.1 Unconditional frames */

TEST(test_lin_ldf_frame_generator, unconditional_frame_signal)
{
    using namespace lin::ldf::frame::unconditional;

    signal_t const signal{ "RightIntLightsSwitch", 8 };

    std::stringstream stream{};
    stream << signal;
    EXPECT_EQ(stream.str(), "RightIntLightsSwitch, 8;\n");
}

TEST(test_lin_ldf_frame_generator, unconditional_frame)
{
    using namespace lin::ldf::frame;

    unconditional_t const unconditional_frame{
        "LSM_Frm2", 0x03, "LSM", 1, { { "LSMerror", 0 }, { "IntTest", 1 } }
    };

    std::stringstream stream{};
    stream << unconditional_frame;
    EXPECT_EQ(
        stream.str(),
        "LSM_Frm2: 0x03, LSM, 1 {\n"
        "    LSMerror, 0;\n"
        "    IntTest, 1;\n"
        "}\n");
}

TEST(test_lin_ldf_frame_generator, unconditional_frames)
{
    using namespace lin::ldf::frame;

    unconditionals_t const unconditional_frames{
        { "CEM_Frm1", 0x01, "CEM", 1, { { "InternalLightsRequest", 0 } } },
        { "LSM_Frm1", 0x02, "LSM", 2, { { "LeftIntLightsSwitch", 8 } } }
    };

    std::stringstream stream{};
    stream << unconditional_frames;
    EXPECT_EQ(
        stream.str(),
        "Frames {\n"
        "    CEM_Frm1: 0x01, CEM, 1 {\n"
        "        InternalLightsRequest, 0;\n"
        "    }\n"
        "    LSM_Frm1: 0x02, LSM, 2 {\n"
        "        LeftIntLightsSwitch, 8;\n"
        "    }\n"
        "}\n");
}
