#include <sstream>

#include <gtest/gtest.h>

#include <lin/common/bitrate.hpp>
#include <lin/common/generator/bitrate.hpp>

/* 8.2.3 General definition */

TEST(test_lin_common_bitrate_generator, bitrate_kbps)
{
    using namespace lin::common;

    bitrate::kbps_t const bitrate_kbps{ 19.2 };

    std::stringstream stream{};
    stream << bitrate_kbps;
    EXPECT_EQ(stream.str(), "19.2 kbps");
}
