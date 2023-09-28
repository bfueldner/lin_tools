#include <string>
#include <variant>

#include <gtest/gtest.h>

#include <lin/ncf/signal.hpp>

#include <lin/ncf/parser/signal.hpp>

/* 8.2.5.2 Signal definition */

TEST(test_lin_ncf_signal_parser, init_value_scalar)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf::signal;

    std::string text{ "init_value = 1" };
    init_value_t init_value;

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::init_value, x3::ascii::space, init_value);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *scalar = std::get_if< init_value_scalar_t >(&init_value);
    ASSERT_NE(scalar, nullptr);
    EXPECT_EQ(*scalar, 1);
}

TEST(test_lin_ncf_signal_parser, init_value_array)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf::signal;

    std::string text{ "init_value = {0x22, 0x11}" };
    init_value_t init_value;

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::init_value, x3::ascii::space, init_value);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *array = std::get_if< init_value_array_t >(&init_value);
    ASSERT_NE(array, nullptr);
    EXPECT_EQ(*array, (init_value_array_t{ 0x22, 0x11 }));
}

TEST(test_lin_ncf_signal_parser, signal_properties)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf::signal;

    std::string text{ "size = 2; init_value = 0; offset = 9; fault_enc;" };
    signal_properties_t signal_properties;

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::signal_properties, x3::ascii::space, signal_properties);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *scalar = std::get_if< init_value_scalar_t >(&signal_properties.init_value);
    ASSERT_NE(scalar, nullptr);
    EXPECT_EQ(*scalar, 0);
    EXPECT_EQ(signal_properties.size, 2);
    EXPECT_EQ(signal_properties.offset, 9);
    EXPECT_STREQ(signal_properties.encoding_name.c_str(), "fault_enc");
}

TEST(test_lin_ncf_signal_parser, signal_definition)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf;

    std::string text{
        "signals {"
        "  state       {size = 8; init_value = 0; offset = 0;}"
        "  fault_state {size = 2; init_value = 0; offset = 9; fault_enc;}"
        "  error_bit   {size = 1; init_value = 0; offset = 8;}"
        "  angle       {size = 16; init_value = {0x22, 0x11}; offset = 16;}"
        "}"
    };
    signals_t signals;

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::signal_definition, x3::ascii::space, signals);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(signals.size(), 4);
    // NOLINTBEGIN(readability-container-data-pointer)
    {
        auto signal = signals[0];
        EXPECT_STREQ(signal.signal_name.c_str(), "state");
        auto *scalar =
            std::get_if< signal::init_value_scalar_t >(&signal.signal_properties.init_value);
        ASSERT_NE(scalar, nullptr);
        EXPECT_EQ(*scalar, 0);
        EXPECT_EQ(signal.signal_properties.size, 8);
        EXPECT_EQ(signal.signal_properties.offset, 0);
        EXPECT_STREQ(signal.signal_properties.encoding_name.c_str(), "");
    }
    {
        auto signal = signals[1];
        EXPECT_STREQ(signal.signal_name.c_str(), "fault_state");
        auto *scalar =
            std::get_if< signal::init_value_scalar_t >(&signal.signal_properties.init_value);
        ASSERT_NE(scalar, nullptr);
        EXPECT_EQ(*scalar, 0);
        EXPECT_EQ(signal.signal_properties.size, 2);
        EXPECT_EQ(signal.signal_properties.offset, 9);
        EXPECT_STREQ(signal.signal_properties.encoding_name.c_str(), "fault_enc");
    }
    {
        auto signal = signals[2];
        EXPECT_STREQ(signal.signal_name.c_str(), "error_bit");
        auto *scalar =
            std::get_if< signal::init_value_scalar_t >(&signal.signal_properties.init_value);
        ASSERT_NE(scalar, nullptr);
        EXPECT_EQ(*scalar, 0);
        EXPECT_EQ(signal.signal_properties.size, 1);
        EXPECT_EQ(signal.signal_properties.offset, 8);
        EXPECT_STREQ(signal.signal_properties.encoding_name.c_str(), "");
    }
    {
        auto signal = signals[3];
        EXPECT_STREQ(signal.signal_name.c_str(), "angle");
        auto *scalar =
            std::get_if< signal::init_value_array_t >(&signal.signal_properties.init_value);
        ASSERT_NE(scalar, nullptr);
        EXPECT_EQ(*scalar, (signal::init_value_array_t{ 0x22, 0x11 }));
        EXPECT_EQ(signal.signal_properties.size, 16);
        EXPECT_EQ(signal.signal_properties.offset, 16);
        EXPECT_STREQ(signal.signal_properties.encoding_name.c_str(), "");
    }
    // NOLINTEND(readability-container-data-pointer)
}

/* 8.2.5.3 Signal encoding type definition */

TEST(test_lin_ncf_signal_encoding_type_parser, encoding)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf::signal_encoding_type;

    std::string text{ " position {physical_value, 0, 199, 1.8, 0, \"deg\";}" };
    encoding_t encoding;

    auto position = text.begin();
    auto result = phrase_parse(position, text.end(), parser::encoding, x3::ascii::space, encoding);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(encoding.encoding_name.c_str(), "position");
    EXPECT_EQ(encoding.value.size(), 1);
    {
        auto *physical = std::get_if< physical_range_t >(encoding.value.data());
        ASSERT_NE(physical, nullptr);
        EXPECT_EQ(physical->min_value, 0);
        EXPECT_EQ(physical->max_value, 199);
        EXPECT_EQ(physical->scale, 1.8);
        EXPECT_EQ(physical->offset, 0.0);
        EXPECT_STREQ(physical->text_info.c_str(), "deg");
    }
}

TEST(test_lin_ncf_signal_encoding_type_parser, encoding_definition)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::ncf::signal_encoding_type;

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
        auto *physical = std::get_if< physical_range_t >(encodings[0].value.data());
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
        auto *logic = std::get_if< logical_value_t >(&encodings[1].value[0]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 0);
        EXPECT_STREQ(logic->text_info.c_str(), "no result");
    }
    {
        auto *logic = std::get_if< logical_value_t >(&encodings[1].value[1]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 1);
        EXPECT_STREQ(logic->text_info.c_str(), "failed");
    }
    {
        auto *logic = std::get_if< logical_value_t >(&encodings[1].value[2]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 2);
        EXPECT_STREQ(logic->text_info.c_str(), "passed");
    }
    // NOLINTEND(readability-container-data-pointer)
}
