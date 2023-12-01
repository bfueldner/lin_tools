#include <sstream>

#include <gtest/gtest.h>

#include <lin/ldf/generator/signal_group.hpp>
#include <lin/ldf/signal_group.hpp>

/* 9.2.3.3 Signal groups */

TEST(test_lin_ldf_signal_group_generator, signal_group_entry)
{
    using namespace lin::ldf::signal::group;

    signal_t const group_entry{ "CPMReqB4", 32 };

    std::stringstream stream{};
    stream << group_entry;
    EXPECT_EQ(stream.str(), "CPMReqB4, 32;\n");
}

TEST(test_lin_ldf_signal_group_generator, signal_group)
{
    using namespace lin::ldf::signal;

    group_t const signal_group{ "CPMReq",
                                64,
                                { { "CPMReqB0", 0 },
                                  { "CPMReqB1", 8 },
                                  { "CPMReqB2", 16 },
                                  { "CPMReqB3", 24 },
                                  { "CPMReqB4", 32 },
                                  { "CPMReqB5", 40 },
                                  { "CPMReqB6", 48 },
                                  { "CPMReqB7", 56 } } };


    std::stringstream stream{};
    stream << signal_group;
    EXPECT_EQ(
        stream.str(),
        "CPMReq: 64 {\n"
        "    CPMReqB0, 0;\n"
        "    CPMReqB1, 8;\n"
        "    CPMReqB2, 16;\n"
        "    CPMReqB3, 24;\n"
        "    CPMReqB4, 32;\n"
        "    CPMReqB5, 40;\n"
        "    CPMReqB6, 48;\n"
        "    CPMReqB7, 56;\n"
        "}\n");
}

TEST(test_lin_ldf_signal_group_generator, signal_groups)
{
    using namespace lin::ldf::signal;

    groups_t const signal_groups{ { "CPMReq",
                                    64,
                                    { { "CPMReqB0", 0 },
                                      { "CPMReqB1", 8 },
                                      { "CPMReqB2", 16 },
                                      { "CPMReqB3", 24 },
                                      { "CPMReqB4", 32 },
                                      { "CPMReqB5", 40 },
                                      { "CPMReqB6", 48 },
                                      { "CPMReqB7", 56 } } },
                                  { "CPMResp",
                                    64,
                                    { { "CPMRespB0", 0 },
                                      { "CPMRespB1", 8 },
                                      { "CPMRespB2", 16 },
                                      { "CPMRespB3", 24 },
                                      { "CPMRespB4", 32 },
                                      { "CPMRespB5", 40 },
                                      { "CPMRespB6", 48 },
                                      { "CPMRespB7", 56 } } } };

    std::stringstream stream{};
    stream << signal_groups;
    EXPECT_EQ(
        stream.str(),
        "Signal_groups {\n"
        "    CPMReq: 64 {\n"
        "        CPMReqB0, 0;\n"
        "        CPMReqB1, 8;\n"
        "        CPMReqB2, 16;\n"
        "        CPMReqB3, 24;\n"
        "        CPMReqB4, 32;\n"
        "        CPMReqB5, 40;\n"
        "        CPMReqB6, 48;\n"
        "        CPMReqB7, 56;\n"
        "    }\n"
        "    CPMResp: 64 {\n"
        "        CPMRespB0, 0;\n"
        "        CPMRespB1, 8;\n"
        "        CPMRespB2, 16;\n"
        "        CPMRespB3, 24;\n"
        "        CPMRespB4, 32;\n"
        "        CPMRespB5, 40;\n"
        "        CPMRespB6, 48;\n"
        "        CPMRespB7, 56;\n"
        "    }\n"
        "}\n");
}
