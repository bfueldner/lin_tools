#pragma once

#include <lin/ncf/validate/check.hpp>

/* 8.2.2 Node definition */

namespace lin::ncf::validate::node {

template < auto ncf::node_t::*member_ >
using check_node_frame_vector_name_t =
    common::validate::check_vector_name_t< ncf::node_t, ncf::frame_t, member_ >;

template < auto ncf::node_t::*member_ >
using check_node_signal_encoding_vector_name_t =
    common::validate::check_vector_name_t< ncf::node_t, ncf::signal::encoding_t, member_ >;

class frame_names_t: public check_node_frame_vector_name_t< &ncf::node_t::frames >
{
  public:
    explicit frame_names_t(common::validate::logger_t &logger):
        check_node_frame_vector_name_t< &ncf::node_t::frames >{ logger, "frame_names" }
    {
    }
};

class signal_encoding_names_t:
    public check_node_signal_encoding_vector_name_t< &ncf::node_t::signal_encodings >
{
  public:
    explicit signal_encoding_names_t(common::validate::logger_t &logger):
        check_node_signal_encoding_vector_name_t< &ncf::node_t::signal_encodings >{
            logger,
            "signal_encoding_names"
        }
    {
    }
};

}    // namespace lin::ncf::validate::node
