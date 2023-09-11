#include <gtest/gtest.h>

#include <lin/lexical/ldf/lin_description_file.hpp>
#include <lin/test/main.hpp>

#include <fstream>

/* 9.2 LIN description file definition */

// NOLINTBEGIN(cppcoreguidelines-avoid-non-const-global-variables)
class test_lin_lexical_ldf: public testing::Test
{
  protected:
    static void SetUpTestSuite()
    {
        namespace x3 = boost::spirit::x3;

        using namespace lin::lexical::ldf;

        std::ifstream input(
            lin::test::binary_path.parent_path() / "example.ldf", std::ifstream::in);
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
        std::cout << std::string{ position, text.end() } << std::endl;
    }

    static lin::lexical::ldf::lin_description_file_t lin_description_file;
};

lin::lexical::ldf::lin_description_file_t test_lin_lexical_ldf::lin_description_file{};
// NOLINTEND(cppcoreguidelines-avoid-non-const-global-variables)

TEST_F(test_lin_lexical_ldf, global)
{
    EXPECT_STREQ(lin_description_file.lin_protocol_version.c_str(), "2.2");
    EXPECT_STREQ(lin_description_file.lin_language_version.c_str(), "2.2");
    EXPECT_EQ(lin_description_file.lin_speed, 19.2);
    EXPECT_STREQ(lin_description_file.channel_name.c_str(), "DB");
}

TEST_F(test_lin_lexical_ldf, participating_nodes)
{
    using namespace lin::lexical::ldf;

    EXPECT_STREQ(lin_description_file.participating_nodes.master.node_name.c_str(), "CEM");
    EXPECT_EQ(lin_description_file.participating_nodes.master.time_base, 5.0);
    EXPECT_EQ(lin_description_file.participating_nodes.master.jitter, 0.1);
    EXPECT_EQ(
        lin_description_file.participating_nodes.slaves,
        (node::participating_nodes::slaves_t{ "LSM", "RSM" }));
}

TEST_F(test_lin_lexical_ldf, node_composition)
{
    EXPECT_EQ(lin_description_file.node_composition.size(), 0);
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST_F(test_lin_lexical_ldf, standard_signals)
{
    using namespace lin::lexical::ldf;

    ASSERT_EQ(lin_description_file.standard_signals.size(), 6);
    {
        EXPECT_STREQ(
            lin_description_file.standard_signals[0].signal_name.c_str(), "InternalLightsRequest");
        EXPECT_EQ(lin_description_file.standard_signals[0].signal_size, 2);
        EXPECT_STREQ(lin_description_file.standard_signals[0].published_by.c_str(), "CEM");
        EXPECT_EQ(
            lin_description_file.standard_signals[0].subscribed_by,
            (std::vector< std::string >{ "LSM", "RSM" }));
    }
    {
        EXPECT_STREQ(
            lin_description_file.standard_signals[1].signal_name.c_str(), "RightIntLightsSwitch");
        EXPECT_EQ(lin_description_file.standard_signals[1].signal_size, 8);
        EXPECT_STREQ(lin_description_file.standard_signals[1].published_by.c_str(), "RSM");
        EXPECT_EQ(
            lin_description_file.standard_signals[1].subscribed_by,
            (std::vector< std::string >{ "CEM" }));
    }
    {
        EXPECT_STREQ(
            lin_description_file.standard_signals[2].signal_name.c_str(), "LeftIntLightsSwitch");
        EXPECT_EQ(lin_description_file.standard_signals[2].signal_size, 8);
        EXPECT_STREQ(lin_description_file.standard_signals[2].published_by.c_str(), "LSM");
        EXPECT_EQ(
            lin_description_file.standard_signals[2].subscribed_by,
            (std::vector< std::string >{ "CEM" }));
    }
    {
        EXPECT_STREQ(lin_description_file.standard_signals[3].signal_name.c_str(), "LSMerror");
        EXPECT_EQ(lin_description_file.standard_signals[3].signal_size, 1);
        EXPECT_STREQ(lin_description_file.standard_signals[3].published_by.c_str(), "LSM");
        EXPECT_EQ(
            lin_description_file.standard_signals[3].subscribed_by,
            (std::vector< std::string >{ "CEM" }));
    }
    {
        EXPECT_STREQ(lin_description_file.standard_signals[4].signal_name.c_str(), "RSMerror");
        EXPECT_EQ(lin_description_file.standard_signals[4].signal_size, 1);
        EXPECT_STREQ(lin_description_file.standard_signals[4].published_by.c_str(), "RSM");
        EXPECT_EQ(
            lin_description_file.standard_signals[4].subscribed_by,
            (std::vector< std::string >{ "CEM" }));
    }
    {
        EXPECT_STREQ(lin_description_file.standard_signals[5].signal_name.c_str(), "IntTest");
        EXPECT_EQ(lin_description_file.standard_signals[5].signal_size, 2);
        EXPECT_STREQ(lin_description_file.standard_signals[5].published_by.c_str(), "LSM");
        EXPECT_EQ(
            lin_description_file.standard_signals[5].subscribed_by,
            (std::vector< std::string >{ "CEM" }));
    }

    for (const auto &standard_signal : lin_description_file.standard_signals)
    {
        const auto *init_value = std::get_if< signal::standard_signal::init_value_scalar_t >(
            &standard_signal.init_value);
        ASSERT_NE(init_value, nullptr);
        EXPECT_EQ(*init_value, 0);
    }
}
// NOLINTEND(readability-function-cognitive-complexity)

TEST_F(test_lin_lexical_ldf, diagnostic_signals)
{
    EXPECT_EQ(lin_description_file.diagnostic_signals.size(), 0);
}

TEST_F(test_lin_lexical_ldf, unconditional_frames)
{
    using namespace lin::lexical::ldf;

    ASSERT_EQ(lin_description_file.unconditional_frames.size(), 5);
    {
        EXPECT_STREQ(lin_description_file.unconditional_frames[0].frame_name.c_str(), "CEM_Frm1");
        EXPECT_EQ(lin_description_file.unconditional_frames[0].frame_id, 1);
        EXPECT_STREQ(lin_description_file.unconditional_frames[0].published_by.c_str(), "CEM");
        EXPECT_EQ(lin_description_file.unconditional_frames[0].frame_size, 1);
        ASSERT_EQ(lin_description_file.unconditional_frames[0].frame_entries.size(), 1);
        EXPECT_STREQ(
            lin_description_file.unconditional_frames[0].frame_entries[0].signal_name.c_str(),
            "InternalLightsRequest");
        EXPECT_EQ(lin_description_file.unconditional_frames[0].frame_entries[0].signal_offset, 0);
    }
    {
        EXPECT_STREQ(lin_description_file.unconditional_frames[1].frame_name.c_str(), "LSM_Frm1");
        EXPECT_EQ(lin_description_file.unconditional_frames[1].frame_id, 2);
        EXPECT_STREQ(lin_description_file.unconditional_frames[1].published_by.c_str(), "LSM");
        EXPECT_EQ(lin_description_file.unconditional_frames[1].frame_size, 2);
        ASSERT_EQ(lin_description_file.unconditional_frames[1].frame_entries.size(), 1);
        EXPECT_STREQ(
            lin_description_file.unconditional_frames[1].frame_entries[0].signal_name.c_str(),
            "LeftIntLightsSwitch");
        EXPECT_EQ(lin_description_file.unconditional_frames[1].frame_entries[0].signal_offset, 8);
    }
    {
        EXPECT_STREQ(lin_description_file.unconditional_frames[2].frame_name.c_str(), "LSM_Frm2");
        EXPECT_EQ(lin_description_file.unconditional_frames[2].frame_id, 3);
        EXPECT_STREQ(lin_description_file.unconditional_frames[2].published_by.c_str(), "LSM");
        EXPECT_EQ(lin_description_file.unconditional_frames[2].frame_size, 1);
        ASSERT_EQ(lin_description_file.unconditional_frames[2].frame_entries.size(), 2);
        EXPECT_STREQ(
            lin_description_file.unconditional_frames[2].frame_entries[0].signal_name.c_str(),
            "LSMerror");
        EXPECT_EQ(lin_description_file.unconditional_frames[2].frame_entries[0].signal_offset, 0);
        EXPECT_STREQ(
            lin_description_file.unconditional_frames[2].frame_entries[1].signal_name.c_str(),
            "IntTest");
        EXPECT_EQ(lin_description_file.unconditional_frames[2].frame_entries[1].signal_offset, 1);
    }
    {
        EXPECT_STREQ(lin_description_file.unconditional_frames[3].frame_name.c_str(), "RSM_Frm1");
        EXPECT_EQ(lin_description_file.unconditional_frames[3].frame_id, 4);
        EXPECT_STREQ(lin_description_file.unconditional_frames[3].published_by.c_str(), "RSM");
        EXPECT_EQ(lin_description_file.unconditional_frames[3].frame_size, 2);
        ASSERT_EQ(lin_description_file.unconditional_frames[3].frame_entries.size(), 1);
        EXPECT_STREQ(
            lin_description_file.unconditional_frames[3].frame_entries[0].signal_name.c_str(),
            "RightIntLightsSwitch");
        EXPECT_EQ(lin_description_file.unconditional_frames[3].frame_entries[0].signal_offset, 8);
    }
    {
        EXPECT_STREQ(lin_description_file.unconditional_frames[4].frame_name.c_str(), "RSM_Frm2");
        EXPECT_EQ(lin_description_file.unconditional_frames[4].frame_id, 5);
        EXPECT_STREQ(lin_description_file.unconditional_frames[4].published_by.c_str(), "RSM");
        EXPECT_EQ(lin_description_file.unconditional_frames[4].frame_size, 1);
        ASSERT_EQ(lin_description_file.unconditional_frames[4].frame_entries.size(), 1);
        EXPECT_STREQ(
            lin_description_file.unconditional_frames[4].frame_entries[0].signal_name.c_str(),
            "RSMerror");
        EXPECT_EQ(lin_description_file.unconditional_frames[4].frame_entries[0].signal_offset, 0);
    }
}

TEST_F(test_lin_lexical_ldf, sporadic_frames)
{
    EXPECT_EQ(lin_description_file.sporadic_frames.size(), 0);
}

TEST_F(test_lin_lexical_ldf, event_triggered_frames)
{
    using namespace lin::lexical::ldf;

    ASSERT_EQ(lin_description_file.event_triggered_frames.size(), 1);
    EXPECT_STREQ(
        lin_description_file.event_triggered_frames[0].event_trig_frm_name.c_str(),
        "Node_Status_Event");
    EXPECT_STREQ(
        lin_description_file.event_triggered_frames[0].collision_resolving_schedule_table.c_str(),
        "Collision_resolver");
    EXPECT_EQ(lin_description_file.event_triggered_frames[0].frame_id, 0x06);
    EXPECT_EQ(
        lin_description_file.event_triggered_frames[0].frame_names,
        (std::vector< std::string >{ "RSM_Frm1", "LSM_Frm1" }));
}

TEST_F(test_lin_lexical_ldf, diagnostic_frames)
{
    EXPECT_EQ(lin_description_file.diagnostic_frames.size(), 0);
}

TEST_F(test_lin_lexical_ldf, node_attributes)
{
    using namespace lin::lexical::ldf;

    ASSERT_EQ(lin_description_file.node_attributes.size(), 2);
    {
        EXPECT_STREQ(lin_description_file.node_attributes[0].node_name.c_str(), "RSM");
        EXPECT_STREQ(lin_description_file.node_attributes[0].lin_protocol.c_str(), "2.0");
        EXPECT_EQ(lin_description_file.node_attributes[0].configured_nad, 0x20);
    }
    {
        EXPECT_STREQ(lin_description_file.node_attributes[1].node_name.c_str(), "LSM");
        EXPECT_STREQ(lin_description_file.node_attributes[1].lin_protocol.c_str(), "2.2");
        EXPECT_EQ(lin_description_file.node_attributes[1].configured_nad, 0x21);
    }
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST_F(test_lin_lexical_ldf, schedule_tables)
{
    using namespace lin::lexical::ldf;

    ASSERT_EQ(lin_description_file.schedule_tables.size(), 5);
    {
        EXPECT_STREQ(
            lin_description_file.schedule_tables[0].schedule_table_name.c_str(),
            "Configuration_Schedule");
        ASSERT_EQ(lin_description_file.schedule_tables[0].table_entries.size(), 5);
        {
            auto *assign_nad = std::get_if< schedule_table::command::assign_nad_t >(
                &(lin_description_file.schedule_tables[0].table_entries[0].command));
            ASSERT_NE(assign_nad, nullptr);
            EXPECT_STREQ(assign_nad->node_name.c_str(), "LSM");
            EXPECT_EQ(lin_description_file.schedule_tables[0].table_entries[0].frame_time, 15.0);
        }
        {
            auto *assign_frame_id_range =
                std::get_if< schedule_table::command::assign_frame_id_range_t >(
                    &(lin_description_file.schedule_tables[0].table_entries[1].command));
            ASSERT_NE(assign_frame_id_range, nullptr);
            EXPECT_STREQ(assign_frame_id_range->node_name.c_str(), "LSM");
            EXPECT_EQ(assign_frame_id_range->frame_index, 0);
            EXPECT_EQ(assign_frame_id_range->frame_pids.size(), 0);
            EXPECT_EQ(lin_description_file.schedule_tables[0].table_entries[1].frame_time, 15.0);
        }
        {
            auto *assign_frame_id = std::get_if< schedule_table::command::assign_frame_id_t >(
                &(lin_description_file.schedule_tables[0].table_entries[2].command));
            ASSERT_NE(assign_frame_id, nullptr);
            EXPECT_STREQ(assign_frame_id->node_name.c_str(), "RSM");
            EXPECT_STREQ(assign_frame_id->frame_name.c_str(), "CEM_Frm1");
            EXPECT_EQ(lin_description_file.schedule_tables[0].table_entries[2].frame_time, 15.0);
        }
        {
            auto *assign_frame_id = std::get_if< schedule_table::command::assign_frame_id_t >(
                &(lin_description_file.schedule_tables[0].table_entries[3].command));
            ASSERT_NE(assign_frame_id, nullptr);
            EXPECT_STREQ(assign_frame_id->node_name.c_str(), "RSM");
            EXPECT_STREQ(assign_frame_id->frame_name.c_str(), "RSM_Frm1");
            EXPECT_EQ(lin_description_file.schedule_tables[0].table_entries[3].frame_time, 15.0);
        }
        {
            auto *assign_frame_id = std::get_if< schedule_table::command::assign_frame_id_t >(
                &(lin_description_file.schedule_tables[0].table_entries[4].command));
            ASSERT_NE(assign_frame_id, nullptr);
            EXPECT_STREQ(assign_frame_id->node_name.c_str(), "RSM");
            EXPECT_STREQ(assign_frame_id->frame_name.c_str(), "RSM_Frm2");
            EXPECT_EQ(lin_description_file.schedule_tables[0].table_entries[4].frame_time, 15.0);
        }
    }
    {
        EXPECT_STREQ(
            lin_description_file.schedule_tables[1].schedule_table_name.c_str(), "Normal_Schedule");
        ASSERT_EQ(lin_description_file.schedule_tables[1].table_entries.size(), 4);
        {
            auto *identifier = std::get_if< schedule_table::command::identifier_t >(
                &(lin_description_file.schedule_tables[1].table_entries[0].command));
            ASSERT_NE(identifier, nullptr);
            EXPECT_STREQ(identifier->c_str(), "CEM_Frm1");
            EXPECT_EQ(lin_description_file.schedule_tables[1].table_entries[0].frame_time, 15.0);
        }
        {
            auto *identifier = std::get_if< schedule_table::command::identifier_t >(
                &(lin_description_file.schedule_tables[1].table_entries[1].command));
            ASSERT_NE(identifier, nullptr);
            EXPECT_STREQ(identifier->c_str(), "LSM_Frm2");
            EXPECT_EQ(lin_description_file.schedule_tables[1].table_entries[1].frame_time, 15.0);
        }
        {
            auto *identifier = std::get_if< schedule_table::command::identifier_t >(
                &(lin_description_file.schedule_tables[1].table_entries[2].command));
            ASSERT_NE(identifier, nullptr);
            EXPECT_STREQ(identifier->c_str(), "RSM_Frm2");
            EXPECT_EQ(lin_description_file.schedule_tables[1].table_entries[2].frame_time, 15.0);
        }
        {
            auto *identifier = std::get_if< schedule_table::command::identifier_t >(
                &(lin_description_file.schedule_tables[1].table_entries[3].command));
            ASSERT_NE(identifier, nullptr);
            EXPECT_STREQ(identifier->c_str(), "Node_Status_Event");
            EXPECT_EQ(lin_description_file.schedule_tables[1].table_entries[3].frame_time, 10.0);
        }
    }
    {
        EXPECT_STREQ(
            lin_description_file.schedule_tables[2].schedule_table_name.c_str(), "MRF_schedule");
        ASSERT_EQ(lin_description_file.schedule_tables[2].table_entries.size(), 1);
        {
            auto *master_req = std::get_if< schedule_table::command::master_req_t >(
                &(lin_description_file.schedule_tables[2].table_entries[0].command));
            ASSERT_NE(master_req, nullptr);
            EXPECT_EQ(lin_description_file.schedule_tables[2].table_entries[0].frame_time, 10.0);
        }
    }
    {
        EXPECT_STREQ(
            lin_description_file.schedule_tables[3].schedule_table_name.c_str(), "SRF_schedule");
        ASSERT_EQ(lin_description_file.schedule_tables[3].table_entries.size(), 1);
        {
            auto *slave_resp = std::get_if< schedule_table::command::slave_resp_t >(
                &(lin_description_file.schedule_tables[3].table_entries[0].command));
            ASSERT_NE(slave_resp, nullptr);
            EXPECT_EQ(lin_description_file.schedule_tables[3].table_entries[0].frame_time, 10.0);
        }
    }
    {
        EXPECT_STREQ(
            lin_description_file.schedule_tables[4].schedule_table_name.c_str(),
            "Collision_resolver");
        ASSERT_EQ(lin_description_file.schedule_tables[4].table_entries.size(), 8);
        for (int index = 0; index < 2; index++)
        {
            {
                auto *identifier = std::get_if< schedule_table::command::identifier_t >(&(
                    lin_description_file.schedule_tables[4].table_entries[index * 4 + 0].command));
                ASSERT_NE(identifier, nullptr);
                EXPECT_STREQ(identifier->c_str(), "CEM_Frm1");
                EXPECT_EQ(
                    lin_description_file.schedule_tables[4].table_entries[index * 4 + 0].frame_time,
                    15.0);
            }
            {
                auto *identifier = std::get_if< schedule_table::command::identifier_t >(&(
                    lin_description_file.schedule_tables[4].table_entries[index * 4 + 1].command));
                ASSERT_NE(identifier, nullptr);
                EXPECT_STREQ(identifier->c_str(), "LSM_Frm2");
                EXPECT_EQ(
                    lin_description_file.schedule_tables[4].table_entries[index * 4 + 1].frame_time,
                    15.0);
            }
            {
                auto *identifier = std::get_if< schedule_table::command::identifier_t >(&(
                    lin_description_file.schedule_tables[4].table_entries[index * 4 + 2].command));
                ASSERT_NE(identifier, nullptr);
                EXPECT_STREQ(identifier->c_str(), "RSM_Frm2");
                EXPECT_EQ(
                    lin_description_file.schedule_tables[4].table_entries[index * 4 + 2].frame_time,
                    15.0);
            }

            if (index == 0)
            {
                auto *identifier = std::get_if< schedule_table::command::identifier_t >(
                    &(lin_description_file.schedule_tables[4].table_entries[3].command));
                ASSERT_NE(identifier, nullptr);
                EXPECT_STREQ(identifier->c_str(), "RSM_Frm1");
                EXPECT_EQ(
                    lin_description_file.schedule_tables[4].table_entries[3].frame_time, 10.0);
            }
            else
            {
                auto *identifier = std::get_if< schedule_table::command::identifier_t >(
                    &(lin_description_file.schedule_tables[4].table_entries[7].command));
                ASSERT_NE(identifier, nullptr);
                EXPECT_STREQ(identifier->c_str(), "LSM_Frm1");
                EXPECT_EQ(
                    lin_description_file.schedule_tables[4].table_entries[7].frame_time, 10.0);
            }
        }
    }
}
// NOLINTEND(readability-function-cognitive-complexity)

TEST_F(test_lin_lexical_ldf, signal_groups)
{
    EXPECT_EQ(lin_description_file.signal_groups.size(), 0);
}

// NOLINTBEGIN(readability-function-cognitive-complexity)
TEST_F(test_lin_lexical_ldf, signal_encoding_types)
{
    using namespace lin::lexical::ldf;

    ASSERT_EQ(lin_description_file.signal_encoding_types.size(), 4);
    {
        EXPECT_STREQ(
            lin_description_file.signal_encoding_types[0].signal_encoding_type_name.c_str(),
            "Dig2Bit");
        ASSERT_EQ(lin_description_file.signal_encoding_types[0].values.size(), 4);
        // NOLINTBEGIN(readability-container-data-pointer)
        {
            auto *logical_value = std::get_if< signal_encoding_type::logical_value_t >(
                &(lin_description_file.signal_encoding_types[0].values[0]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->signal_value, 0);
            EXPECT_STREQ(logical_value->text_info.c_str(), "off");
        }
        {
            auto *logical_value = std::get_if< signal_encoding_type::logical_value_t >(
                &(lin_description_file.signal_encoding_types[0].values[1]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->signal_value, 1);
            EXPECT_STREQ(logical_value->text_info.c_str(), "on");
        }
        {
            auto *logical_value = std::get_if< signal_encoding_type::logical_value_t >(
                &(lin_description_file.signal_encoding_types[0].values[2]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->signal_value, 2);
            EXPECT_STREQ(logical_value->text_info.c_str(), "error");
        }
        {
            auto *logical_value = std::get_if< signal_encoding_type::logical_value_t >(
                &(lin_description_file.signal_encoding_types[0].values[3]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->signal_value, 3);
            EXPECT_STREQ(logical_value->text_info.c_str(), "void");
        }
        // NOLINTEND(readability-container-data-pointer)
    }
    {
        EXPECT_STREQ(
            lin_description_file.signal_encoding_types[1].signal_encoding_type_name.c_str(),
            "ErrorEncoding");
        ASSERT_EQ(lin_description_file.signal_encoding_types[1].values.size(), 2);
        // NOLINTBEGIN(readability-container-data-pointer)
        {
            auto *logical_value = std::get_if< signal_encoding_type::logical_value_t >(
                &(lin_description_file.signal_encoding_types[1].values[0]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->signal_value, 0);
            EXPECT_STREQ(logical_value->text_info.c_str(), "OK");
        }
        {
            auto *logical_value = std::get_if< signal_encoding_type::logical_value_t >(
                &(lin_description_file.signal_encoding_types[1].values[1]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->signal_value, 1);
            EXPECT_STREQ(logical_value->text_info.c_str(), "error");
        }
        // NOLINTEND(readability-container-data-pointer)
    }
    {
        EXPECT_STREQ(
            lin_description_file.signal_encoding_types[2].signal_encoding_type_name.c_str(),
            "FaultStateEncoding");
        ASSERT_EQ(lin_description_file.signal_encoding_types[2].values.size(), 4);
        // NOLINTBEGIN(readability-container-data-pointer)
        {
            auto *logical_value = std::get_if< signal_encoding_type::logical_value_t >(
                &(lin_description_file.signal_encoding_types[2].values[0]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->signal_value, 0);
            EXPECT_STREQ(logical_value->text_info.c_str(), "No test result");
        }
        {
            auto *logical_value = std::get_if< signal_encoding_type::logical_value_t >(
                &(lin_description_file.signal_encoding_types[2].values[1]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->signal_value, 1);
            EXPECT_STREQ(logical_value->text_info.c_str(), "failed");
        }
        {
            auto *logical_value = std::get_if< signal_encoding_type::logical_value_t >(
                &(lin_description_file.signal_encoding_types[2].values[2]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->signal_value, 2);
            EXPECT_STREQ(logical_value->text_info.c_str(), "passed");
        }
        {
            auto *logical_value = std::get_if< signal_encoding_type::logical_value_t >(
                &(lin_description_file.signal_encoding_types[2].values[3]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->signal_value, 3);
            EXPECT_STREQ(logical_value->text_info.c_str(), "not used");
        }
        // NOLINTEND(readability-container-data-pointer)
    }
    {
        EXPECT_STREQ(
            lin_description_file.signal_encoding_types[3].signal_encoding_type_name.c_str(),
            "LightEncoding");
        ASSERT_EQ(lin_description_file.signal_encoding_types[3].values.size(), 3);
        // NOLINTBEGIN(readability-container-data-pointer)
        {
            auto *logical_value = std::get_if< signal_encoding_type::logical_value_t >(
                &(lin_description_file.signal_encoding_types[3].values[0]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->signal_value, 0);
            EXPECT_STREQ(logical_value->text_info.c_str(), "Off");
        }
        {
            auto *physical_range = std::get_if< signal_encoding_type::physical_range_t >(
                &(lin_description_file.signal_encoding_types[3].values[1]));
            ASSERT_NE(physical_range, nullptr);
            EXPECT_EQ(physical_range->min_value, 1);
            EXPECT_EQ(physical_range->max_value, 254);
            EXPECT_EQ(physical_range->scale, 1.0);
            EXPECT_EQ(physical_range->offset, 100.0);
            EXPECT_STREQ(physical_range->text_info.c_str(), "lux");
        }
        {
            auto *logical_value = std::get_if< signal_encoding_type::logical_value_t >(
                &(lin_description_file.signal_encoding_types[3].values[2]));
            ASSERT_NE(logical_value, nullptr);
            EXPECT_EQ(logical_value->signal_value, 255);
            EXPECT_STREQ(logical_value->text_info.c_str(), "error");
        }
        // NOLINTEND(readability-container-data-pointer)
    }
}
// NOLINTEND(readability-function-cognitive-complexity)

TEST_F(test_lin_lexical_ldf, signal_representations)
{
    using namespace lin::lexical::ldf;

    ASSERT_EQ(lin_description_file.signal_representations.size(), 4);
    {
        EXPECT_STREQ(
            lin_description_file.signal_representations[0].signal_encoding_type_name.c_str(),
            "Dig2Bit");
        EXPECT_EQ(
            lin_description_file.signal_representations[0].signal_names,
            (std::vector< std::string >{ "InternalLightsRequest" }));
    }
    {
        EXPECT_STREQ(
            lin_description_file.signal_representations[1].signal_encoding_type_name.c_str(),
            "ErrorEncoding");
        EXPECT_EQ(
            lin_description_file.signal_representations[1].signal_names,
            (std::vector< std::string >{ "RSMerror", "LSMerror" }));
    }
    {
        EXPECT_STREQ(
            lin_description_file.signal_representations[2].signal_encoding_type_name.c_str(),
            "FaultStateEncoding");
        EXPECT_EQ(
            lin_description_file.signal_representations[2].signal_names,
            (std::vector< std::string >{ "IntError" }));
    }
    {
        EXPECT_STREQ(
            lin_description_file.signal_representations[3].signal_encoding_type_name.c_str(),
            "LightEncoding");
        EXPECT_EQ(
            lin_description_file.signal_representations[3].signal_names,
            (std::vector< std::string >{ "RightIntLightsSwitch", "LefttIntLightsSwitch" }));
    }
}
