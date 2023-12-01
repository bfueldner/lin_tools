#include <string>
#include <vector>

#include <gtest/gtest.h>

#include <lin/ldf/parser/signal_representation.hpp>
#include <lin/ldf/signal_representation.hpp>

/* 9.2.6.2 Signal representation definition */

TEST(test_lin_ldf_signal_parser, signal_representation)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{ "LightEncoding: RightIntLightsSwitch, LefttIntLightsSwitch;" };
    signal::representation_t representation{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::signal_representation, x3::ascii::space, representation);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(representation.name.c_str(), "LightEncoding");
    ASSERT_EQ(representation.signals.size(), 2);
    EXPECT_STREQ(representation.signals[0].c_str(), "RightIntLightsSwitch");
    EXPECT_STREQ(representation.signals[1].c_str(), "LefttIntLightsSwitch");
}

TEST(test_lin_ldf_signal_parser, signal_representations)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ldf;

    std::string text{
        "Signal_representation {"
        "    Dig2Bit: InternalLightsRequest;"
        "    ErrorEncoding: RSMerror, LSMerror;"
        "    FaultStateEncoding: IntError;"
        "    LightEncoding: RightIntLightsSwitch, LefttIntLightsSwitch;"
        "}"
    };
    signal::representations_t representations{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::signal_representations, x3::ascii::space, representations);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(representations.size(), 4);
    EXPECT_STREQ(representations[0].name.c_str(), "Dig2Bit");
    ASSERT_EQ(representations[0].signals.size(), 1);
    EXPECT_STREQ(representations[0].signals[0].c_str(), "InternalLightsRequest");
    EXPECT_STREQ(representations[1].name.c_str(), "ErrorEncoding");
    ASSERT_EQ(representations[1].signals.size(), 2);
    EXPECT_STREQ(representations[1].signals[0].c_str(), "RSMerror");
    EXPECT_STREQ(representations[1].signals[1].c_str(), "LSMerror");
    EXPECT_STREQ(representations[2].name.c_str(), "FaultStateEncoding");
    ASSERT_EQ(representations[2].signals.size(), 1);
    EXPECT_STREQ(representations[2].signals[0].c_str(), "IntError");
    EXPECT_STREQ(representations[3].name.c_str(), "LightEncoding");
    ASSERT_EQ(representations[3].signals.size(), 2);
    EXPECT_STREQ(representations[3].signals[0].c_str(), "RightIntLightsSwitch");
    EXPECT_STREQ(representations[3].signals[1].c_str(), "LefttIntLightsSwitch");
}
