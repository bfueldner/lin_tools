#include <iomanip>
#include <ios>
#include <ostream>

#include <lin/ldf/frame.hpp>

#include <lin/common/generator/indention.hpp>
#include <lin/ldf/generator/frame.hpp>

/* 9.2.4 Frame definition */

namespace lin::ldf::frame {

/* 9.2.4.1 Unconditional frames */

namespace unconditional_frame {

std::ostream &operator<<(std::ostream &out, frame_entry_t const &frame_entry)
{
    out << common::indention_t::indent << frame_entry.signal_name << ", "
        << frame_entry.signal_offset << ";\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, frame_entries_t const &frame_entries)
{
    for (auto const &frame_entry : frame_entries)
    {
        out << frame_entry;
    }
    return out;
}

}    // namespace unconditional_frame

std::ostream &operator<<(std::ostream &out, unconditional_frame_t const &unconditional_frame)
{
    out << common::indention_t::indent << common::indention_t::push
        << unconditional_frame.frame_name << ": " << std::hex << "0x" << std::setw(2)
        << std::setfill('0') << unconditional_frame.frame_id << std::dec << ", "
        << unconditional_frame.published_by << ", " << unconditional_frame.frame_size << " {\n";
    for (auto const &frame_entry : unconditional_frame.frame_entries)
    {
        out << frame_entry;
    }
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, unconditional_frames_t const &unconditional_frames)
{
    out << common::indention_t::push << "Frames {\n";
    for (auto const &unconditional_frame : unconditional_frames)
    {
        out << unconditional_frame;
    }
    out << common::indention_t::pop << "}\n";
    return out;
}

/* 9.2.4.2 Sporadic frames */

std::ostream &operator<<(std::ostream &out, sporadic_frame_t const &sporadic_frame)
{
    out << common::indention_t::indent << sporadic_frame.sporadic_frame_name << ": ";
    for (auto iter = sporadic_frame.frame_names.cbegin(); iter != sporadic_frame.frame_names.cend();
         ++iter)
    {
        out << *iter;
        if (iter != sporadic_frame.frame_names.cend() - 1)
        {
            out << ", ";
        }
    }
    out << ";\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, sporadic_frames_t const &sporadic_frames)
{
    out << common::indention_t::push << "Sporadic_frames {\n";
    for (auto const &sporadic_frame : sporadic_frames)
    {
        out << sporadic_frame;
    }
    out << common::indention_t::pop << "}\n";
    return out;
}

/* 9.2.4.3 Event triggered frames */

std::ostream &operator<<(std::ostream &out, event_triggered_frame_t const &event_triggered_frame)
{
    out << common::indention_t::indent << event_triggered_frame.event_trig_frm_name << ": "
        << event_triggered_frame.collision_resolving_schedule_table << ", " << std::hex << "0x"
        << std::setw(2) << std::setfill('0') << event_triggered_frame.frame_id << std::dec;
    for (auto const &frame_name : event_triggered_frame.frame_names)
    {
        out << ", " << frame_name;
    }
    out << ";\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, event_triggered_frames_t const &event_triggered_frames)
{
    out << common::indention_t::push << "Event_triggered_frames {\n";
    for (auto const &event_triggered_frame : event_triggered_frames)
    {
        out << event_triggered_frame;
    }
    out << common::indention_t::pop << "}\n";
    return out;
}

/* 9.2.4.4 Diagnostic frames */

std::ostream &operator<<(std::ostream &out, diagnostic_frame_t const &diagnostic_frame)
{
    out << common::indention_t::indent << common::indention_t::push << diagnostic_frame.frame_name
        << ": " << std::hex << "0x" << std::setw(2) << std::setfill('0')
        << diagnostic_frame.frame_id << std::dec << " {\n";
    for (auto const &frame_entry : diagnostic_frame.frame_entries)
    {
        out << common::indention_t::indent << frame_entry.signal_name << ", "
            << frame_entry.signal_offset << ";\n";
    }
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, diagnostic_frames_t const &diagnostic_frames)
{
    out << common::indention_t::push << "Diagnostic_frames {\n";
    for (auto const &diagnostic_frame : diagnostic_frames)
    {
        out << diagnostic_frame;
    }
    out << common::indention_t::pop << "}\n";
    return out;
}

}    // namespace lin::ldf::frame
