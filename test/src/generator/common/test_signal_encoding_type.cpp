#include <sstream>

#include <gtest/gtest.h>

#include <lin/common/signal_encoding_type.hpp>

#include <lin/common/generator/signal_encoding_type.hpp>

TEST(test_lin_common_signal_encoding_type_generator, logical_value)
{
    using namespace lin::common::signal_encoding_type;

    logical_value_t const logical_value{ 0, "off" };

    std::stringstream stream{};
    stream << logical_value;
    EXPECT_EQ(stream.str(), "logical_value, 0, \"off\"");
}

TEST(test_lin_common_signal_encoding_type_generator, physical_value)
{
    using namespace lin::common::signal_encoding_type;

    physical_range_t const physical_range{ 1, 254, 1, 100, "lux" };

    std::stringstream stream{};
    stream << physical_range;
    EXPECT_EQ(stream.str(), "physical_value, 1, 254, 1, 100, \"lux\"");
}

TEST(test_lin_common_signal_encoding_type_generator, bcd_value)
{
    using namespace lin::common::signal_encoding_type;

    bcd_value_t const bcd_value{};

    std::stringstream stream{};
    stream << bcd_value;
    EXPECT_EQ(stream.str(), "bcd_value");
}

TEST(test_lin_common_signal_encoding_type_generator, encoding_ascii_value)
{
    using namespace lin::common::signal_encoding_type;

    ascii_value_t const ascii_value{};

    std::stringstream stream{};
    stream << ascii_value;
    EXPECT_EQ(stream.str(), "ascii_value");
}

TEST(test_lin_common_signal_encoding_type_generator, encoding_value)
{
    using namespace lin::common::signal_encoding_type;

    value_t const value{ logical_value_t{ 1, "on" } };

    std::stringstream stream{};
    stream << value;
    EXPECT_EQ(stream.str(), "logical_value, 1, \"on\";\n");
}
