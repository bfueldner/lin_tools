#include <sstream>

#include <gtest/gtest.h>

#include <lin/ldf/frame_sporadic.hpp>
#include <lin/ldf/generator/frame_sporadic.hpp>

/* 9.2.4.2 Sporadic frames */

TEST(test_lin_ldf_frame_generator, sporadic_frame)
{
    using namespace lin::ldf::frame;

    sporadic_t const sporadic_frame{ "SPRD_Frm", { "LSM_Frm1" } };

    std::stringstream stream{};
    stream << sporadic_frame;
    EXPECT_EQ(stream.str(), "SPRD_Frm: LSM_Frm1;\n");
}

TEST(test_lin_ldf_frame_generator, sporadic_frames)
{
    using namespace lin::ldf::frame;

    sporadics_t const sporadic_frames{ { "SPRD_Frm1", { "LSM_Frm1" } },
                                       { "SPRD_Frm2", { "RSM_Frm1", "RSM_Frm2" } } };

    std::stringstream stream{};
    stream << sporadic_frames;
    EXPECT_EQ(
        stream.str(),
        "Sporadic_frames {\n"
        "    SPRD_Frm1: LSM_Frm1;\n"
        "    SPRD_Frm2: RSM_Frm1, RSM_Frm2;\n"
        "}\n");
}
