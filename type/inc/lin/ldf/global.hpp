#pragma once

#include <lin/common/bnf.hpp>

/* 9.2.1 Global definition */

namespace lin::ldf::global {

/* 9.2.1.1 LIN protocol version number definition */

using lin_protocol_version_t = common::bnf::char_string_t;

/* 9.2.1.2 LIN language version number definition */

using lin_language_version_t = common::bnf::char_string_t;

/* 9.2.1.3 LIN speed definition */

using lin_speed_t = common::bnf::real_or_integer_t;

/* 9.2.1.4 Channel postfix name definition */

/* NOTE: Specification says 'identifier', but this does not make sense. */
using channel_name_t = common::bnf::char_string_t;

}    // namespace lin::ldf::global
