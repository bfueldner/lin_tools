#include <iomanip>
#include <ios>
#include <ostream>

#include <lin/common/generator/indention.hpp>
#include <lin/ldf/frame_event_triggered.hpp>
#include <lin/ldf/generator/frame_event_triggered.hpp>

/* 9.2.4.3 Event triggered frames */

namespace lin::ldf::frame {

std::ostream &operator<<(std::ostream &out, event_triggered_t const &event_triggered)
{
    out << common::indention_t::indent << event_triggered.name << ": "
        << event_triggered.schedule_table << ", " << std::hex << "0x" << std::setw(2)
        << std::setfill('0') << event_triggered.id << std::dec;
    for (auto const &frame : event_triggered.frames)
    {
        out << ", " << frame;
    }
    out << ";\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, event_triggereds_t const &event_triggereds)
{
    out << common::indention_t::push << "Event_triggered_frames {\n";
    for (auto const &event_triggered : event_triggereds)
    {
        out << event_triggered;
    }
    out << common::indention_t::pop << "}\n";
    return out;
}

}    // namespace lin::ldf::frame
