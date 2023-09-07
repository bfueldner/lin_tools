#include <gtest/gtest.h>

#include <lin/lexical/ldf/signal_representation.hpp>

/* 9.2.6.2 Signal representation definition */

TEST(test_lin_lexical_ncf_signal_representation, signal_representation)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf;

    std::string text{ "LightEncoding: RightIntLightsSwitch, LefttIntLightsSwitch;" };
    signal_representation_t signal_representation;

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::signal_representation,
        x3::ascii::space,
        signal_representation);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(signal_representation.signal_encoding_type_name.c_str(), "LightEncoding");
    ASSERT_EQ(signal_representation.signal_names.size(), 2);
    EXPECT_STREQ(signal_representation.signal_names[0].c_str(), "RightIntLightsSwitch");
    EXPECT_STREQ(signal_representation.signal_names[1].c_str(), "LefttIntLightsSwitch");
}

TEST(test_lin_lexical_ncf_signal_representation, signal_representations)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf;

    std::string text{
        "Signal_representation {"
        "    Dig2Bit: InternalLightsRequest;"
        "    ErrorEncoding: RSMerror, LSMerror;"
        "    FaultStateEncoding: IntError;"
        "    LightEncoding: RightIntLightsSwitch, LefttIntLightsSwitch;"
        "}"
    };
    signal_representations_t signal_representations;

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::signal_representations,
        x3::ascii::space,
        signal_representations);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(signal_representations.size(), 4);
    EXPECT_STREQ(signal_representations[0].signal_encoding_type_name.c_str(), "Dig2Bit");
    ASSERT_EQ(signal_representations[0].signal_names.size(), 1);
    EXPECT_STREQ(signal_representations[0].signal_names[0].c_str(), "InternalLightsRequest");
    EXPECT_STREQ(signal_representations[1].signal_encoding_type_name.c_str(), "ErrorEncoding");
    ASSERT_EQ(signal_representations[1].signal_names.size(), 2);
    EXPECT_STREQ(signal_representations[1].signal_names[0].c_str(), "RSMerror");
    EXPECT_STREQ(signal_representations[1].signal_names[1].c_str(), "LSMerror");
    EXPECT_STREQ(signal_representations[2].signal_encoding_type_name.c_str(), "FaultStateEncoding");
    ASSERT_EQ(signal_representations[2].signal_names.size(), 1);
    EXPECT_STREQ(signal_representations[2].signal_names[0].c_str(), "IntError");
    EXPECT_STREQ(signal_representations[3].signal_encoding_type_name.c_str(), "LightEncoding");
    ASSERT_EQ(signal_representations[3].signal_names.size(), 2);
    EXPECT_STREQ(signal_representations[3].signal_names[0].c_str(), "RightIntLightsSwitch");
    EXPECT_STREQ(signal_representations[3].signal_names[1].c_str(), "LefttIntLightsSwitch");
}
