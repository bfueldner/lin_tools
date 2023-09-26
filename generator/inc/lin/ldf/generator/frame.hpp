#pragma once

#include <iostream>

#include <lin/ldf/frame.hpp>

/* 9.2.4 Frame definition */

namespace lin::ldf::frame {

/* 9.2.4.1 Unconditional frames */

namespace unconditional_frame {

std::ostream &operator<<(std::ostream &out, frame_entry_t const &frame_entry);
std::ostream &operator<<(std::ostream &out, frame_entries_t const &frame_entries);

}    // namespace unconditional_frame

std::ostream &operator<<(std::ostream &out, unconditional_frame_t const &unconditional_frame);
std::ostream &operator<<(std::ostream &out, unconditional_frames_t const &unconditional_frames);

/* 9.2.4.2 Sporadic frames */

std::ostream &operator<<(std::ostream &out, sporadic_frame_t const &sporadic_frame);
std::ostream &operator<<(std::ostream &out, sporadic_frames_t const &sporadic_frames);

/* 9.2.4.3 Event triggered frames */

std::ostream &operator<<(std::ostream &out, event_triggered_frame_t const &event_triggered_frame);
std::ostream &operator<<(std::ostream &out, event_triggered_frames_t const &event_triggered_frames);

/* 9.2.4.4 Diagnostic frames */

std::ostream &operator<<(std::ostream &out, diagnostic_frame_t const &diagnostic_frame);
std::ostream &operator<<(std::ostream &out, diagnostic_frames_t const &diagnostic_frames);

}    // namespace lin::ldf::frame
