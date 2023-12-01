#include <sstream>

#include <gtest/gtest.h>

#include <lin/ncf/general.hpp>
#include <lin/ncf/generator/general.hpp>

/* 8.2.3 General definition */

TEST(test_lin_ncf_general_generator, bitrate_automatic_default)
{
    using namespace lin::ncf::general;

    bitrate_t const bitrate{ bitrate::automatic_t{} };

    std::stringstream stream{};
    stream << bitrate;
    EXPECT_EQ(stream.str(), "automatic");
}

TEST(test_lin_ncf_general_generator, bitrate_automatic_min)
{
    using namespace lin::ncf::general;

    bitrate_t const bitrate{ bitrate::automatic_t{ bitrate::kbps_t{ 9.6 } } };

    std::stringstream stream{};
    stream << bitrate;
    EXPECT_EQ(stream.str(), "automatic min 9.6 kbps");
}

TEST(test_lin_ncf_general_generator, bitrate_automatic_max)
{
    using namespace lin::ncf::general;

    bitrate_t const bitrate{ bitrate::automatic_t{ {}, bitrate::kbps_t{ 19.2 } } };

    std::stringstream stream{};
    stream << bitrate;
    EXPECT_EQ(stream.str(), "automatic max 19.2 kbps");
}

TEST(test_lin_ncf_general_generator, bitrate_automatic_min_max)
{
    using namespace lin::ncf::general;

    bitrate_t const bitrate{ bitrate::automatic_t{ bitrate::kbps_t{ 9.6 },
                                                   bitrate::kbps_t{ 19.2 } } };

    std::stringstream stream{};
    stream << bitrate;
    EXPECT_EQ(stream.str(), "automatic min 9.6 kbps max 19.2 kbps");
}

TEST(test_lin_ncf_general_generator, bitrate_select_single)
{
    using namespace lin::ncf::general;

    bitrate_t const bitrate{ bitrate::select_t{ bitrate::kbps_t{ 19.2 } } };

    std::stringstream stream{};
    stream << bitrate;
    EXPECT_EQ(stream.str(), "select { 19.2 kbps }");
}

TEST(test_lin_ncf_general_generator, bitrate_select_multiple)
{
    using namespace lin::ncf::general;

    bitrate_t const bitrate{ bitrate::select_t{
        bitrate::kbps_t{ 4.8 }, bitrate::kbps_t{ 9.6 }, bitrate::kbps_t{ 19.2 } } };

    std::stringstream stream{};
    stream << bitrate;
    EXPECT_EQ(stream.str(), "select { 4.8 kbps, 9.6 kbps, 19.2 kbps }");
}

TEST(test_lin_ncf_general_generator, bitrate_fixed)
{
    using namespace lin::ncf::general;

    bitrate_t const bitrate{ bitrate::fixed_t{ 19.2 } };

    std::stringstream stream{};
    stream << bitrate;
    EXPECT_EQ(stream.str(), "19.2 kbps");
}

TEST(test_lin_ncf_general_generator, general)
{
    using namespace lin::ncf;

    general_t const general{ "2.2",
                             5,
                             0x20,
                             1,
                             general::bitrate::automatic_t{ general::bitrate::kbps_t{ 10 },
                                                            general::bitrate::kbps_t{ 20 } },
                             true };

    std::stringstream stream{};
    stream << general;
    EXPECT_EQ(
        stream.str(),
        "general {\n"
        "    LIN_protocol_version = \"2.2\";\n"
        "    supplier = 0x0005;\n"
        "    function = 0x0020;\n"
        "    variant = 1;\n"
        "    bitrate = automatic min 10 kbps max 20 kbps;\n"
        "    sends_wake_up_signal = \"yes\";\n"
        "}\n");
}
