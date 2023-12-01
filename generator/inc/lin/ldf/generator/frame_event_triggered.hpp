#pragma once

#include <iostream>

#include <lin/ldf/frame_event_triggered.hpp>

/* 9.2.4.3 Event triggered frames */

namespace lin::ldf::frame {

std::ostream &operator<<(std::ostream &out, event_triggered_t const &event_triggered);
std::ostream &operator<<(std::ostream &out, event_triggereds_t const &event_triggereds);

}    // namespace lin::ldf::frame
