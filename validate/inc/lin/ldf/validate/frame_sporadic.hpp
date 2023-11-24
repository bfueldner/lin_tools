#pragma once

#include <lin/ldf/validate/check.hpp>

/* 9.2.4.2 Sporadic frames */

namespace lin::ldf::validate::frame::sporadic {

class frames_t:
    public common::validate::check_names_t<
        ldf::frame::sporadic_t,
        &ldf::frame::sporadic_t::frames,
        0,
        ldf::frame::unconditionals_t >
{
  public:
    explicit frames_t(common::validate::logger_t &logger):
        common::validate::check_names_t<
            ldf::frame::sporadic_t,
            &ldf::frame::sporadic_t::frames,
            0,
            ldf::frame::unconditionals_t >{ logger, "frames" }
    {
    }
};

}    // namespace lin::ldf::validate::frame::sporadic
