#pragma once

#include <lin/ncf/validate/check.hpp>

/* 8.2 Node capability file definition */

namespace lin::ncf::validate {

/* 8.2.1 Global definition */

namespace node_capability_file {

template < auto ncf::node_capability_file_t::*member_ >
using check_node_capability_file_node_vector_name_t =
    common::validate::check_vector_name_t< ncf::node_capability_file_t, ncf::node_t, member_ >;

class language_version_t:
    public common::validate::check_language_version_t< ncf::node_capability_file_t >
{
  public:
    explicit language_version_t(common::validate::logger_t &logger):
        common::validate::check_language_version_t< ncf::node_capability_file_t >{
            logger,
            "language_version"
        }
    {
    }
};

class node_names_t:
    public check_node_capability_file_node_vector_name_t< &ncf::node_capability_file_t::nodes >
{
  public:
    explicit node_names_t(common::validate::logger_t &logger):
        check_node_capability_file_node_vector_name_t< &ncf::node_capability_file_t::nodes >{
            logger,
            "node_names"
        }
    {
    }
};

}    // namespace node_capability_file

class node_capability_file_t
{
  public:
    explicit node_capability_file_t(common::validate::logger_t &logger):
        _logger{ logger }
    {
    }

    void run(const ncf::node_capability_file_t &node_capability_file) const;

  private:
    common::validate::logger_t
        &_logger;    // NOLINT(cppcoreguidelines-avoid-const-or-ref-data-members)
};

}    // namespace lin::ncf::validate
