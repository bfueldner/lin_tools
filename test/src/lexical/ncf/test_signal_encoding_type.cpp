#include <gtest/gtest.h>

#include <lin/lexical/ncf/signal_encoding_type.hpp>

TEST(test_lin_lexical_ncf_signal_encoding_type, encoding)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ncf;
    using namespace lin::lexical::common;

    std::string text{ " position {physical_value, 0, 199, 1.8, 0, \"deg\";}" };
    encoding_t encoding;

    auto position = text.begin();
    auto result = phrase_parse(position, text.end(), parser::encoding, x3::ascii::space, encoding);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(encoding.encoding_name.c_str(), "position");
    EXPECT_EQ(encoding.value.size(), 1);
    {
        auto *physical = std::get_if< signal_encoding::physical_range_t >(encoding.value.data());
        ASSERT_NE(physical, nullptr);
        EXPECT_EQ(physical->min_value, 0);
        EXPECT_EQ(physical->max_value, 199);
        EXPECT_EQ(physical->scale, 1.8);
        EXPECT_EQ(physical->offset, 0.0);
        EXPECT_STREQ(physical->text_info.c_str(), "deg");
    }
}

TEST(test_lin_lexical_ncf_signal_encoding_type, encoding_definition)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ncf;
    using namespace lin::lexical::common;

    std::string text{
        "encoding { "
        "    position {physical_value, 0, 199, 1.8, 0, \"deg\";}"
        "    fault_enc {logical_value, 0, \"no result\";"
        "               logical_value, 1, \"failed\";"
        "               logical_value, 2, \"passed\";}"
        "}"
    };
    encodings_t encodings;

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::encoding_definition, x3::ascii::space, encodings);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(encodings.size(), 2);
    EXPECT_STREQ(encodings[0].encoding_name.c_str(), "position");
    ASSERT_EQ(encodings[0].value.size(), 1);
    {
        auto *physical =
            std::get_if< signal_encoding::physical_range_t >(encodings[0].value.data());
        ASSERT_NE(physical, nullptr);
        EXPECT_EQ(physical->min_value, 0);
        EXPECT_EQ(physical->max_value, 199);
        EXPECT_EQ(physical->scale, 1.8);
        EXPECT_EQ(physical->offset, 0.0);
        EXPECT_STREQ(physical->text_info.c_str(), "deg");
    }
    EXPECT_STREQ(encodings[1].encoding_name.c_str(), "fault_enc");
    ASSERT_EQ(encodings[1].value.size(), 3);
    // NOLINTBEGIN(readability-container-data-pointer)
    {
        auto *logic = std::get_if< signal_encoding::logical_value_t >(&encodings[1].value[0]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 0);
        EXPECT_STREQ(logic->text_info.c_str(), "no result");
    }
    {
        auto *logic = std::get_if< signal_encoding::logical_value_t >(&encodings[1].value[1]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 1);
        EXPECT_STREQ(logic->text_info.c_str(), "failed");
    }
    {
        auto *logic = std::get_if< signal_encoding::logical_value_t >(&encodings[1].value[2]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 2);
        EXPECT_STREQ(logic->text_info.c_str(), "passed");
    }
    // NOLINTEND(readability-container-data-pointer)
}
