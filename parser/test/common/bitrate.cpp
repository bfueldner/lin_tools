#include <string>

#include <gtest/gtest.h>

#include <lin/common/bitrate.hpp>
#include <lin/common/parser/bitrate.hpp>

TEST(test_lin_common_bitrate_parser, kbps)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::common;

    std::string const text{ "19.2 kbps" };
    bitrate::kbps_t bitrate_kbps{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::bitrate_kbps, x3::ascii::space, bitrate_kbps);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_EQ(bitrate_kbps, 19.2);
}
