#include <stdexcept>

#include <gtest/gtest.h>

#include <lin/common/validate/version.hpp>

TEST(test_lin_common_version_validate, from_string)
{
    using namespace lin::common::validate;

    version_t const version = version::from_string("2.1");

    EXPECT_EQ(version.high, 2);
    EXPECT_EQ(version.low, 1);
}

TEST(test_lin_common_version_validate, from_string_error)
{
    using namespace lin::common::validate;

    EXPECT_THROW(version::from_string("21"), std::out_of_range);
}
