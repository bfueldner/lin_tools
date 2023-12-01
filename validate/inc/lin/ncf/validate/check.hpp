#pragma once

#include <lin/common/validate/check.hpp>
#include <lin/ncf/frame.hpp>
#include <lin/ncf/node.hpp>
#include <lin/ncf/node_capability_file.hpp>
#include <lin/ncf/signal.hpp>

namespace lin::ncf::validate::check {

using node_capability_file_t = common::validate::check_t< ncf::node_capability_file_t >;
using node_t                 = common::validate::check_t< ncf::node_t >;
using general_t              = common::validate::check_t< ncf::general_t >;
using diagnostic_t           = common::validate::check_t< ncf::diagnostic_t >;
using frame_t                = common::validate::check_t< ncf::frame_t >;
using signal_t               = common::validate::check_t< ncf::signal_t >;
using signal_encodings_t     = common::validate::check_t< ncf::signal::encodings_t, ncf::frames_t >;
using status_management_t    = common::validate::check_t< ncf::status_management_t, ncf::frames_t >;

}    // namespace lin::ncf::validate::check
