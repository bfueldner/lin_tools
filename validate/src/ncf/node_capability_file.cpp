#include <vector>

#include <lin/ncf/node_capability_file.hpp>
#include <lin/ncf/validate/check.hpp>
#include <lin/ncf/validate/diagnostic.hpp>
#include <lin/ncf/validate/frame.hpp>
#include <lin/ncf/validate/general.hpp>
#include <lin/ncf/validate/node.hpp>
#include <lin/ncf/validate/node_capability_file.hpp>
#include <lin/ncf/validate/signal.hpp>
#include <lin/ncf/validate/signal_encoding.hpp>
#include <lin/ncf/validate/status_management.hpp>

/* 8.2 Node capability file definition */

namespace lin::ncf::validate {

void node_capability_file_t::run(const ncf::node_capability_file_t &node_capability_file) const
{
    /* 8.2.1 Global definition */

    auto validate_language_version = validate::node_capability_file::language_version_t{ _logger };
    auto validate_node_names       = validate::node_capability_file::node_names_t{ _logger };
    std::vector< validate::check::node_capability_file_t * > const ncf_checks{
        &validate_language_version,
        &validate_node_names,
    };

    /* 8.2.2 Node definition */

    auto validate_node_frame_names           = validate::node::frame_names_t{ _logger };
    auto validate_node_signal_encoding_names = validate::node::signal_encoding_names_t{ _logger };
    std::vector< validate::check::node_t * > const node_checks{
        &validate_node_frame_names, &validate_node_signal_encoding_names
    };

    /* 8.2.3 General definition */

    auto validate_general_protocol_version = validate::general::protocol_version_t{ _logger };
    auto validate_general_supplier         = validate::general::supplier_t{ _logger };
    auto validate_general_function         = validate::general::function_t{ _logger };
    auto validate_general_variant          = validate::general::variant_t{ _logger };
    auto validate_general_bitrate          = validate::general::bitrate_t{ _logger };
    std::vector< validate::check::general_t * > const general_checks{
        &validate_general_protocol_version,
        &validate_general_supplier,
        &validate_general_function,
        &validate_general_variant,
        &validate_general_bitrate
    };

    /* 8.2.4 Diagnostic definition */

    auto validate_diagnostic_nad          = validate::diagnostic::nad_t{ _logger };
    auto validate_diagnostic_class        = validate::diagnostic::diagnostic_class_t{ _logger };
    auto validate_diagnostic_p2_min       = validate::diagnostic::p2_min_t{ _logger };
    auto validate_diagnostic_st_min       = validate::diagnostic::st_min_t{ _logger };
    auto validate_diagnostic_n_as_timeout = validate::diagnostic::n_as_timeout_t{ _logger };
    auto validate_diagnostic_n_cr_timeout = validate::diagnostic::n_cr_timeout_t{ _logger };
    auto validate_diagnostic_support_sid  = validate::diagnostic::support_sid_t{ _logger };
    auto validate_diagnostic_max_message_length =
        validate::diagnostic::max_message_length_t{ _logger };
    std::vector< validate::check::diagnostic_t * > const diagnostic_checks{
        &validate_diagnostic_nad,          &validate_diagnostic_class,
        &validate_diagnostic_p2_min,       &validate_diagnostic_st_min,
        &validate_diagnostic_n_as_timeout, &validate_diagnostic_n_cr_timeout,
        &validate_diagnostic_support_sid,  &validate_diagnostic_max_message_length
    };

    /* 8.2.5 Frame definition */

    auto validate_frame_length                = validate::frame::length_t{ _logger };
    auto validate_frame_min_period            = validate::frame::min_period_t{ _logger };
    auto validate_frame_max_period            = validate::frame::max_period_t{ _logger };
    auto validate_frame_min_period_max_period = validate::frame::min_period_max_period_t{ _logger };
    auto validate_frame_signal_names          = validate::frame::signal_names_t{ _logger };
    auto validate_frame_signal_sizes          = validate::frame::signal_sizes_t{ _logger };
    auto validate_frame_signal_offsets        = validate::frame::signal_offsets_t{ _logger };
    auto validate_frame_signal_size_offset    = validate::frame::signal_size_offset_t{ _logger };
    std::vector< validate::check::frame_t * > const frame_checks{
        &validate_frame_length,         &validate_frame_min_period,
        &validate_frame_max_period,     &validate_frame_min_period_max_period,
        &validate_frame_signal_names,   &validate_frame_signal_sizes,
        &validate_frame_signal_offsets, &validate_frame_signal_size_offset
    };

    /* 8.2.5.2 Signal definition */

    auto validate_signal_init_value = validate::signal::init_value_t{ _logger };
    auto validate_signal_size       = validate::signal::size_t{ _logger };
    auto validate_signal_offset     = validate::signal::offset_t{ _logger };
    std::vector< validate::check::signal_t * > const signal_checks{
        &validate_signal_init_value,
        &validate_signal_size,
        &validate_signal_offset,
    };

    /* 8.2.5.3 Signal encoding type definition */

    auto validate_signal_encodings_usage = validate::signal_encoding::usage_t{ _logger };

    /* 8.2.6 Status management */

    auto validate_status_management_response_error =
        validate::status_management::response_error_t{ _logger };
    auto validate_status_management_fault_state_signals =
        validate::status_management::fault_state_signals_t{ _logger };
    std::vector< validate::check::status_management_t * > const status_management_checks{
        &validate_status_management_response_error,
        &validate_status_management_fault_state_signals,
    };

    /* 8.2.1 Global definition */

    _logger.push_section("global");
    for (auto const &check : ncf_checks)
    {
        check->run(node_capability_file);
    }
    _logger.pop_section();

    for (auto const &node : node_capability_file.nodes)
    {
        /* 8.2.2 Node definition */

        _logger.push_section("node", node.name);
        for (auto const &check : node_checks)
        {
            check->run(node);
        }

        /* 8.2.3 General definition */

        _logger.push_section("general");
        for (auto const &check : general_checks)
        {
            check->run(node.general);
        }
        _logger.pop_section();

        /* 8.2.4 Diagnostic definition */

        _logger.push_section("diagnostic");
        for (auto const &check : diagnostic_checks)
        {
            check->run(node.diagnostic);
        }
        _logger.pop_section();

        for (auto const &frame : node.frames)
        {
            /* 8.2.5 Frame definition */

            _logger.push_section("frame", frame.name);
            for (auto const &check : frame_checks)
            {
                check->run(frame);
            }

            for (auto const &signal : frame.signals)
            {
                /* 8.2.5.2 Signal definition */

                _logger.push_section("signal", signal.name);
                for (auto const &check : signal_checks)
                {
                    check->run(signal);
                }
                _logger.pop_section();
            }
            _logger.pop_section();
        }

        /* 8.2.5.3 Signal encoding type definition */

        _logger.push_section("signal_encodings");
        validate_signal_encodings_usage.run(node.frames, node.signal_encodings);
        _logger.pop_section();

        /* 8.2.6 Status management */

        _logger.push_section("status_management");
        for (auto const &check : status_management_checks)
        {
            check->run(node.frames, node.status_management);
        }
        _logger.pop_section();

        _logger.pop_section();
    }
}

}    // namespace lin::ncf::validate
