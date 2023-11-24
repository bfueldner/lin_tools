#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <lin/ldf/frame_sporadic.hpp>
#include <lin/ldf/parser/frame_sporadic.hpp>

/* 9.2.4.2 Sporadic frames */

TEST(test_lin_ldf_frame_sporadic_parser, sporadic_frame)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "SPRD_Frm: LSM_Frm1;" };
    frame::sporadic_t frame{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::sporadic_frame, x3::ascii::space, frame);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(frame.name.c_str(), "SPRD_Frm");
    ASSERT_EQ(frame.frames.size(), 1);
    EXPECT_STREQ(frame.frames[0].c_str(), "LSM_Frm1");
}

TEST(test_lin_ldf_frame_sporadic_parser, sporadic_frames)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "Sporadic_frames {"
        "    SPRD_Frm1: LSM_Frm1;"
        "    SPRD_Frm2: RSM_Frm1, RSM_Frm2;"
        "}"
    };
    frame::sporadics_t frames{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::sporadic_frames, x3::ascii::space, frames);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(frames.size(), 2);
    EXPECT_STREQ(frames[0].name.c_str(), "SPRD_Frm1");
    ASSERT_EQ(frames[0].frames.size(), 1);
    EXPECT_EQ(frames[0].frames, (std::vector< std::string >{ "LSM_Frm1" }));
    EXPECT_STREQ(frames[1].name.c_str(), "SPRD_Frm2");
    EXPECT_EQ(frames[1].frames, (std::vector< std::string >{ "RSM_Frm1", "RSM_Frm2" }));
}
