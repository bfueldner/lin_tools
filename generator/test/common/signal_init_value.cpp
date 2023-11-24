#include <sstream>

#include <gtest/gtest.h>

#include <lin/common/generator/signal_init_value.hpp>
#include <lin/common/signal_init_value.hpp>

/* Common signal init value definition */

TEST(test_lin_common_signal_init_value_generator, init_value_scalar)
{
    using namespace lin::common::signal;

    init_value_t const init_value{ 100 };

    std::stringstream stream{};
    stream << init_value;
    EXPECT_EQ(stream.str(), "100");
}

TEST(test_lin_common_signal_init_value_generator, init_value_array)
{
    using namespace lin::common::signal;

    init_value_t const init_value{ init_value::array_t{ 0xA0, 0xB0 } };

    std::stringstream stream{};
    stream << init_value;
    EXPECT_EQ(stream.str(), "{ 0xa0, 0xb0 }");
}
