#pragma once

#include <lin/ldf/validate/check.hpp>

/* 9.2 LIN description file definition */

namespace lin::ldf::validate {

namespace lin_description_file {

class language_version_t:
    public common::validate::check_language_version_t< ldf::lin_description_file_t >
{
  public:
    explicit language_version_t(common::validate::logger_t &logger):
        common::validate::check_language_version_t< ldf::lin_description_file_t >{
            logger,

            "lin_language_version"
        }
    {
    }
};

class protocol_version_t:
    public common::validate::check_protocol_version_t< ldf::lin_description_file_t >
{
  public:
    explicit protocol_version_t(common::validate::logger_t &logger):
        common::validate::check_protocol_version_t< ldf::lin_description_file_t >{
            logger,

            "lin_protocol_version"
        }
    {
    }
};

class bitrate_t:
    public common::validate::check_min_max_t<
        ldf::lin_description_file_t,
        ldf::bitrate_t,
        &ldf::lin_description_file_t::bitrate,
        ldf::bitrate_t{ 1.0 },
        ldf::bitrate_t{ 20.0 } >
{
  public:
    explicit bitrate_t(common::validate::logger_t &logger):
        common::validate::check_min_max_t<
            ldf::lin_description_file_t,
            ldf::bitrate_t,
            &ldf::lin_description_file_t::bitrate,
            ldf::bitrate_t{ 1.0 },
            ldf::bitrate_t{ 20.0 } >{ logger, "lin_speed" }
    {
    }
};

class channel_name_t: public check::lin_description_file_t
{
  public:
    explicit channel_name_t(common::validate::logger_t &logger):
        check::lin_description_file_t{ logger, "channel_name" }
    {
    }

    void run(const ldf::lin_description_file_t &lin_description_file) const final;
};

class node_attribute_names_t:
    public common::validate::check_vector_name_t<
        ldf::lin_description_file_t,
        ldf::node::attribute_t,
        &ldf::lin_description_file_t::node_attributes >
{
  public:
    explicit node_attribute_names_t(common::validate::logger_t &logger):
        common::validate::check_vector_name_t<
            ldf::lin_description_file_t,
            ldf::node::attribute_t,
            &ldf::lin_description_file_t::node_attributes >{ logger,

                                                             "node_attribute_names" }
    {
    }
};

class node_composition_names_t:
    public common::validate::check_vector_name_t<
        ldf::lin_description_file_t,
        ldf::node::composition::configuration_t,
        &ldf::lin_description_file_t::node_compositions >
{
  public:
    explicit node_composition_names_t(common::validate::logger_t &logger):
        common::validate::check_vector_name_t<
            ldf::lin_description_file_t,
            ldf::node::composition::configuration_t,
            &ldf::lin_description_file_t::node_compositions >{ logger, "node_composition_names" }
    {
    }
};

class standard_signal_names_t:
    public common::validate::check_vector_name_t<
        ldf::lin_description_file_t,
        ldf::signal::standard_t,
        &ldf::lin_description_file_t::standard_signals >
{
  public:
    explicit standard_signal_names_t(common::validate::logger_t &logger):
        common::validate::check_vector_name_t<
            ldf::lin_description_file_t,
            ldf::signal::standard_t,
            &ldf::lin_description_file_t::standard_signals >{ logger, "standard_signal_names" }
    {
    }
};

class diagnostic_signal_names_t:
    public common::validate::check_vector_name_t<
        ldf::lin_description_file_t,
        ldf::signal::diagnostic_t,
        &ldf::lin_description_file_t::diagnostic_signals >
{
  public:
    explicit diagnostic_signal_names_t(common::validate::logger_t &logger):
        common::validate::check_vector_name_t<
            ldf::lin_description_file_t,
            ldf::signal::diagnostic_t,
            &ldf::lin_description_file_t::diagnostic_signals >{ logger, "diagnostic_signal_names" }
    {
    }
};

class signal_group_names_t:
    public common::validate::check_vector_name_t<
        ldf::lin_description_file_t,
        ldf::signal::group_t,
        &ldf::lin_description_file_t::signal_groups >
{
  public:
    explicit signal_group_names_t(common::validate::logger_t &logger):
        common::validate::check_vector_name_t<
            ldf::lin_description_file_t,
            ldf::signal::group_t,
            &ldf::lin_description_file_t::signal_groups >{ logger, "signal_group_names" }
    {
    }
};


class unconditional_frame_names_t:
    public common::validate::check_vector_name_t<
        ldf::lin_description_file_t,
        ldf::frame::unconditional_t,
        &ldf::lin_description_file_t::unconditional_frames >
{
  public:
    explicit unconditional_frame_names_t(common::validate::logger_t &logger):
        common::validate::check_vector_name_t<
            ldf::lin_description_file_t,
            ldf::frame::unconditional_t,
            &ldf::lin_description_file_t::unconditional_frames >{ logger,
                                                                  "unconditional_frame_names" }
    {
    }
};

class sporadic_frame_names_t:
    public common::validate::check_vector_name_t<
        ldf::lin_description_file_t,
        ldf::frame::sporadic_t,
        &ldf::lin_description_file_t::sporadic_frames >
{
  public:
    explicit sporadic_frame_names_t(common::validate::logger_t &logger):
        common::validate::check_vector_name_t<
            ldf::lin_description_file_t,
            ldf::frame::sporadic_t,
            &ldf::lin_description_file_t::sporadic_frames >{ logger, "sporadic_frame_names" }
    {
    }
};

class event_triggered_frame_names_t:
    public common::validate::check_vector_name_t<
        ldf::lin_description_file_t,
        ldf::frame::event_triggered_t,
        &ldf::lin_description_file_t::event_triggered_frames >
{
  public:
    explicit event_triggered_frame_names_t(common::validate::logger_t &logger):
        common::validate::check_vector_name_t<
            ldf::lin_description_file_t,
            ldf::frame::event_triggered_t,
            &ldf::lin_description_file_t::event_triggered_frames >{ logger,
                                                                    "event_triggered_frame_names" }
    {
    }
};

class diagnostic_frame_names_t:
    public common::validate::check_vector_name_t<
        ldf::lin_description_file_t,
        ldf::frame::diagnostic_t,
        &ldf::lin_description_file_t::diagnostic_frames >
{
  public:
    explicit diagnostic_frame_names_t(common::validate::logger_t &logger):
        common::validate::check_vector_name_t<
            ldf::lin_description_file_t,
            ldf::frame::diagnostic_t,
            &ldf::lin_description_file_t::diagnostic_frames >{ logger, "diagnostic_frame_names" }
    {
    }
};

class schedule_table_names_t:
    public common::validate::check_vector_name_t<
        ldf::lin_description_file_t,
        ldf::schedule_table_t,
        &ldf::lin_description_file_t::schedule_tables >

{
  public:
    explicit schedule_table_names_t(common::validate::logger_t &logger):
        common::validate::check_vector_name_t<
            ldf::lin_description_file_t,
            ldf::schedule_table_t,
            &ldf::lin_description_file_t::schedule_tables >{ logger, "schedule_table_names" }
    {
    }
};

class signal_encoding_names_t:
    public common::validate::check_vector_name_t<
        ldf::lin_description_file_t,
        ldf::signal::encoding_t,
        &ldf::lin_description_file_t::signal_encodings >
{
  public:
    explicit signal_encoding_names_t(common::validate::logger_t &logger):
        common::validate::check_vector_name_t<
            ldf::lin_description_file_t,
            ldf::signal::encoding_t,
            &ldf::lin_description_file_t::signal_encodings >{ logger, "signal_encoding_names" }
    {
    }
};

class signal_representation_names_t:
    public common::validate::check_vector_name_t<
        ldf::lin_description_file_t,
        ldf::signal::representation_t,
        &ldf::lin_description_file_t::signal_representations >
{
  public:
    explicit signal_representation_names_t(common::validate::logger_t &logger):
        common::validate::check_vector_name_t<
            ldf::lin_description_file_t,
            ldf::signal::representation_t,
            &ldf::lin_description_file_t::signal_representations >{ logger,
                                                                    "signal_representation_names" }
    {
    }
};

}    // namespace lin_description_file

class lin_description_file_t
{
  public:
    explicit lin_description_file_t(common::validate::logger_t &logger):
        _logger{ logger }
    {
    }

    void run(const ldf::lin_description_file_t &lin_description_file) const;

  private:
    common::validate::logger_t
        &_logger;    // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
};

}    // namespace lin::ldf::validate
