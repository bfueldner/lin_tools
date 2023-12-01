#include <fstream>
#include <iterator>
#include <string>
#include <variant>
#include <vector>

#include <gtest/gtest.h>

#include <lin/ldf/lin_description_file.hpp>
#include <lin/ldf/parser/lin_description_file.hpp>
#include <lin/ldf/schedule_table.hpp>
#include <lin/ldf/signal_encoding.hpp>
#include <lin/ldf/signal_standard.hpp>
#include <lin/test/main.hpp>

/* 9.2 LIN description file definition */

// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
class test_lin_ldf_parser: public testing::Test
{
  protected:
    static void SetUpTestSuite()
    {
        namespace x3 = boost::spirit::x3;

        using namespace lin::ldf;

        std::ifstream input(
            lin::test::binary_path.parent_path() / "example_22.ldf", std::ifstream::in);
        ASSERT_TRUE(input.good());

        std::string text(std::istreambuf_iterator< char >{ input }, {});
        auto position = text.begin();
        auto result   = phrase_parse(
            position,
            text.end(),
            parser::lin_description_file,
            x3::ascii::space,
            lin_description_file);
        ASSERT_TRUE(result);
    }

    static lin::ldf::lin_description_file_t lin_description_file;
};

lin::ldf::lin_description_file_t test_lin_ldf_parser::lin_description_file{};
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

TEST_F(test_lin_ldf_parser, global)
{
    EXPECT_STREQ(lin_description_file.protocol_version.c_str(), "2.2");
    EXPECT_STREQ(lin_description_file.language_version.c_str(), "2.2");
    EXPECT_EQ(lin_description_file.bitrate, 19.2);
    EXPECT_STREQ(lin_description_file.channel_name.c_str(), "DB");
}

TEST_F(test_lin_ldf_parser, participating_nodes)
{
    using namespace lin::ldf;

    EXPECT_STREQ(lin_description_file.nodes.master.name.c_str(), "CEM");
    EXPECT_EQ(lin_description_file.nodes.master.time_base, 5.0);
    EXPECT_EQ(lin_description_file.nodes.master.jitter, 0.1);
    EXPECT_EQ(lin_description_file.nodes.slaves, (nodes::slaves_t{ "LSM", "RSM" }));
}

TEST_F(test_lin_ldf_parser, node_composition)
{
    EXPECT_EQ(lin_description_file.node_compositions.size(), 0);
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST_F(test_lin_ldf_parser, standard_signals)
{
    using namespace lin::ldf;

    ASSERT_EQ(lin_description_file.standard_signals.size(), 6);
    {
        EXPECT_STREQ(
            lin_description_file.standard_signals[0].name.c_str(), "InternalLightsRequest");
        EXPECT_EQ(lin_description_file.standard_signals[0].size, 2);
        EXPECT_STREQ(lin_description_file.standard_signals[0].published_by.c_str(), "CEM");
        EXPECT_EQ(
            lin_description_file.standard_signals[0].subscribed_by,
            (std::vector< std::string >{ "LSM", "RSM" }));
    }
    {
        EXPECT_STREQ(lin_description_file.standard_signals[1].name.c_str(), "RightIntLightsSwitch");
        EXPECT_EQ(lin_description_file.standard_signals[1].size, 8);
        EXPECT_STREQ(lin_description_file.standard_signals[1].published_by.c_str(), "RSM");
        EXPECT_EQ(
            lin_description_file.standard_signals[1].subscribed_by,
            (std::vector< std::string >{ "CEM" }));
    }
    {
        EXPECT_STREQ(lin_description_file.standard_signals[2].name.c_str(), "LeftIntLightsSwitch");
        EXPECT_EQ(lin_description_file.standard_signals[2].size, 8);
        EXPECT_STREQ(lin_description_file.standard_signals[2].published_by.c_str(), "LSM");
        EXPECT_EQ(
            lin_description_file.standard_signals[2].subscribed_by,
            (std::vector< std::string >{ "CEM" }));
    }
    {
        EXPECT_STREQ(lin_description_file.standard_signals[3].name.c_str(), "LSMerror");
        EXPECT_EQ(lin_description_file.standard_signals[3].size, 1);
        EXPECT_STREQ(lin_description_file.standard_signals[3].published_by.c_str(), "LSM");
        EXPECT_EQ(
            lin_description_file.standard_signals[3].subscribed_by,
            (std::vector< std::string >{ "CEM" }));
    }
    {
        EXPECT_STREQ(lin_description_file.standard_signals[4].name.c_str(), "RSMerror");
        EXPECT_EQ(lin_description_file.standard_signals[4].size, 1);
        EXPECT_STREQ(lin_description_file.standard_signals[4].published_by.c_str(), "RSM");
        EXPECT_EQ(
            lin_description_file.standard_signals[4].subscribed_by,
            (std::vector< std::string >{ "CEM" }));
    }
    {
        EXPECT_STREQ(lin_description_file.standard_signals[5].name.c_str(), "IntError");
        EXPECT_EQ(lin_description_file.standard_signals[5].size, 2);
        EXPECT_STREQ(lin_description_file.standard_signals[5].published_by.c_str(), "LSM");
        EXPECT_EQ(
            lin_description_file.standard_signals[5].subscribed_by,
            (std::vector< std::string >{ "CEM" }));
    }

    for (const auto &standard_signal : lin_description_file.standard_signals)
    {
        const auto *init_value =
            std::get_if< signal::standard::init_value::scalar_t >(&standard_signal.init_value);
        ASSERT_NE(init_value, nullptr);
        EXPECT_EQ(*init_value, 0);
    }
}
// NOLINTEND(readability-function-cognitive-complexity)

TEST_F(test_lin_ldf_parser, diagnostic_signals)
{
    EXPECT_EQ(lin_description_file.diagnostic_signals.size(), 0);
}

TEST_F(test_lin_ldf_parser, unconditional_frames)
{
    using namespace lin::ldf;

    ASSERT_EQ(lin_description_file.unconditional_frames.size(), 5);
    {
        EXPECT_STREQ(lin_description_file.unconditional_frames[0].name.c_str(), "CEM_Frm1");
        EXPECT_EQ(lin_description_file.unconditional_frames[0].id, 1);
        EXPECT_STREQ(lin_description_file.unconditional_frames[0].published_by.c_str(), "CEM");
        EXPECT_EQ(lin_description_file.unconditional_frames[0].size, 1);
        ASSERT_EQ(lin_description_file.unconditional_frames[0].signals.size(), 1);
        EXPECT_STREQ(
            lin_description_file.unconditional_frames[0].signals[0].name.c_str(),
            "InternalLightsRequest");
        EXPECT_EQ(lin_description_file.unconditional_frames[0].signals[0].offset, 0);
    }
    {
        EXPECT_STREQ(lin_description_file.unconditional_frames[1].name.c_str(), "LSM_Frm1");
        EXPECT_EQ(lin_description_file.unconditional_frames[1].id, 2);
        EXPECT_STREQ(lin_description_file.unconditional_frames[1].published_by.c_str(), "LSM");
        EXPECT_EQ(lin_description_file.unconditional_frames[1].size, 2);
        ASSERT_EQ(lin_description_file.unconditional_frames[1].signals.size(), 1);
        EXPECT_STREQ(
            lin_description_file.unconditional_frames[1].signals[0].name.c_str(),
            "LeftIntLightsSwitch");
        EXPECT_EQ(lin_description_file.unconditional_frames[1].signals[0].offset, 8);
    }
    {
        EXPECT_STREQ(lin_description_file.unconditional_frames[2].name.c_str(), "LSM_Frm2");
        EXPECT_EQ(lin_description_file.unconditional_frames[2].id, 3);
        EXPECT_STREQ(lin_description_file.unconditional_frames[2].published_by.c_str(), "LSM");
        EXPECT_EQ(lin_description_file.unconditional_frames[2].size, 1);
        ASSERT_EQ(lin_description_file.unconditional_frames[2].signals.size(), 2);
        EXPECT_STREQ(
            lin_description_file.unconditional_frames[2].signals[0].name.c_str(), "LSMerror");
        EXPECT_EQ(lin_description_file.unconditional_frames[2].signals[0].offset, 0);
        EXPECT_STREQ(
            lin_description_file.unconditional_frames[2].signals[1].name.c_str(), "IntTest");
        EXPECT_EQ(lin_description_file.unconditional_frames[2].signals[1].offset, 1);
    }
    {
        EXPECT_STREQ(lin_description_file.unconditional_frames[3].name.c_str(), "RSM_Frm1");
        EXPECT_EQ(lin_description_file.unconditional_frames[3].id, 4);
        EXPECT_STREQ(lin_description_file.unconditional_frames[3].published_by.c_str(), "RSM");
        EXPECT_EQ(lin_description_file.unconditional_frames[3].size, 2);
        ASSERT_EQ(lin_description_file.unconditional_frames[3].signals.size(), 1);
        EXPECT_STREQ(
            lin_description_file.unconditional_frames[3].signals[0].name.c_str(),
            "RightIntLightsSwitch");
        EXPECT_EQ(lin_description_file.unconditional_frames[3].signals[0].offset, 8);
    }
    {
        EXPECT_STREQ(lin_description_file.unconditional_frames[4].name.c_str(), "RSM_Frm2");
        EXPECT_EQ(lin_description_file.unconditional_frames[4].id, 5);
        EXPECT_STREQ(lin_description_file.unconditional_frames[4].published_by.c_str(), "RSM");
        EXPECT_EQ(lin_description_file.unconditional_frames[4].size, 1);
        ASSERT_EQ(lin_description_file.unconditional_frames[4].signals.size(), 1);
        EXPECT_STREQ(
            lin_description_file.unconditional_frames[4].signals[0].name.c_str(), "RSMerror");
        EXPECT_EQ(lin_description_file.unconditional_frames[4].signals[0].offset, 0);
    }
}

TEST_F(test_lin_ldf_parser, sporadic_frames)
{
    EXPECT_EQ(lin_description_file.sporadic_frames.size(), 0);
}

TEST_F(test_lin_ldf_parser, event_triggered_frames)
{
    using namespace lin::ldf;

    ASSERT_EQ(lin_description_file.event_triggered_frames.size(), 1);
    EXPECT_STREQ(lin_description_file.event_triggered_frames[0].name.c_str(), "Node_Status_Event");
    EXPECT_STREQ(
        lin_description_file.event_triggered_frames[0].schedule_table.c_str(),
        "Collision_resolver");
    EXPECT_EQ(lin_description_file.event_triggered_frames[0].id, 0x06);
    EXPECT_EQ(
        lin_description_file.event_triggered_frames[0].frames,
        (std::vector< std::string >{ "RSM_Frm1", "LSM_Frm1" }));
}

TEST_F(test_lin_ldf_parser, diagnostic_frames)
{
    EXPECT_EQ(lin_description_file.diagnostic_frames.size(), 0);
}

TEST_F(test_lin_ldf_parser, node_attributes)
{
    using namespace lin::ldf;

    ASSERT_EQ(lin_description_file.node_attributes.size(), 2);
    {
        EXPECT_STREQ(lin_description_file.node_attributes[0].name.c_str(), "RSM");
        EXPECT_STREQ(lin_description_file.node_attributes[0].protocol_version.c_str(), "2.0");
        EXPECT_EQ(lin_description_file.node_attributes[0].configured_nad, 0x20);
    }
    {
        EXPECT_STREQ(lin_description_file.node_attributes[1].name.c_str(), "LSM");
        EXPECT_STREQ(lin_description_file.node_attributes[1].protocol_version.c_str(), "2.2");
        EXPECT_EQ(lin_description_file.node_attributes[1].configured_nad, 0x21);
    }
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST_F(test_lin_ldf_parser, schedule_tables)
{
    using namespace lin::ldf;

    ASSERT_EQ(lin_description_file.schedule_tables.size(), 5);
    {
        EXPECT_STREQ(
            lin_description_file.schedule_tables[0].name.c_str(), "Configuration_Schedule");
        ASSERT_EQ(lin_description_file.schedule_tables[0].entries.size(), 5);
        {
            auto *assign_nad = std::get_if< schedule_table::command::assign_nad_t >(
                &(lin_description_file.schedule_tables[0].entries[0].command));
            ASSERT_NE(assign_nad, nullptr);
            EXPECT_STREQ(assign_nad->node.c_str(), "LSM");
            EXPECT_EQ(lin_description_file.schedule_tables[0].entries[0].delay, 15.0);
        }
        {
            auto *assign_id_range = std::get_if< schedule_table::command::assign_frame_id_range_t >(
                &(lin_description_file.schedule_tables[0].entries[1].command));
            ASSERT_NE(assign_id_range, nullptr);
            EXPECT_STREQ(assign_id_range->node.c_str(), "LSM");
            EXPECT_EQ(assign_id_range->index, 0);
            EXPECT_EQ(assign_id_range->pids.size(), 0);
            EXPECT_EQ(lin_description_file.schedule_tables[0].entries[1].delay, 15.0);
        }
        {
            auto *assign_id = std::get_if< schedule_table::command::assign_frame_id_t >(
                &(lin_description_file.schedule_tables[0].entries[2].command));
            ASSERT_NE(assign_id, nullptr);
            EXPECT_STREQ(assign_id->node.c_str(), "RSM");
            EXPECT_STREQ(assign_id->frame.c_str(), "CEM_Frm1");
            EXPECT_EQ(lin_description_file.schedule_tables[0].entries[2].delay, 15.0);
        }
        {
            auto *assign_id = std::get_if< schedule_table::command::assign_frame_id_t >(
                &(lin_description_file.schedule_tables[0].entries[3].command));
            ASSERT_NE(assign_id, nullptr);
            EXPECT_STREQ(assign_id->node.c_str(), "RSM");
            EXPECT_STREQ(assign_id->frame.c_str(), "RSM_Frm1");
            EXPECT_EQ(lin_description_file.schedule_tables[0].entries[3].delay, 15.0);
        }
        {
            auto *assign_id = std::get_if< schedule_table::command::assign_frame_id_t >(
                &(lin_description_file.schedule_tables[0].entries[4].command));
            ASSERT_NE(assign_id, nullptr);
            EXPECT_STREQ(assign_id->node.c_str(), "RSM");
            EXPECT_STREQ(assign_id->frame.c_str(), "RSM_Frm2");
            EXPECT_EQ(lin_description_file.schedule_tables[0].entries[4].delay, 15.0);
        }
    }
    {
        EXPECT_STREQ(lin_description_file.schedule_tables[1].name.c_str(), "Normal_Schedule");
        ASSERT_EQ(lin_description_file.schedule_tables[1].entries.size(), 4);
        {
            auto *identifier = std::get_if< schedule_table::command::identifier_t >(
                &(lin_description_file.schedule_tables[1].entries[0].command));
            ASSERT_NE(identifier, nullptr);
            EXPECT_STREQ(identifier->c_str(), "CEM_Frm1");
            EXPECT_EQ(lin_description_file.schedule_tables[1].entries[0].delay, 15.0);
        }
        {
            auto *identifier = std::get_if< schedule_table::command::identifier_t >(
                &(lin_description_file.schedule_tables[1].entries[1].command));
            ASSERT_NE(identifier, nullptr);
            EXPECT_STREQ(identifier->c_str(), "LSM_Frm2");
            EXPECT_EQ(lin_description_file.schedule_tables[1].entries[1].delay, 15.0);
        }
        {
            auto *identifier = std::get_if< schedule_table::command::identifier_t >(
                &(lin_description_file.schedule_tables[1].entries[2].command));
            ASSERT_NE(identifier, nullptr);
            EXPECT_STREQ(identifier->c_str(), "RSM_Frm2");
            EXPECT_EQ(lin_description_file.schedule_tables[1].entries[2].delay, 15.0);
        }
        {
            auto *identifier = std::get_if< schedule_table::command::identifier_t >(
                &(lin_description_file.schedule_tables[1].entries[3].command));
            ASSERT_NE(identifier, nullptr);
            EXPECT_STREQ(identifier->c_str(), "Node_Status_Event");
            EXPECT_EQ(lin_description_file.schedule_tables[1].entries[3].delay, 10.0);
        }
    }
    {
        EXPECT_STREQ(lin_description_file.schedule_tables[2].name.c_str(), "MRF_schedule");
        ASSERT_EQ(lin_description_file.schedule_tables[2].entries.size(), 1);
        {
            auto *master_req = std::get_if< schedule_table::command::master_req_t >(
                &(lin_description_file.schedule_tables[2].entries[0].command));
            ASSERT_NE(master_req, nullptr);
            EXPECT_EQ(lin_description_file.schedule_tables[2].entries[0].delay, 10.0);
        }
    }
    {
        EXPECT_STREQ(lin_description_file.schedule_tables[3].name.c_str(), "SRF_schedule");
        ASSERT_EQ(lin_description_file.schedule_tables[3].entries.size(), 1);
        {
            auto *slave_resp = std::get_if< schedule_table::command::slave_resp_t >(
                &(lin_description_file.schedule_tables[3].entries[0].command));
            ASSERT_NE(slave_resp, nullptr);
            EXPECT_EQ(lin_description_file.schedule_tables[3].entries[0].delay, 10.0);
        }
    }
    {
        EXPECT_STREQ(lin_description_file.schedule_tables[4].name.c_str(), "Collision_resolver");
        ASSERT_EQ(lin_description_file.schedule_tables[4].entries.size(), 8);
        for (int index = 0; index < 2; index++)
        {
            {
                auto *identifier = std::get_if< schedule_table::command::identifier_t >(
                    &(lin_description_file.schedule_tables[4].entries[index * 4 + 0].command));
                ASSERT_NE(identifier, nullptr);
                EXPECT_STREQ(identifier->c_str(), "CEM_Frm1");
                EXPECT_EQ(
                    lin_description_file.schedule_tables[4].entries[index * 4 + 0].delay, 15.0);
            }
            {
                auto *identifier = std::get_if< schedule_table::command::identifier_t >(
                    &(lin_description_file.schedule_tables[4].entries[index * 4 + 1].command));
                ASSERT_NE(identifier, nullptr);
                EXPECT_STREQ(identifier->c_str(), "LSM_Frm2");
                EXPECT_EQ(
                    lin_description_file.schedule_tables[4].entries[index * 4 + 1].delay, 15.0);
            }
            {
                auto *identifier = std::get_if< schedule_table::command::identifier_t >(
                    &(lin_description_file.schedule_tables[4].entries[index * 4 + 2].command));
                ASSERT_NE(identifier, nullptr);
                EXPECT_STREQ(identifier->c_str(), "RSM_Frm2");
                EXPECT_EQ(
                    lin_description_file.schedule_tables[4].entries[index * 4 + 2].delay, 15.0);
            }

            if (index == 0)
            {
                auto *identifier = std::get_if< schedule_table::command::identifier_t >(
                    &(lin_description_file.schedule_tables[4].entries[3].command));
                ASSERT_NE(identifier, nullptr);
                EXPECT_STREQ(identifier->c_str(), "RSM_Frm1");
                EXPECT_EQ(lin_description_file.schedule_tables[4].entries[3].delay, 10.0);
            }
            else
            {
                auto *identifier = std::get_if< schedule_table::command::identifier_t >(
                    &(lin_description_file.schedule_tables[4].entries[7].command));
                ASSERT_NE(identifier, nullptr);
                EXPECT_STREQ(identifier->c_str(), "LSM_Frm1");
                EXPECT_EQ(lin_description_file.schedule_tables[4].entries[7].delay, 10.0);
            }
        }
    }
}
// NOLINTEND(readability-function-cognitive-complexity)

TEST_F(test_lin_ldf_parser, signal_groups)
{
    EXPECT_EQ(lin_description_file.signal_groups.size(), 0);
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST_F(test_lin_ldf_parser, signal_encodings)
{
    using namespace lin::ldf;

    ASSERT_EQ(lin_description_file.signal_encodings.size(), 4);
    {
        EXPECT_STREQ(lin_description_file.signal_encodings[0].name.c_str(), "Dig2Bit");
        ASSERT_EQ(lin_description_file.signal_encodings[0].values.size(), 4);
        // NOLINTBEGIN(readability-container-data-pointer)
        {
            auto *logical_value = std::get_if< signal::encoding::logical_value_t >(
                &(lin_description_file.signal_encodings[0].values[0]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->value, 0);
            EXPECT_STREQ(logical_value->text_info.c_str(), "off");
        }
        {
            auto *logical_value = std::get_if< signal::encoding::logical_value_t >(
                &(lin_description_file.signal_encodings[0].values[1]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->value, 1);
            EXPECT_STREQ(logical_value->text_info.c_str(), "on");
        }
        {
            auto *logical_value = std::get_if< signal::encoding::logical_value_t >(
                &(lin_description_file.signal_encodings[0].values[2]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->value, 2);
            EXPECT_STREQ(logical_value->text_info.c_str(), "error");
        }
        {
            auto *logical_value = std::get_if< signal::encoding::logical_value_t >(
                &(lin_description_file.signal_encodings[0].values[3]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->value, 3);
            EXPECT_STREQ(logical_value->text_info.c_str(), "void");
        }
        // NOLINTEND(readability-container-data-pointer)
    }
    {
        EXPECT_STREQ(lin_description_file.signal_encodings[1].name.c_str(), "ErrorEncoding");
        ASSERT_EQ(lin_description_file.signal_encodings[1].values.size(), 2);
        // NOLINTBEGIN(readability-container-data-pointer)
        {
            auto *logical_value = std::get_if< signal::encoding::logical_value_t >(
                &(lin_description_file.signal_encodings[1].values[0]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->value, 0);
            EXPECT_STREQ(logical_value->text_info.c_str(), "OK");
        }
        {
            auto *logical_value = std::get_if< signal::encoding::logical_value_t >(
                &(lin_description_file.signal_encodings[1].values[1]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->value, 1);
            EXPECT_STREQ(logical_value->text_info.c_str(), "error");
        }
        // NOLINTEND(readability-container-data-pointer)
    }
    {
        EXPECT_STREQ(lin_description_file.signal_encodings[2].name.c_str(), "FaultStateEncoding");
        ASSERT_EQ(lin_description_file.signal_encodings[2].values.size(), 4);
        // NOLINTBEGIN(readability-container-data-pointer)
        {
            auto *logical_value = std::get_if< signal::encoding::logical_value_t >(
                &(lin_description_file.signal_encodings[2].values[0]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->value, 0);
            EXPECT_STREQ(logical_value->text_info.c_str(), "No test result");
        }
        {
            auto *logical_value = std::get_if< signal::encoding::logical_value_t >(
                &(lin_description_file.signal_encodings[2].values[1]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->value, 1);
            EXPECT_STREQ(logical_value->text_info.c_str(), "failed");
        }
        {
            auto *logical_value = std::get_if< signal::encoding::logical_value_t >(
                &(lin_description_file.signal_encodings[2].values[2]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->value, 2);
            EXPECT_STREQ(logical_value->text_info.c_str(), "passed");
        }
        {
            auto *logical_value = std::get_if< signal::encoding::logical_value_t >(
                &(lin_description_file.signal_encodings[2].values[3]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->value, 3);
            EXPECT_STREQ(logical_value->text_info.c_str(), "not used");
        }
        // NOLINTEND(readability-container-data-pointer)
    }
    {
        EXPECT_STREQ(lin_description_file.signal_encodings[3].name.c_str(), "LightEncoding");
        ASSERT_EQ(lin_description_file.signal_encodings[3].values.size(), 3);
        // NOLINTBEGIN(readability-container-data-pointer)
        {
            auto *logical_value = std::get_if< signal::encoding::logical_value_t >(
                &(lin_description_file.signal_encodings[3].values[0]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->value, 0);
            EXPECT_STREQ(logical_value->text_info.c_str(), "Off");
        }
        {
            auto *physical_range = std::get_if< signal::encoding::physical_range_t >(
                &(lin_description_file.signal_encodings[3].values[1]));
            ASSERT_NE(physical_range, nullptr);
            EXPECT_EQ(physical_range->min, 1);
            EXPECT_EQ(physical_range->max, 254);
            EXPECT_EQ(physical_range->scale, 1.0);
            EXPECT_EQ(physical_range->offset, 100.0);
            EXPECT_STREQ(physical_range->text_info.c_str(), "lux");
        }
        {
            auto *logical_value = std::get_if< signal::encoding::logical_value_t >(
                &(lin_description_file.signal_encodings[3].values[2]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->value, 255);
            EXPECT_STREQ(logical_value->text_info.c_str(), "error");
        }
        // NOLINTEND(readability-container-data-pointer)
    }
}
// NOLINTEND(readability-function-cognitive-complexity)

TEST_F(test_lin_ldf_parser, signal_representations)
{
    using namespace lin::ldf;

    ASSERT_EQ(lin_description_file.signal_representations.size(), 4);
    {
        EXPECT_STREQ(lin_description_file.signal_representations[0].name.c_str(), "Dig2Bit");
        EXPECT_EQ(
            lin_description_file.signal_representations[0].signals,
            (std::vector< std::string >{ "InternalLightsRequest" }));
    }
    {
        EXPECT_STREQ(lin_description_file.signal_representations[1].name.c_str(), "ErrorEncoding");
        EXPECT_EQ(
            lin_description_file.signal_representations[1].signals,
            (std::vector< std::string >{ "RSMerror", "LSMerror" }));
    }
    {
        EXPECT_STREQ(
            lin_description_file.signal_representations[2].name.c_str(), "FaultStateEncoding");
        EXPECT_EQ(
            lin_description_file.signal_representations[2].signals,
            (std::vector< std::string >{ "IntError" }));
    }
    {
        EXPECT_STREQ(lin_description_file.signal_representations[3].name.c_str(), "LightEncoding");
        EXPECT_EQ(
            lin_description_file.signal_representations[3].signals,
            (std::vector< std::string >{ "RightIntLightsSwitch", "LeftIntLightsSwitch" }));
    }
}
