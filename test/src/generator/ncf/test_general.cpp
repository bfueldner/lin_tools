#include <sstream>

#include <gtest/gtest.h>

#include <lin/ncf/general.hpp>

#include <lin/ncf/generator/general.hpp>

TEST(test_lin_ncf_general_generator, bitrate)
{
    using namespace lin::ncf::general;

    bitrate_t const bitrate{ 19.2 };

    std::stringstream stream{};
    stream << bitrate;
    EXPECT_EQ(stream.str(), "19.2 kbps");
}

TEST(test_lin_ncf_general_generator, bitrate_definition_automatic_default)
{
    using namespace lin::ncf::general::bitrate_definition;

    automatic_t const bitrate_definition_automatic{};

    std::stringstream stream{};
    stream << bitrate_definition_automatic;
    EXPECT_EQ(stream.str(), "automatic");
}

TEST(test_lin_ncf_general_generator, bitrate_definition_automatic_min)
{
    using namespace lin::ncf::general::bitrate_definition;

    automatic_t const bitrate_definition_automatic{ lin::ncf::general::bitrate_t{ 9.6 } };

    std::stringstream stream{};
    stream << bitrate_definition_automatic;
    EXPECT_EQ(stream.str(), "automatic min 9.6 kbps");
}

TEST(test_lin_ncf_general_generator, bitrate_definition_automatic_max)
{
    using namespace lin::ncf::general::bitrate_definition;

    automatic_t const bitrate_definition_automatic{ {}, lin::ncf::general::bitrate_t{ 19.2 } };

    std::stringstream stream{};
    stream << bitrate_definition_automatic;
    EXPECT_EQ(stream.str(), "automatic max 19.2 kbps");
}

TEST(test_lin_ncf_general_generator, bitrate_definition_automatic_min_max)
{
    using namespace lin::ncf::general::bitrate_definition;

    automatic_t const bitrate_definition_automatic{ lin::ncf::general::bitrate_t{ 9.6 },
                                                    lin::ncf::general::bitrate_t{ 19.2 } };

    std::stringstream stream{};
    stream << bitrate_definition_automatic;
    EXPECT_EQ(stream.str(), "automatic min 9.6 kbps max 19.2 kbps");
}

TEST(test_lin_ncf_general_generator, bitrate_definition_select_single)
{
    using namespace lin::ncf::general::bitrate_definition;

    select_t const bitrate_definition_select{ lin::ncf::general::bitrate_t{ 19.2 } };

    std::stringstream stream{};
    stream << bitrate_definition_select;
    EXPECT_EQ(stream.str(), "select { 19.2 kbps }");
}

TEST(test_lin_ncf_general_generator, bitrate_definition_select_multiple)
{
    using namespace lin::ncf::general::bitrate_definition;

    select_t const bitrate_definition_select{ lin::ncf::general::bitrate_t{ 4.8 },
                                              lin::ncf::general::bitrate_t{ 9.6 },
                                              lin::ncf::general::bitrate_t{ 19.2 } };

    std::stringstream stream{};
    stream << bitrate_definition_select;
    EXPECT_EQ(stream.str(), "select { 4.8 kbps, 9.6 kbps, 19.2 kbps }");
}

TEST(test_lin_ncf_general_generator, bitrate_definition_fixed)
{
    using namespace lin::ncf::general::bitrate_definition;

    fixed_t const bitrate_definition_fixed{ 19.2 };

    std::stringstream stream{};
    stream << bitrate_definition_fixed;
    EXPECT_EQ(stream.str(), "19.2 kbps");
}

TEST(test_lin_ncf_general_generator, general)
{
    using namespace lin::ncf;

    general_t const general{ "2.2",
                             5,
                             0x20,
                             1,
                             general::bitrate_definition::automatic_t{
                                 lin::ncf::general::bitrate_t{ 10 },
                                 lin::ncf::general::bitrate_t{ 20 } },
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
