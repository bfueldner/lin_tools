#include <sstream>

#include <gtest/gtest.h>

#include <lin/ldf/signal.hpp>

#include <lin/ldf/generator/signal.hpp>

/* 9.2.3.1 Standard signals */

TEST(test_lin_ldf_signal_generator, standard_signal_init_value_scalar)
{
    using namespace lin::ldf::signal::standard_signal;

    init_value_t const init_value{ 100 };

    std::stringstream stream{};
    stream << init_value;
    EXPECT_EQ(stream.str(), "100");
}

TEST(test_lin_ldf_signal_generator, standard_signal_init_value_array)
{
    using namespace lin::ldf::signal::standard_signal;

    init_value_t const init_value{ init_value_array_t{ 0xA0, 0xB0 } };

    std::stringstream stream{};
    stream << init_value;
    EXPECT_EQ(stream.str(), "{ 0xa0, 0xb0 }");
}

TEST(test_lin_ldf_signal_generator, standard_signal)
{
    using namespace lin::ldf::signal;

    standard_signal_t const standard_signal{
        "InternalLightsRequest", 2, 0, "CEM", { "LSM", "RSM" }
    };

    std::stringstream stream{};
    stream << standard_signal;
    EXPECT_EQ(stream.str(), "InternalLightsRequest: 2, 0, CEM, LSM, RSM;\n");
}

TEST(test_lin_ldf_signal_generator, standard_signals)
{
    using namespace lin::ldf::signal;

    standard_signals_t const standard_signals{ { "LSMerror", 1, 0, "LSM" },
                                               { "RSMerror", 1, 1, "RSM", { "CEM" } } };

    std::stringstream stream{};
    stream << standard_signals;
    EXPECT_EQ(
        stream.str(),
        "Signals {\n"
        "    LSMerror: 1, 0, LSM;\n"
        "    RSMerror: 1, 1, RSM, CEM;\n"
        "}\n");
}

/* 9.2.3.2 Diagnostic signals */

TEST(test_lin_ldf_signal_generator, diagnostic_signal)
{
    using namespace lin::ldf::signal;

    diagnostic_signal_t const diagnostic_signal{ "MasterReqB0", 8, 0 };

    std::stringstream stream{};
    stream << diagnostic_signal;
    EXPECT_EQ(stream.str(), "MasterReqB0: 8, 0;\n");
}

TEST(test_lin_ldf_signal_generator, diagnostic_signals)
{
    using namespace lin::ldf::signal;

    diagnostic_signals_t const diagnostic_signals{
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

/* 9.2.3.3 Signal groups */

TEST(test_lin_ldf_signal_generator, signal_group_group_entry)
{
    using namespace lin::ldf::signal::signal_group;

    group_entry_t const group_entry{ "CPMReqB4", 32 };

    std::stringstream stream{};
    stream << group_entry;
    EXPECT_EQ(stream.str(), "CPMReqB4, 32;\n");
}

TEST(test_lin_ldf_signal_generator, signal_group)
{
    using namespace lin::ldf::signal;

    signal_group_t const signal_group{ "CPMReq",
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

TEST(test_lin_ldf_signal_generator, signal_groups)
{
    using namespace lin::ldf::signal;

    signal_groups_t const signal_groups{ { "CPMReq",
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

/* 9.2.6.1 Signal encoding type definition */

TEST(test_lin_ldf_signal_generator, signal_encoding_type)
{
    using namespace lin::ldf::signal;

    signal_encoding_type_t const signal_encoding_type{
        "LightEncoding",
        { signal_encoding_type::logical_value_t{ 0, "Off" },
          signal_encoding_type::physical_range_t{ 1, 254, 1.0, 100.0, "lux" },
          signal_encoding_type::logical_value_t{ 255, "error" } }
    };

    std::stringstream stream{};
    stream << signal_encoding_type;
    EXPECT_EQ(
        stream.str(),
        "LightEncoding {\n"
        "    logical_value, 0, \"Off\";\n"
        "    physical_value, 1, 254, 1, 100, \"lux\";\n"
        "    logical_value, 255, \"error\";\n"
        "}\n");
}

TEST(test_lin_ldf_signal_generator, signal_encoding_types)
{
    using namespace lin::ldf::signal;

    signal_encoding_types_t const signal_encoding_types{
        { "Dig2Bit",
          { signal_encoding_type::logical_value_t{ 0, "off" },
            signal_encoding_type::logical_value_t{ 1, "on" },
            signal_encoding_type::logical_value_t{ 2, "error" },
            signal_encoding_type::logical_value_t{ 3, "void" } } },
        { "LightEncoding",
          { signal_encoding_type::logical_value_t{ 0, "Off" },
            signal_encoding_type::physical_range_t{ 1, 254, 1.0, 100.0, "lux" },
            signal_encoding_type::logical_value_t{ 255, "error" } } }
    };

    std::stringstream stream{};
    stream << signal_encoding_types;
    EXPECT_EQ(
        stream.str(),
        "Signal_encoding_types {\n"
        "    Dig2Bit {\n"
        "        logical_value, 0, \"off\";\n"
        "        logical_value, 1, \"on\";\n"
        "        logical_value, 2, \"error\";\n"
        "        logical_value, 3, \"void\";\n"
        "    }\n"
        "    LightEncoding {\n"
        "        logical_value, 0, \"Off\";\n"
        "        physical_value, 1, 254, 1, 100, \"lux\";\n"
        "        logical_value, 255, \"error\";\n"
        "    }\n"
        "}\n");
}

/* 9.2.6.2 Signal representation definition */

TEST(test_lin_ldf_signal_generator, signal_representation)
{
    using namespace lin::ldf::signal;

    signal_representation_t const signal_representation{
        "LightEncoding", { "RightIntLightsSwitch", "LefttIntLightsSwitch" }
    };

    std::stringstream stream{};
    stream << signal_representation;
    EXPECT_EQ(stream.str(), "LightEncoding: RightIntLightsSwitch, LefttIntLightsSwitch;\n");
}

TEST(test_lin_ldf_signal_generator, signal_representations)
{
    using namespace lin::ldf::signal;

    signal_representations_t const signal_representations{
        { "Dig2Bit", { "InternalLightsRequest" } },
        { "ErrorEncoding", { "RSMerror", "LSMerror" } },
        { "FaultStateEncoding", { "IntError" } },
        { "LightEncoding", { "RightIntLightsSwitch", "LefttIntLightsSwitch" } }
    };

    std::stringstream stream{};
    stream << signal_representations;
    EXPECT_EQ(
        stream.str(),
        "Signal_representation {\n"
        "    Dig2Bit: InternalLightsRequest;\n"
        "    ErrorEncoding: RSMerror, LSMerror;\n"
        "    FaultStateEncoding: IntError;\n"
        "    LightEncoding: RightIntLightsSwitch, LefttIntLightsSwitch;\n"
        "}\n");
}
