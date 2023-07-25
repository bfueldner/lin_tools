#include <gtest/gtest.h>

#include <lin/lexical/ncf/signal_encoding_type.hpp>

TEST(test_lin_lexical_ncf_signal_encoding_type, encoding)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ncf;
    using namespace lin::lexical::common;

    std::string text{
        "LightEncoding {"
        "    logical_value, 0, \"Off\";"
        "    physical_value, 1, 254, 1, 100, \"lux\";"
        "    logical_value, 255, \"error\";"
        "}"
    };
    encoding_t encoding;

    auto position = text.begin();
    auto result = phrase_parse(position, text.end(), parser::encoding, x3::ascii::space, encoding);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(encoding.encoding_name.c_str(), "LightEncoding");
    EXPECT_EQ(encoding.value.size(), 3);

    // NOLINTBEGIN(readability-container-data-pointer)
    {
        auto *logic = std::get_if< signal_encoding::logical_value_t >(&encoding.value[0]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 0);
        EXPECT_STREQ(logic->text_info.c_str(), "Off");
    }
    {
        auto *physical = std::get_if< signal_encoding::physical_range_t >(&encoding.value[1]);
        ASSERT_NE(physical, nullptr);
        EXPECT_EQ(physical->min_value, 1);
        EXPECT_EQ(physical->max_value, 254);
        EXPECT_EQ(physical->scale, 1.0);
        EXPECT_EQ(physical->offset, 100.0);
        EXPECT_STREQ(physical->text_info.c_str(), "lux");
    }
    {
        auto *logic = std::get_if< signal_encoding::logical_value_t >(&encoding.value[2]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 255);
        EXPECT_STREQ(logic->text_info.c_str(), "error");
    }
    // NOLINTEND(readability-container-data-pointer)
}

TEST(test_lin_lexical_ncf_signal_encoding_type, encodings)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ncf;
    using namespace lin::lexical::common;

    std::string text{
        "encoding {"
        "    Dig2Bit {"
        "        logical_value, 0, \"off\";"
        "        logical_value, 1, \"on\";"
        "        logical_value, 2, \"error\";"
        "        logical_value, 3, \"void\";"
        "    }"
        "    ErrorEncoding {"
        "        logical_value, 0, \"OK\";"
        "        logical_value, 1, \"error\";"
        "    }"
        "}"
    };
    encodings_t encodings;

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::encoding_definition, x3::ascii::space, encodings);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(encodings.size(), 2);
    EXPECT_STREQ(encodings[0].encoding_name.c_str(), "Dig2Bit");
    ASSERT_EQ(encodings[0].value.size(), 4);
    // NOLINTBEGIN(readability-container-data-pointer)
    {
        auto *logic = std::get_if< signal_encoding::logical_value_t >(&encodings[0].value[0]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 0);
        EXPECT_STREQ(logic->text_info.c_str(), "off");
    }
    {
        auto *logic = std::get_if< signal_encoding::logical_value_t >(&encodings[0].value[1]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 1);
        EXPECT_STREQ(logic->text_info.c_str(), "on");
    }
    {
        auto *logic = std::get_if< signal_encoding::logical_value_t >(&encodings[0].value[2]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 2);
        EXPECT_STREQ(logic->text_info.c_str(), "error");
    }
    {
        auto *logic = std::get_if< signal_encoding::logical_value_t >(&encodings[0].value[3]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 3);
        EXPECT_STREQ(logic->text_info.c_str(), "void");
    }
    // NOLINTEND(readability-container-data-pointer)
    EXPECT_STREQ(encodings[1].encoding_name.c_str(), "ErrorEncoding");
    EXPECT_EQ(encodings[1].value.size(), 2);
    // NOLINTBEGIN(readability-container-data-pointer)
    {
        auto *logic = std::get_if< signal_encoding::logical_value_t >(&encodings[1].value[0]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 0);
        EXPECT_STREQ(logic->text_info.c_str(), "OK");
    }
    {
        auto *logic = std::get_if< signal_encoding::logical_value_t >(&encodings[1].value[1]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 1);
        EXPECT_STREQ(logic->text_info.c_str(), "error");
    }
    // NOLINTEND(readability-container-data-pointer)
}
