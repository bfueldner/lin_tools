#include "lin/lexical/ncf/signal_encoding_type.hpp"
#include <gtest/gtest.h>

#include <lin/lexical/ncf/free_text.hpp>

TEST(test_lin_lexical_ncf_signal_encoding_type, encoding_logical_value)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ncf;

    std::string text{ "logical_value, 0, \"off\";" };
    encoding::logical_value_t logical_value{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::logical_value, x3::ascii::space, logical_value);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(logical_value.signal_value, 0);
    EXPECT_STREQ(logical_value.text_info.c_str(), "off");
}

TEST(test_lin_lexical_ncf_signal_encoding_type, encoding_physical_value)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ncf;

    std::string text{ "physical_value, 1, 254, 1, 100, \"lux\";" };
    encoding::physical_range_t physical_range;

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::physical_range, x3::ascii::space, physical_range);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(physical_range.min_value, 1);
    EXPECT_EQ(physical_range.max_value, 254);
    EXPECT_EQ(physical_range.scale, 1.0);
    EXPECT_EQ(physical_range.offset, 100.0);
    EXPECT_STREQ(physical_range.text_info.c_str(), "lux");
}

TEST(test_lin_lexical_ncf_signal_encoding_type, encoding_bcd_value)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ncf;

    std::string text{ "bcd_value ;" };
    encoding::bcd_value_t bcd_value;

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::bcd_value, x3::ascii::space, bcd_value);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());
}

TEST(test_lin_lexical_ncf_signal_encoding_type, encoding_ascii_value)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ncf;

    std::string text{ "ascii_value ;" };
    encoding::ascii_value_t ascii_value;

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::ascii_value, x3::ascii::space, ascii_value);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());
}

TEST(test_lin_lexical_ncf_signal_encoding_type, encoding_value)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ncf;

    std::string text{ "logical_value, 1, \"on\";" };
    encoding::value_t value;

    auto position = text.begin();
    auto result   = phrase_parse(position, text.end(), parser::value, x3::ascii::space, value);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *logic = std::get_if< encoding::logical_value_t >(&value);
    ASSERT_NE(logic, nullptr);
    EXPECT_EQ(logic->signal_value, 1);
    EXPECT_STREQ(logic->text_info.c_str(), "on");
}

TEST(test_lin_lexical_ncf_signal_encoding_type, encoding)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ncf;

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
        auto *logic = std::get_if< encoding::logical_value_t >(&encoding.value[0]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 0);
        EXPECT_STREQ(logic->text_info.c_str(), "Off");
    }
    {
        auto *physical = std::get_if< encoding::physical_range_t >(&encoding.value[1]);
        ASSERT_NE(physical, nullptr);
        EXPECT_EQ(physical->min_value, 1);
        EXPECT_EQ(physical->max_value, 254);
        EXPECT_EQ(physical->scale, 1.0);
        EXPECT_EQ(physical->offset, 100.0);
        EXPECT_STREQ(physical->text_info.c_str(), "lux");
    }
    {
        auto *logic = std::get_if< encoding::logical_value_t >(&encoding.value[2]);
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
        auto *logic = std::get_if< encoding::logical_value_t >(&encodings[0].value[0]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 0);
        EXPECT_STREQ(logic->text_info.c_str(), "off");
    }
    {
        auto *logic = std::get_if< encoding::logical_value_t >(&encodings[0].value[1]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 1);
        EXPECT_STREQ(logic->text_info.c_str(), "on");
    }
    {
        auto *logic = std::get_if< encoding::logical_value_t >(&encodings[0].value[2]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 2);
        EXPECT_STREQ(logic->text_info.c_str(), "error");
    }
    {
        auto *logic = std::get_if< encoding::logical_value_t >(&encodings[0].value[3]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 3);
        EXPECT_STREQ(logic->text_info.c_str(), "void");
    }
    // NOLINTEND(readability-container-data-pointer)
    EXPECT_STREQ(encodings[1].encoding_name.c_str(), "ErrorEncoding");
    EXPECT_EQ(encodings[1].value.size(), 2);
    // NOLINTBEGIN(readability-container-data-pointer)
    {
        auto *logic = std::get_if< encoding::logical_value_t >(&encodings[1].value[0]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 0);
        EXPECT_STREQ(logic->text_info.c_str(), "OK");
    }
    {
        auto *logic = std::get_if< encoding::logical_value_t >(&encodings[1].value[1]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 1);
        EXPECT_STREQ(logic->text_info.c_str(), "error");
    }
    // NOLINTEND(readability-container-data-pointer)
}
