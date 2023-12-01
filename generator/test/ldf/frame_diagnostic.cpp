#include <sstream>

#include <gtest/gtest.h>

#include <lin/ldf/frame_diagnostic.hpp>
#include <lin/ldf/generator/frame_diagnostic.hpp>

/* 9.2.4.4 Diagnostic frames */

TEST(test_lin_ldf_frame_generator, diagnostic_frame)
{
    using namespace lin::ldf::frame;

    diagnostic_t const diagnostic_frame{ "MasterReq",
                                         60,
                                         { { "MasterReqB0", 0 },
                                           { "MasterReqB1", 8 },
                                           { "MasterReqB2", 16 },
                                           { "MasterReqB3", 24 },
                                           { "MasterReqB4", 32 },
                                           { "MasterReqB5", 40 },
                                           { "MasterReqB6", 48 },
                                           { "MasterReqB7", 56 } } };

    std::stringstream stream{};
    stream << diagnostic_frame;
    EXPECT_EQ(
        stream.str(),
        "MasterReq: 0x3c {\n"
        "    MasterReqB0, 0;\n"
        "    MasterReqB1, 8;\n"
        "    MasterReqB2, 16;\n"
        "    MasterReqB3, 24;\n"
        "    MasterReqB4, 32;\n"
        "    MasterReqB5, 40;\n"
        "    MasterReqB6, 48;\n"
        "    MasterReqB7, 56;\n"
        "}\n");
}

TEST(test_lin_ldf_frame_generator, diagnostic_frames)
{
    using namespace lin::ldf::frame;

    diagnostics_t const diagnostic_frames{ { "MasterReq",
                                             60,
                                             { { "MasterReqB0", 0 },
                                               { "MasterReqB1", 8 },
                                               { "MasterReqB2", 16 },
                                               { "MasterReqB3", 24 },
                                               { "MasterReqB4", 32 },
                                               { "MasterReqB5", 40 },
                                               { "MasterReqB6", 48 },
                                               { "MasterReqB7", 56 } } },
                                           { "SlaveResp",
                                             61,
                                             { { "SlaveRespB0", 0 },
                                               { "SlaveRespB1", 8 },
                                               { "SlaveRespB2", 16 },
                                               { "SlaveRespB3", 24 },
                                               { "SlaveRespB4", 32 },
                                               { "SlaveRespB5", 40 },
                                               { "SlaveRespB6", 48 },
                                               { "SlaveRespB7", 56 } } } };

    std::stringstream stream{};
    stream << diagnostic_frames;
    EXPECT_EQ(
        stream.str(),
        "Diagnostic_frames {\n"
        "    MasterReq: 0x3c {\n"
        "        MasterReqB0, 0;\n"
        "        MasterReqB1, 8;\n"
        "        MasterReqB2, 16;\n"
        "        MasterReqB3, 24;\n"
        "        MasterReqB4, 32;\n"
        "        MasterReqB5, 40;\n"
        "        MasterReqB6, 48;\n"
        "        MasterReqB7, 56;\n"
        "    }\n"
        "    SlaveResp: 0x3d {\n"
        "        SlaveRespB0, 0;\n"
        "        SlaveRespB1, 8;\n"
        "        SlaveRespB2, 16;\n"
        "        SlaveRespB3, 24;\n"
        "        SlaveRespB4, 32;\n"
        "        SlaveRespB5, 40;\n"
        "        SlaveRespB6, 48;\n"
        "        SlaveRespB7, 56;\n"
        "    }\n"
        "}\n");
}
