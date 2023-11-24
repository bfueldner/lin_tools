#include <cctype>
#include <string>
#include <vector>

#include <lin/common/validate/check.hpp>
#include <lin/common/validate/logger.hpp>
#include <lin/common/validate/signal_encoding.hpp>
#include <lin/ldf/lin_description_file.hpp>
#include <lin/ldf/validate/check.hpp>
#include <lin/ldf/validate/frame_diagnostic.hpp>
#include <lin/ldf/validate/frame_event_triggered.hpp>
#include <lin/ldf/validate/frame_sporadic.hpp>
#include <lin/ldf/validate/frame_unconditional.hpp>
#include <lin/ldf/validate/lin_description_file.hpp>
#include <lin/ldf/validate/node_attribute.hpp>
#include <lin/ldf/validate/node_composition.hpp>
#include <lin/ldf/validate/nodes.hpp>
#include <lin/ldf/validate/schedule_table.hpp>
#include <lin/ldf/validate/signal_diagnostic.hpp>
#include <lin/ldf/validate/signal_encoding.hpp>
#include <lin/ldf/validate/signal_group.hpp>
#include <lin/ldf/validate/signal_representation.hpp>
#include <lin/ldf/validate/signal_standard.hpp>

/* 9.2 LIN description file definition */

namespace lin::ldf::validate {

namespace lin_description_file {

void channel_name_t::run(const ldf::lin_description_file_t &lin_description_file) const
{
    if (!lin_description_file.channel_name.empty())
    {
        if (std::isdigit(*lin_description_file.channel_name.data()) != 0)
        {
            _log_warning(
                "Name starts with numeric character",
                std::string{ *lin_description_file.channel_name.data() },
                "A-Z/a-z");
            return;
        }

        _log_ok();
    }
}

}    // namespace lin_description_file

// NOLINTBEGIN(readability-function-cognitive-complexity)
void lin_description_file_t::run(const ldf::lin_description_file_t &lin_description_file) const
{
    /* 9.2.1 Global definition */

    auto validate_global_language_version =
        validate::lin_description_file::language_version_t{ _logger };
    auto validate_global_protocol_version =
        validate::lin_description_file::protocol_version_t{ _logger };
    auto validate_global_bitrate      = validate::lin_description_file::bitrate_t{ _logger };
    auto validate_global_channel_name = validate::lin_description_file::channel_name_t{ _logger };
    auto validate_global_node_attribute_names =
        validate::lin_description_file::node_attribute_names_t{ _logger };
    auto validate_global_node_composition_names =
        validate::lin_description_file::node_composition_names_t{ _logger };
    auto validate_global_standard_signal_names =
        validate::lin_description_file::standard_signal_names_t{ _logger };
    auto validate_global_diagnostic_signal_names =
        validate::lin_description_file::diagnostic_signal_names_t{ _logger };
    auto validate_global_signal_group_names =
        validate::lin_description_file::signal_group_names_t{ _logger };

    auto validate_global_unconditional_frame_names =
        validate::lin_description_file::unconditional_frame_names_t{ _logger };
    auto validate_global_sporadic_frame_names =
        validate::lin_description_file::sporadic_frame_names_t{ _logger };
    auto validate_global_event_triggered_frame_names =
        validate::lin_description_file::event_triggered_frame_names_t{ _logger };
    auto validate_global_diagnostic_frame_names =
        validate::lin_description_file::diagnostic_frame_names_t{ _logger };
    auto validate_global_schedule_table_names =
        validate::lin_description_file::schedule_table_names_t{ _logger };
    auto validate_global_signal_encoding_names =
        validate::lin_description_file::signal_encoding_names_t{ _logger };
    auto validate_global_signal_representation_names =
        validate::lin_description_file::signal_representation_names_t{ _logger };
    std::vector< validate::check::lin_description_file_t * > const ldf_checks{
        &validate_global_language_version,
        &validate_global_protocol_version,
        &validate_global_bitrate,
        &validate_global_channel_name,
        &validate_global_node_attribute_names,
        &validate_global_node_composition_names,
        &validate_global_standard_signal_names,
        &validate_global_diagnostic_signal_names,
        &validate_global_signal_group_names,
        &validate_global_unconditional_frame_names,
        &validate_global_sporadic_frame_names,
        &validate_global_event_triggered_frame_names,
        &validate_global_diagnostic_frame_names,
        &validate_global_schedule_table_names,
        &validate_global_signal_encoding_names,
        &validate_global_signal_representation_names
    };

    /* 9.2.2 Node definition */

    auto validate_nodes_master_time_base = validate::nodes::master_time_base_t{ _logger };
    auto validate_nodes_master_jitter    = validate::nodes::master_jitter_t{ _logger };
    auto validate_nodes_node_names       = validate::nodes::node_names_t{ _logger };
    std::vector< validate::check::nodes_t * > const nodes_checks{
        &validate_nodes_master_time_base,
        &validate_nodes_master_jitter,
        &validate_nodes_node_names,
    };

    /* 9.2.2.2 Node attributes */

    auto validate_node_attribute_protocol_version =
        validate::node::attribute::protocol_version_t{ _logger };
    auto validate_node_attribute_configured_nad =
        validate::node::attribute::configured_nad_t{ _logger };
    auto validate_node_attribute_initial_nad = validate::node::attribute::initial_nad_t{ _logger };
    auto validate_node_attribute_attributes  = validate::node::attribute::attributes_t{ _logger };
    auto validate_node_attribute_configurable_frames =
        validate::node::attribute::configurable_frames_t{ _logger };
    std::vector< validate::check::node_attribute_t * > const node_attribute_checks{
        &validate_node_attribute_protocol_version,
        &validate_node_attribute_configured_nad,
        &validate_node_attribute_initial_nad,
        &validate_node_attribute_attributes,
        &validate_node_attribute_configurable_frames
    };

    /* 9.2.2.3 Node composition definition */

    auto validate_node_composition_composite_name =
        validate::node::composition::composite_names_t{ _logger };
    std::vector< validate::check::node_composition_configuration_t * > const
        node_composition_configuration_checks{ &validate_node_composition_composite_name };

    auto validate_node_composition_configuration_composite_nodes =
        validate::node::composition::configuration::composite_nodes_t{ _logger };
    std::vector< validate::check::node_composition_configuration_composite_t * > const
        node_composition_configuration_composite_checks{
            &validate_node_composition_configuration_composite_nodes
        };

    /* 9.2.3.1 Standard signals */

    auto validate_standard_signal_size       = validate::signal::standard::size_t{ _logger };
    auto validate_standard_signal_init_value = validate::signal::standard::init_value_t{ _logger };
    auto validate_standard_signal_published_by =
        validate::signal::standard::published_by_t{ _logger };
    auto validate_standard_signal_subscribed_by =
        validate::signal::standard::subscribed_by_t{ _logger };
    std::vector< validate::check::standard_signal_t * > const standard_signal_checks{
        &validate_standard_signal_size,
        &validate_standard_signal_init_value,
        &validate_standard_signal_published_by,
        &validate_standard_signal_subscribed_by
    };

    /* 9.2.3.2 Diagnostic signals */

    auto validate_diagnostic_signal_size = validate::signal::diagnostic::size_t{ _logger };
    auto validate_diagnostic_signal_init_value =
        validate::signal::diagnostic::init_value_t{ _logger };
    std::vector< validate::check::diagnostic_signal_t * > const diagnostic_signal_checks{
        &validate_diagnostic_signal_size, &validate_diagnostic_signal_init_value
    };

    /* 9.2.3.3 Signal groups */

    auto validate_signal_group_size = validate::signal::group::size_t{ _logger };
    std::vector< validate::check::signal_group_t * > const signal_group_checks{
        &validate_signal_group_size
    };

    /* 9.2.4.1 Unconditional frames */

    auto validate_unconditional_frame_id = validate::frame::unconditional::id_t{ _logger };
    auto validate_unconditional_frame_published_by =
        validate::frame::unconditional::published_by_t{ _logger };
    auto validate_unconditional_frame_size = validate::frame::unconditional::size_t{ _logger };
    auto validate_unconditional_frame_signal_published_by =
        validate::frame::unconditional::signal_published_by_t{ _logger };
    auto validate_unconditional_frame_signal_sizes =
        validate::frame::unconditional::signal_sizes_t{ _logger };
    auto validate_unconditional_frame_signal_offsets =
        validate::frame::unconditional::signal_offsets_t{ _logger };
    auto validate_unconditional_frame_signals =
        validate::frame::unconditional::signals_t{ _logger };
    std::vector< validate::check::unconditional_frame_t * > const unconditional_frame_checks{
        &validate_unconditional_frame_id,
        &validate_unconditional_frame_published_by,
        &validate_unconditional_frame_size,
        &validate_unconditional_frame_signal_published_by,
        &validate_unconditional_frame_signal_sizes,
        &validate_unconditional_frame_signal_offsets,
        &validate_unconditional_frame_signals
    };

    auto validate_unconditional_frame_signal_name =
        validate::frame::unconditional::signal::name_t{ _logger };
    auto validate_unconditional_frame_signal_offset =
        validate::frame::unconditional::signal::offset_t{ _logger };
    std::vector< validate::check::unconditional_frame_signal_t * > const
        unconditional_frame_signal_checks{ &validate_unconditional_frame_signal_name,
                                           &validate_unconditional_frame_signal_offset };

    /* 9.2.4.2 Sporadic frames */

    auto validate_sporadic_frame_frames = validate::frame::sporadic::frames_t{ _logger };
    std::vector< validate::check::sporadic_frame_t * > const sporadic_frame_checks{
        &validate_sporadic_frame_frames
    };

    /* 9.2.4.3 Event triggered frames */

    auto validate_event_triggered_frame_schedule_table =
        validate::frame::event_triggered::schedule_table_t{ _logger };
    auto validate_event_triggered_frame_id = validate::frame::event_triggered::id_t{ _logger };
    auto validate_event_triggered_frame_frames =
        validate::frame::event_triggered::frames_t{ _logger };
    std::vector< validate::check::event_triggered_frame_t * > const event_triggered_frame_checks{
        &validate_event_triggered_frame_schedule_table,
        &validate_event_triggered_frame_id,
        &validate_event_triggered_frame_frames
    };

    /* 9.2.4.4 Diagnostic frames */

    auto validate_diagnostic_frame_id      = validate::frame::diagnostic::id_t{ _logger };
    auto validate_diagnostic_frame_signals = validate::frame::diagnostic::signals_t{ _logger };
    std::vector< validate::check::diagnostic_frame_t * > const diagnostic_frame_checks{
        &validate_diagnostic_frame_id, &validate_diagnostic_frame_signals
    };

    auto validate_diagnostic_frame_signal_name =
        validate::frame::diagnostic::signal::name_t{ _logger };
    auto validate_diagnostic_frame_signal_offset =
        validate::frame::diagnostic::signal::offset_t{ _logger };
    std::vector< validate::check::diagnostic_frame_signal_t * > const
        diagnostic_frame_signal_checks{ &validate_diagnostic_frame_signal_name,
                                        &validate_diagnostic_frame_signal_offset };

    /* 9.2.5 Schedule table */

    auto validate_schedule_table_entry_command_node =
        validate::schedule_table::entry::command_node_t{ _logger };
    auto validate_schedule_table_entry_command_frame =
        validate::schedule_table::entry::command_frame_t{ _logger };
    auto validate_schedule_table_entry_command_values =
        validate::schedule_table::entry::command_values_t{ _logger };
    auto validate_schedule_table_entry_delay = validate::schedule_table::entry::delay_t{ _logger };
    std::vector< validate::check::schedule_table_entry_t * > const schedule_table_entry_checks{
        &validate_schedule_table_entry_command_node,
        &validate_schedule_table_entry_command_frame,
        &validate_schedule_table_entry_command_values,
        &validate_schedule_table_entry_delay
    };

    /* 9.2.6.1 Signal encoding type definition */

    auto validate_signal_encoding_types  = common::validate::signal::encoding::types_t{ _logger };
    auto validate_signal_encoding_values = common::validate::signal::encoding::values_t{ _logger };
    std::vector< common::validate::check::signal_encoding_t * > const common_signal_encoding_checks{
        &validate_signal_encoding_types, &validate_signal_encoding_values
    };

    auto validate_signal_encoding_value_value =
        common::validate::signal::encoding::value::value_t{ _logger };
    auto validate_signal_encoding_value_text_info =
        common::validate::signal::encoding::value::text_info_t{ _logger };
    std::vector< common::validate::check::signal_encoding_value_t * > const
        common_signal_encoding_value_checks{ &validate_signal_encoding_value_value,
                                             &validate_signal_encoding_value_text_info };

    auto validate_signal_encoding_usage = validate::signal::encoding::usage_t{ _logger };
    auto validate_signal_encoding_size  = validate::signal::encoding::size_t{ _logger };
    std::vector< validate::check::signal_encoding_t * > const signal_encoding_checks{
        &validate_signal_encoding_usage, &validate_signal_encoding_size
    };

    /* 9.2.6.2 Signal representation definition */

    auto validate_signal_representation_encoding =
        validate::signal::representation::encoding_t{ _logger };
    auto validate_signal_representation_signals =
        validate::signal::representation::signals_t{ _logger };
    std::vector< validate::check::signal_representation_t * > const signal_representation_checks{
        &validate_signal_representation_encoding, &validate_signal_representation_signals
    };


    /* 9.2.1 Global definition */

    _logger.push_section("global");

    for (auto const &check : ldf_checks)
    {
        check->run(lin_description_file);
    }

    _logger.pop_section();

    /* 9.2.2 Node definition */

    _logger.push_section("nodes");

    for (auto const &check : nodes_checks)
    {
        check->run(lin_description_file.nodes);
    }

    _logger.pop_section();

    /* 9.2.2.2 Node attributes */

    for (auto const &node_attribute : lin_description_file.node_attributes)
    {
        _logger.push_section("node_attribute", node_attribute.name);

        for (auto const &check : node_attribute_checks)
        {
            check->run(node_attribute);
        }

        _logger.pop_section();
    }

    /* 9.2.2.3 Node composition definition */

    for (auto const &configuration : lin_description_file.node_compositions)
    {
        _logger.push_section("configuration", configuration.name);

        for (auto const &check : node_composition_configuration_checks)
        {
            check->run(configuration);
        }

        for (auto const &composite_node : configuration.composites)
        {
            _logger.push_section("composite", composite_node.name);

            for (auto const &check : node_composition_configuration_composite_checks)
            {
                check->run(lin_description_file.nodes, composite_node);
            }

            _logger.pop_section();
        }

        _logger.pop_section();
    }

    /* 9.2.3.1 Standard signals */

    for (auto const &standard_signal : lin_description_file.standard_signals)
    {
        _logger.push_section("standard_signal", standard_signal.name);

        for (auto const &check : standard_signal_checks)
        {
            check->run(lin_description_file.nodes, standard_signal);
        }

        _logger.pop_section();
    }

    /* 9.2.3.2 Diagnostic signals */

    for (auto const &diagnostic_signal : lin_description_file.diagnostic_signals)
    {
        _logger.push_section("diagnostic_signal", diagnostic_signal.name);

        for (auto const &check : diagnostic_signal_checks)
        {
            check->run(diagnostic_signal);
        }

        _logger.pop_section();
    }

    /* 9.2.3.3 Signal groups */

    for (auto const &signal_group : lin_description_file.signal_groups)
    {
        _logger.push_section("signal_group", signal_group.name);

        for (auto const &check : signal_group_checks)
        {
            check->run(lin_description_file.standard_signals, signal_group);
        }

        _logger.pop_section();
    }

    /* 9.2.4.1 Unconditional frames */

    for (auto const &unconditional_frame : lin_description_file.unconditional_frames)
    {
        _logger.push_section("unconditional_frame", unconditional_frame.name);

        for (auto const &check : unconditional_frame_checks)
        {
            check->run(
                lin_description_file.nodes,
                lin_description_file.standard_signals,
                unconditional_frame);
        }

        for (auto const &unconditional_frame_signal : unconditional_frame.signals)
        {
            _logger.push_section("signal", unconditional_frame_signal.name);

            for (auto const &check : unconditional_frame_signal_checks)
            {
                check->run(lin_description_file.standard_signals, unconditional_frame_signal);
            }

            _logger.pop_section();
        }

        _logger.pop_section();
    }

    /* 9.2.4.2 Sporadic frames */

    for (auto const &sporadic_frame : lin_description_file.sporadic_frames)
    {
        _logger.push_section("sporadic_frame", sporadic_frame.name);

        for (auto const &check : sporadic_frame_checks)
        {
            check->run(lin_description_file.unconditional_frames, sporadic_frame);
        }

        _logger.pop_section();
    }

    /* 9.2.4.3 Event triggered frames */

    for (auto const &event_triggered_frame : lin_description_file.event_triggered_frames)
    {
        _logger.push_section("event_triggered_frame", event_triggered_frame.name);

        for (auto const &check : event_triggered_frame_checks)
        {
            check->run(
                lin_description_file.schedule_tables,
                lin_description_file.unconditional_frames,
                event_triggered_frame);
        }

        _logger.pop_section();
    }

    /* 9.2.4.4 Diagnostic frames */

    for (auto const &diagnostic_frame : lin_description_file.diagnostic_frames)
    {
        _logger.push_section("diagnostic_frame", diagnostic_frame.name);

        for (auto const &check : diagnostic_frame_checks)
        {
            check->run(diagnostic_frame);
        }

        for (auto const &diagnostic_frame_signal : diagnostic_frame.signals)
        {
            _logger.push_section("signal", diagnostic_frame_signal.name);

            for (auto const &check : diagnostic_frame_signal_checks)
            {
                check->run(lin_description_file.diagnostic_signals, diagnostic_frame_signal);
            }

            _logger.pop_section();
        }

        _logger.pop_section();
    }

    /* 9.2.5 Schedule table */

    for (auto const &schedul_table : lin_description_file.schedule_tables)
    {
        _logger.push_section("schedul_table", schedul_table.name);

        int index{ 0 };

        for (auto const &entry : schedul_table.entries)
        {
            _logger.push_section("entry", std::to_string(index++));

            for (auto const &check : schedule_table_entry_checks)
            {
                check->run(
                    lin_description_file.nodes,
                    lin_description_file.unconditional_frames,
                    lin_description_file.sporadic_frames,
                    lin_description_file.event_triggered_frames,
                    entry);
            }

            _logger.pop_section();
        }

        _logger.pop_section();
    }

    /* 9.2.6.1 Signal encoding type definition */

    for (auto const &signal_encoding : lin_description_file.signal_encodings)
    {
        _logger.push_section("signal_encoding", signal_encoding.name);

        for (auto const &check : common_signal_encoding_checks)
        {
            check->run(signal_encoding);
        }

        for (auto const &check : signal_encoding_checks)
        {
            check->run(
                lin_description_file.standard_signals,
                lin_description_file.signal_representations,
                signal_encoding);
        }

        int index{ 0 };

        for (auto const &value : signal_encoding.values)
        {
            _logger.push_section("value", std::to_string(index++));

            for (auto const &check : common_signal_encoding_value_checks)
            {
                check->run(value);
            }

            _logger.pop_section();
        }

        _logger.pop_section();
    }

    /* 9.2.6.2 Signal representation definition */

    for (auto const &signal_representation : lin_description_file.signal_representations)
    {
        _logger.push_section("signal_representation", signal_representation.name);

        for (auto const &check : signal_representation_checks)
        {
            check->run(
                lin_description_file.signal_encodings,
                lin_description_file.standard_signals,
                signal_representation);
        }

        _logger.pop_section();
    }
}
// NOLINTEND(readability-function-cognitive-complexity)

}    // namespace lin::ldf::validate
