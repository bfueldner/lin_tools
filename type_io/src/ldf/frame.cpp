#include <iomanip>

#include <lin/type_io/ldf/frame.hpp>

/* 9.2.4 Frame definition */

namespace lin::type::ldf::frame {

/* 9.2.4.1 Unconditional frames */

namespace unconditional_frame {

std::ostream &operator<<(std::ostream &out, frame_entry_t const &frame_entry)
{
    out << frame_entry.signal_name << ", " << frame_entry.signal_offset << ";" << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, frame_entries_t const &frame_entries)
{
    for (auto const &frame_entry : frame_entries)
    {
        out << std::setw(4) << frame_entry;
    }
    return out;
}

}    // namespace unconditional_frame

std::ostream &operator<<(std::ostream &out, unconditional_frame_t const &unconditional_frame)
{
    out << "    " << unconditional_frame.frame_name << ": " << std::hex << "0x" << std::setw(2)
        << std::setfill('0') << unconditional_frame.frame_id << std::dec << ", "
        << unconditional_frame.published_by << ", " << unconditional_frame.frame_size << " {"
        << std::endl;
    for (auto const &frame_entry : unconditional_frame.frame_entries)
    {
        out << "        " << frame_entry;
    }
    out << "    }" << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, unconditional_frames_t const &unconditional_frames)
{
    out << "Frames {" << std::endl;
    for (auto const &unconditional_frame : unconditional_frames)
    {
        out << unconditional_frame;
    }
    out << "}" << std::endl;
    return out;
}

/* 9.2.4.2 Sporadic frames */

std::ostream &operator<<(std::ostream &out, sporadic_frame_t const &sporadic_frame)
{
    out << sporadic_frame.sporadic_frame_name << ": ";
    for (auto iter = sporadic_frame.frame_names.begin(); iter != sporadic_frame.frame_names.end();
         ++iter)
    {
        out << *iter;
        if (iter != sporadic_frame.frame_names.end() - 1)
        {
            out << ", ";
        }
    }
    out << ";" << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, sporadic_frames_t const &sporadic_frames)
{
    out << "Sporadic_frames {" << std::endl;
    for (auto const &sporadic_frame : sporadic_frames)
    {
        out << "    " << sporadic_frame;
    }
    out << "}" << std::endl;
    return out;
}

/* 9.2.4.3 Event triggered frames */

std::ostream &operator<<(std::ostream &out, event_triggered_frame_t const &event_triggered_frame)
{
    out << event_triggered_frame.event_trig_frm_name << ": "
        << event_triggered_frame.collision_resolving_schedule_table << ", " << std::hex << "0x"
        << std::setw(2) << std::setfill('0') << event_triggered_frame.frame_id << std::dec;
    for (auto const &frame_name : event_triggered_frame.frame_names)
    {
        out << ", " << frame_name;
    }
    out << ";" << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, event_triggered_frames_t const &event_triggered_frames)
{
    out << "Event_triggered_frames {" << std::endl;
    for (auto const &event_triggered_frame : event_triggered_frames)
    {
        out << "    " << event_triggered_frame;
    }
    out << "}" << std::endl;
    return out;
}

/* 9.2.4.4 Diagnostic frames */

std::ostream &operator<<(std::ostream &out, diagnostic_frame_t const &diagnostic_frame)
{
    out << "    " << diagnostic_frame.frame_name << ": " << std::hex << "0x" << std::setw(2)
        << std::setfill('0') << diagnostic_frame.frame_id << std::dec << " {" << std::endl;
    for (auto const &frame_entry : diagnostic_frame.frame_entries)
    {
        out << "        " << frame_entry.signal_name << ", " << frame_entry.signal_offset << ";"
            << std::endl;
    }
    out << "    }" << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, diagnostic_frames_t const &diagnostic_frames)
{
    out << "Diagnostic_frames {" << std::endl;
    for (auto const &diagnostic_frame : diagnostic_frames)
    {
        out << diagnostic_frame;
    }
    out << "}" << std::endl;
    return out;
}

}    // namespace lin::type::ldf::frame
