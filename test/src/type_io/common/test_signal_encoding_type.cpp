#include <gtest/gtest.h>

#include <lin/type_io/common/signal_encoding_type.hpp>

TEST(test_lin_type_io_common_signal_encoding_type, logical_value)
{
    using namespace lin::type::common::signal_encoding_type;

    logical_value_t const logical_value{ 0, "off" };

    std::stringstream stream{};
    stream << logical_value;
    EXPECT_EQ(stream.str(), "logical_value, 0, \"off\";\n");
}

TEST(test_lin_type_io_common_signal_encoding_type, physical_value)
{
    using namespace lin::type::common::signal_encoding_type;

    physical_range_t const physical_range{ 1, 254, 1, 100, "lux" };

    std::stringstream stream{};
    stream << physical_range;
    EXPECT_EQ(stream.str(), "physical_value, 1, 254, 1, 100, \"lux\";\n");
}

TEST(test_lin_type_io_common_signal_encoding_type, bcd_value)
{
    using namespace lin::type::common::signal_encoding_type;

    bcd_value_t const bcd_value{};

    std::stringstream stream{};
    stream << bcd_value;
    EXPECT_EQ(stream.str(), "bcd_value;\n");
}

TEST(test_lin_type_io_common_signal_encoding_type, encoding_ascii_value)
{
    using namespace lin::type::common::signal_encoding_type;

    ascii_value_t const ascii_value{};

    std::stringstream stream{};
    stream << ascii_value;
    EXPECT_EQ(stream.str(), "ascii_value;\n");
}

TEST(test_lin_type_io_common_signal_encoding_type, encoding_value)
{
    using namespace lin::type::common::signal_encoding_type;

    //std::string text{ "logical_value, 1, \"on\";" };
    value_t const value{ logical_value_t{ 1, "on" } };

    std::stringstream stream{};
    stream << value;
    EXPECT_EQ(stream.str(), "logical_value, 1, \"on\";\n");
}
