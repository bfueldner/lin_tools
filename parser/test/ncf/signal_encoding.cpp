#include <string>
#include <variant>

#include <gtest/gtest.h>

#include <lin/ncf/parser/signal_encoding.hpp>
#include <lin/ncf/signal_encoding.hpp>

/* 8.2.5.3 Signal encoding type definition */

TEST(test_lin_ncf_signal_encoding_parser, signal_encoding)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string text{ " position {physical_value, 0, 199, 1.8, 0, \"deg\";}" };
    signal::encoding_t encoding{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::signal_encoding, x3::ascii::space, encoding);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(encoding.name.c_str(), "position");
    EXPECT_EQ(encoding.values.size(), 1);
    {
        auto *physical = std::get_if< signal::encoding::physical_range_t >(encoding.values.data());
        ASSERT_NE(physical, nullptr);
        EXPECT_EQ(physical->min, 0);
        EXPECT_EQ(physical->max, 199);
        EXPECT_EQ(physical->scale, 1.8);
        EXPECT_EQ(physical->offset, 0.0);
        EXPECT_STREQ(physical->text_info.c_str(), "deg");
    }
}

TEST(test_lin_ncf_signal_encoding_parser, encodings)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string const text{
        "encoding { "
        "    position {physical_value, 0, 199, 1.8, 0, \"deg\";}"
        "    fault_enc {logical_value, 0, \"no result\";"
        "               logical_value, 1, \"failed\";"
        "               logical_value, 2, \"passed\";}"
        "}"
    };
    signal::encodings_t encodings{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::signal_encodings, x3::ascii::space, encodings);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(encodings.size(), 2);
    EXPECT_STREQ(encodings[0].name.c_str(), "position");
    ASSERT_EQ(encodings[0].values.size(), 1);
    {
        auto *physical =
            std::get_if< signal::encoding::physical_range_t >(encodings[0].values.data());
        ASSERT_NE(physical, nullptr);
        EXPECT_EQ(physical->min, 0);
        EXPECT_EQ(physical->max, 199);
        EXPECT_EQ(physical->scale, 1.8);
        EXPECT_EQ(physical->offset, 0.0);
        EXPECT_STREQ(physical->text_info.c_str(), "deg");
    }
    EXPECT_STREQ(encodings[1].name.c_str(), "fault_enc");
    ASSERT_EQ(encodings[1].values.size(), 3);
    // NOLINTBEGIN(readability-container-data-pointer)
    {
        auto *logic = std::get_if< signal::encoding::logical_value_t >(&encodings[1].values[0]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->value, 0);
        EXPECT_STREQ(logic->text_info.c_str(), "no result");
    }
    {
        auto *logic = std::get_if< signal::encoding::logical_value_t >(&encodings[1].values[1]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->value, 1);
        EXPECT_STREQ(logic->text_info.c_str(), "failed");
    }
    {
        auto *logic = std::get_if< signal::encoding::logical_value_t >(&encodings[1].values[2]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->value, 2);
        EXPECT_STREQ(logic->text_info.c_str(), "passed");
    }
    // NOLINTEND(readability-container-data-pointer)
}
