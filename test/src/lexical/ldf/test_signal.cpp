#include <gtest/gtest.h>

#include <lin/lexical/ldf/signal.hpp>

/* 9.2.3.1 Standard signals */

TEST(test_lin_lexical_ldf_signal, standard_signal_init_value_scalar)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::signal::standard_signal;

    std::string text{ "100" };
    init_value_t init_value{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::init_value, x3::ascii::space, init_value);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *scalar = std::get_if< init_value_scalar_t >(&init_value);
    ASSERT_NE(scalar, nullptr);
    EXPECT_EQ(*scalar, 100);
}

TEST(test_lin_lexical_ldf_signal, standard_signal_init_value_array)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::signal::standard_signal;

    std::string text{ "{ 0xA0, 0xB0 }" };
    init_value_t init_value{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::init_value, x3::ascii::space, init_value);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    auto *array = std::get_if< init_value_array_t >(&init_value);
    ASSERT_NE(array, nullptr);
    EXPECT_EQ(*array, (init_value_array_t{ 0xA0, 0xB0 }));
}

TEST(test_lin_lexical_ldf_signal, standard_signal)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::signal;

    std::string text{ "InternalLightsRequest: 2, 0, CEM, LSM, RSM;" };
    standard_signal_t standard_signal{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::standard_signal, x3::ascii::space, standard_signal);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(standard_signal.signal_name.c_str(), "InternalLightsRequest");
    EXPECT_EQ(standard_signal.signal_size, 2);
    auto *init_value =
        std::get_if< standard_signal::init_value_scalar_t >(&standard_signal.init_value);
    ASSERT_NE(init_value, nullptr);
    EXPECT_EQ(*init_value, 0);
    EXPECT_STREQ(standard_signal.published_by.c_str(), "CEM");
    EXPECT_EQ(standard_signal.subscribed_by, (std::vector< std::string >{ "LSM", "RSM" }));
}

TEST(test_lin_lexical_ldf_signal, standard_signals)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::signal;

    std::string text{
        "Signals {"
        "   LSMerror: 1, 0, LSM;"
        "   RSMerror: 1, 1, RSM, CEM;"
        "}"
    };
    standard_signals_t standard_signals;

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::standard_signals, x3::ascii::space, standard_signals);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(standard_signals.size(), 2);

    EXPECT_STREQ(standard_signals[0].signal_name.c_str(), "LSMerror");
    EXPECT_EQ(standard_signals[0].signal_size, 1);
    {
        auto *init_value =
            std::get_if< standard_signal::init_value_scalar_t >(&standard_signals[0].init_value);
        ASSERT_NE(init_value, nullptr);
        EXPECT_EQ(*init_value, 0);
    }
    EXPECT_STREQ(standard_signals[0].published_by.c_str(), "LSM");
    EXPECT_EQ(standard_signals[0].subscribed_by, (std::vector< std::string >{}));

    EXPECT_STREQ(standard_signals[1].signal_name.c_str(), "RSMerror");
    EXPECT_EQ(standard_signals[1].signal_size, 1);
    {
        auto *init_value =
            std::get_if< standard_signal::init_value_scalar_t >(&standard_signals[1].init_value);
        ASSERT_NE(init_value, nullptr);
        EXPECT_EQ(*init_value, 1);
    }
    EXPECT_STREQ(standard_signals[1].published_by.c_str(), "RSM");
    EXPECT_EQ(standard_signals[1].subscribed_by, (std::vector< std::string >{ "CEM" }));
}

/* 9.2.3.2 Diagnostic signals */

TEST(test_lin_lexical_ldf_signal, diagnostic_signal)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::signal;

    std::string text{ "MasterReqB0: 8, 0 ;" };
    diagnostic_signal_t diagnostic_signal{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::diagnostic_signal, x3::ascii::space, diagnostic_signal);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(diagnostic_signal.signal_name.c_str(), "MasterReqB0");
    EXPECT_EQ(diagnostic_signal.signal_size, 8);
    auto *init_value =
        std::get_if< diagnostic_signal::init_value_scalar_t >(&diagnostic_signal.init_value);
    ASSERT_NE(init_value, nullptr);
    EXPECT_EQ(*init_value, 0);
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_lexical_ldf_signal, diagnostic_signals)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::signal;

    std::string text{
        "Diagnostic_signals {"
        "    MasterReqB0: 8, 0 ;"
        "    MasterReqB1: 8, 0 ;"
        "    MasterReqB2: 8, 0 ;"
        "    MasterReqB3: 8, 0 ;"
        "    MasterReqB4: 8, 0 ;"
        "    MasterReqB5: 8, 0 ;"
        "    MasterReqB6: 8, 0 ;"
        "    MasterReqB7: 8, 0 ;"
        "    SlaveRespB0: 8, 0 ;"
        "    SlaveRespB1: 8, 0 ;"
        "    SlaveRespB2: 8, 0 ;"
        "    SlaveRespB3: 8, 0 ;"
        "    SlaveRespB4: 8, 0 ;"
        "    SlaveRespB5: 8, 0 ;"
        "    SlaveRespB6: 8, 0 ;"
        "    SlaveRespB7: 8, 0 ;"
        "}"
    };
    diagnostic_signals_t diagnostic_signals{};

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::diagnostic_signals, x3::ascii::space, diagnostic_signals);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    for (int index = 0; index < 8; index++)
    {
        std::string const name = "MasterReqB" + std::to_string(index);

        EXPECT_STREQ(diagnostic_signals[index].signal_name.c_str(), name.c_str());
        EXPECT_EQ(diagnostic_signals[index].signal_size, 8);
        auto *init_value = std::get_if< diagnostic_signal::init_value_scalar_t >(
            &diagnostic_signals[index].init_value);
        ASSERT_NE(init_value, nullptr);
        EXPECT_EQ(*init_value, 0);
    }

    for (int index = 0; index < 8; index++)
    {
        std::string const name = "SlaveRespB" + std::to_string(index);

        EXPECT_STREQ(diagnostic_signals[index + 8].signal_name.c_str(), name.c_str());
        EXPECT_EQ(diagnostic_signals[index + 8].signal_size, 8);
        auto *init_value = std::get_if< diagnostic_signal::init_value_scalar_t >(
            &diagnostic_signals[index + 8].init_value);
        ASSERT_NE(init_value, nullptr);
        EXPECT_EQ(*init_value, 0);
    }
}
// NOLINTEND(readability-function-cognitive-complexity)

/* 9.2.3.3 Signal groups */

TEST(test_lin_lexical_ldf_signal, signal_group_group_entry)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::signal::signal_group;

    std::string text{ "CPMReqB4,32;" };
    group_entry_t group_entry{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::group_entry, x3::ascii::space, group_entry);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(group_entry.signal_name.c_str(), "CPMReqB4");
    EXPECT_EQ(group_entry.group_offset, 32);
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_lexical_ldf_signal, signal_group)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::signal;

    std::string text{
        "CPMReq:64 {"
        "    CPMReqB0,0;"
        "    CPMReqB1,8;"
        "    CPMReqB2,16;"
        "    CPMReqB3,24;"
        "    CPMReqB4,32;"
        "    CPMReqB5,40;"
        "    CPMReqB6,48;"
        "    CPMReqB7,56;"
        "}"
    };
    signal_group_t signal_group{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::signal_group, x3::ascii::space, signal_group);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(signal_group.signal_group_name.c_str(), "CPMReq");
    EXPECT_EQ(signal_group.group_size, 64);

    int index = 0;
    for (auto const &group_entry : signal_group.group_entries)
    {
        std::string const name = "CPMReqB" + std::to_string(index);

        EXPECT_STREQ(group_entry.signal_name.c_str(), name.c_str());
        EXPECT_EQ(group_entry.group_offset, index * 8);
        index++;
    }
}
// NOLINTEND(readability-function-cognitive-complexity)

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST(test_lin_lexical_ldf_signal, signal_groups)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::signal;

    std::string text{
        "Signal_groups {"
        "    CPMReq:64 {"
        "        CPMReqB0,0;"
        "        CPMReqB1,8;"
        "        CPMReqB2,16;"
        "        CPMReqB3,24;"
        "        CPMReqB4,32;"
        "        CPMReqB5,40;"
        "        CPMReqB6,48;"
        "        CPMReqB7,56;"
        "    }"
        "    CPMResp:64 {"
        "        CPMRespB0,0;"
        "        CPMRespB1,8;"
        "        CPMRespB2,16;"
        "        CPMRespB3,24;"
        "        CPMRespB4,32;"
        "        CPMRespB5,40;"
        "        CPMRespB6,48;"
        "        CPMRespB7,56;"
        "    }"
        "}"
    };
    signal_groups_t signal_groups{};

    auto position = text.begin();
    auto result =
        phrase_parse(position, text.end(), parser::signal_groups, x3::ascii::space, signal_groups);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(signal_groups.size(), 2);

    EXPECT_STREQ(signal_groups[0].signal_group_name.c_str(), "CPMReq");
    EXPECT_EQ(signal_groups[0].group_size, 64);

    int index = 0;
    for (auto const &group_entry : signal_groups[0].group_entries)
    {
        std::string const name = "CPMReqB" + std::to_string(index);

        EXPECT_STREQ(group_entry.signal_name.c_str(), name.c_str());
        EXPECT_EQ(group_entry.group_offset, index * 8);
        index++;
    }

    index = 0;
    for (auto const &group_entry : signal_groups[1].group_entries)
    {
        std::string const name = "CPMRespB" + std::to_string(index);

        EXPECT_STREQ(group_entry.signal_name.c_str(), name.c_str());
        EXPECT_EQ(group_entry.group_offset, index * 8);
        index++;
    }
}
// NOLINTEND(readability-function-cognitive-complexity)

/* 9.2.6.1 Signal encoding type definition */

TEST(test_lin_lexical_ldf_signal, signal_encoding_type)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::signal;

    std::string text{
        "LightEncoding {"
        "    logical_value, 0, \"Off\";"
        "    physical_value, 1, 254, 1, 100, \"lux\";"
        "    logical_value, 255, \"error\";"
        "}"
    };
    signal_encoding_type_t signal_encoding_type;

    auto position = text.begin();
    auto result   = phrase_parse(
        position, text.end(), parser::signal_encoding_type, x3::ascii::space, signal_encoding_type);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(signal_encoding_type.signal_encoding_type_name.c_str(), "LightEncoding");
    ASSERT_EQ(signal_encoding_type.values.size(), 3);
    // NOLINTBEGIN(readability-container-data-pointer)
    {
        auto *logic =
            std::get_if< signal_encoding_type::logical_value_t >(&signal_encoding_type.values[0]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 0);
        EXPECT_STREQ(logic->text_info.c_str(), "Off");
    }
    {
        auto *physical =
            std::get_if< signal_encoding_type::physical_range_t >(&signal_encoding_type.values[1]);
        ASSERT_NE(physical, nullptr);
        EXPECT_EQ(physical->min_value, 1);
        EXPECT_EQ(physical->max_value, 254);
        EXPECT_EQ(physical->scale, 1.0);
        EXPECT_EQ(physical->offset, 100.0);
        EXPECT_STREQ(physical->text_info.c_str(), "lux");
    }
    {
        auto *logic =
            std::get_if< signal_encoding_type::logical_value_t >(&signal_encoding_type.values[2]);
        ASSERT_NE(logic, nullptr);
        EXPECT_EQ(logic->signal_value, 255);
        EXPECT_STREQ(logic->text_info.c_str(), "error");
    }
    // NOLINTEND(readability-container-data-pointer)
}

/* 9.2.6.2 Signal representation definition */

TEST(test_lin_lexical_ldf_signal, signal_representation)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::signal;

    std::string text{ "LightEncoding: RightIntLightsSwitch, LefttIntLightsSwitch;" };
    signal_representation_t signal_representation;

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::signal_representation,
        x3::ascii::space,
        signal_representation);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    EXPECT_STREQ(signal_representation.signal_encoding_type_name.c_str(), "LightEncoding");
    ASSERT_EQ(signal_representation.signal_names.size(), 2);
    EXPECT_STREQ(signal_representation.signal_names[0].c_str(), "RightIntLightsSwitch");
    EXPECT_STREQ(signal_representation.signal_names[1].c_str(), "LefttIntLightsSwitch");
}

TEST(test_lin_lexical_ldf_signal, signal_representations)
{
    namespace x3 = boost::spirit::x3;

    using namespace lin::lexical::ldf::signal;

    std::string text{
        "Signal_representation {"
        "    Dig2Bit: InternalLightsRequest;"
        "    ErrorEncoding: RSMerror, LSMerror;"
        "    FaultStateEncoding: IntError;"
        "    LightEncoding: RightIntLightsSwitch, LefttIntLightsSwitch;"
        "}"
    };
    signal_representations_t signal_representations;

    auto position = text.begin();
    auto result   = phrase_parse(
        position,
        text.end(),
        parser::signal_representations,
        x3::ascii::space,
        signal_representations);
    ASSERT_TRUE(result);
    ASSERT_EQ(position, text.end());

    ASSERT_EQ(signal_representations.size(), 4);
    EXPECT_STREQ(signal_representations[0].signal_encoding_type_name.c_str(), "Dig2Bit");
    ASSERT_EQ(signal_representations[0].signal_names.size(), 1);
    EXPECT_STREQ(signal_representations[0].signal_names[0].c_str(), "InternalLightsRequest");
    EXPECT_STREQ(signal_representations[1].signal_encoding_type_name.c_str(), "ErrorEncoding");
    ASSERT_EQ(signal_representations[1].signal_names.size(), 2);
    EXPECT_STREQ(signal_representations[1].signal_names[0].c_str(), "RSMerror");
    EXPECT_STREQ(signal_representations[1].signal_names[1].c_str(), "LSMerror");
    EXPECT_STREQ(signal_representations[2].signal_encoding_type_name.c_str(), "FaultStateEncoding");
    ASSERT_EQ(signal_representations[2].signal_names.size(), 1);
    EXPECT_STREQ(signal_representations[2].signal_names[0].c_str(), "IntError");
    EXPECT_STREQ(signal_representations[3].signal_encoding_type_name.c_str(), "LightEncoding");
    ASSERT_EQ(signal_representations[3].signal_names.size(), 2);
    EXPECT_STREQ(signal_representations[3].signal_names[0].c_str(), "RightIntLightsSwitch");
    EXPECT_STREQ(signal_representations[3].signal_names[1].c_str(), "LefttIntLightsSwitch");
}
