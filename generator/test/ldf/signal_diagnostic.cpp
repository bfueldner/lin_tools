#include <sstream>

#include <gtest/gtest.h>

#include <lin/ldf/generator/signal_diagnostic.hpp>
#include <lin/ldf/signal_diagnostic.hpp>

/* 9.2.3.2 Diagnostic signals */

TEST(test_lin_ldf_signal_diagnostic_generator, diagnostic_signal)
{
    using namespace lin::ldf::signal;

    diagnostic_t const diagnostic_signal{ "MasterReqB0", 8, 0 };

    std::stringstream stream{};
    stream << diagnostic_signal;
    EXPECT_EQ(stream.str(), "MasterReqB0: 8, 0;\n");
}

TEST(test_lin_ldf_signal_diagnostic_generator, diagnostic_signals)
{
    using namespace lin::ldf::signal;

    diagnostics_t const diagnostic_signals{
        { "MasterReqB0", 8, 0 }, { "MasterReqB1", 8, 0 }, { "MasterReqB2", 8, 0 },
        { "MasterReqB3", 8, 0 }, { "MasterReqB4", 8, 0 }, { "MasterReqB5", 8, 0 },
        { "MasterReqB6", 8, 0 }, { "MasterReqB7", 8, 0 }, { "SlaveRespB0", 8, 0 },
        { "SlaveRespB1", 8, 0 }, { "SlaveRespB2", 8, 0 }, { "SlaveRespB3", 8, 0 },
        { "SlaveRespB4", 8, 0 }, { "SlaveRespB5", 8, 0 }, { "SlaveRespB6", 8, 0 },
        { "SlaveRespB7", 8, 0 },
    };

    std::stringstream stream{};
    stream << diagnostic_signals;
    EXPECT_EQ(
        stream.str(),
        "Diagnostic_signals {\n"
        "    MasterReqB0: 8, 0;\n"
        "    MasterReqB1: 8, 0;\n"
        "    MasterReqB2: 8, 0;\n"
        "    MasterReqB3: 8, 0;\n"
        "    MasterReqB4: 8, 0;\n"
        "    MasterReqB5: 8, 0;\n"
        "    MasterReqB6: 8, 0;\n"
        "    MasterReqB7: 8, 0;\n"
        "    SlaveRespB0: 8, 0;\n"
        "    SlaveRespB1: 8, 0;\n"
        "    SlaveRespB2: 8, 0;\n"
        "    SlaveRespB3: 8, 0;\n"
        "    SlaveRespB4: 8, 0;\n"
        "    SlaveRespB5: 8, 0;\n"
        "    SlaveRespB6: 8, 0;\n"
        "    SlaveRespB7: 8, 0;\n"
        "}\n");
}
