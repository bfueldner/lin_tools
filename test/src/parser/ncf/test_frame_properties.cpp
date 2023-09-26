#include <string>

#include <gtest/gtest.h>

#include <lin/ncf/frame_properties.hpp>

#include <lin/ncf/parser/frame_properties.hpp>

TEST(test_lin_ncf_frame_properties_parser, frame_properties)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string text{ "length = 4; min_period = 10 ms; max_period = 100 ms;" };
    frame_properties_t frame_properties;

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::frame_properties, x3::ascii::space, frame_properties);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(frame_properties.length, 4);
    EXPECT_EQ(frame_properties.min_period, 10);
    EXPECT_EQ(frame_properties.max_period, 100);
    EXPECT_STREQ(frame_properties.event_triggered_frame.c_str(), "");
}
