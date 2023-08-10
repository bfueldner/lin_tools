#include <gtest/gtest.h>

#include <lin/lexical/ldf/signal_encoding_type.hpp>

/* 9.2.6.1 Signal encoding type definition */

TEST(test_lin_lexical_ncf_signal_encoding_type, signal_encoding_type)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf;

    std::string text{
        "LightEncoding {"
        "    logical_value, 0, \"Off\";"
        "    physical_value, 1, 254, 1, 100, \"lux\";"
        "    logical_value, 255, \"error\";"
        "}"
    };
    signal_encoding_type_t signal_encoding_type;

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::signal_encoding_type, x3::ascii::space, signal_encoding_type);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(signal_encoding_type.signal_encoding_type_name.c_str(), "LightEncoding");
    ASSERT_EQ(signal_encoding_type.values.size(), 3);
    // NOLINTBEGIN(readability-container-data-pointer)
    {
        auto *logic =
            std::get_if< signal_encoding_type::logical_value_t >(&signal_encoding_type.values[0]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 0);
        EXPECT_STREQ(logic->text_info.c_str(), "Off");
    }
    {
        auto *physical =
            std::get_if< signal_encoding_type::physical_range_t >(&signal_encoding_type.values[1]);
        ASSERT_NE(physical, nullptr);
        EXPECT_EQ(physical->min_value, 1);
        EXPECT_EQ(physical->max_value, 254);
        EXPECT_EQ(physical->scale, 1.0);
        EXPECT_EQ(physical->offset, 100.0);
        EXPECT_STREQ(physical->text_info.c_str(), "lux");
    }
    {
        auto *logic =
            std::get_if< signal_encoding_type::logical_value_t >(&signal_encoding_type.values[2]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 255);
        EXPECT_STREQ(logic->text_info.c_str(), "error");
    }
    // NOLINTEND(readability-container-data-pointer)
}
