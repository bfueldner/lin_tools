#include <ostream>

#include <lin/ncf/frame.hpp>

#include <lin/common/generator/indention.hpp>
#include <lin/ncf/generator/signal.hpp>

#include <lin/ncf/generator/frame.hpp>

namespace lin::ncf {

/* 8.2.5.1 Frame properties */

std::ostream &operator<<(std::ostream &out, frame_properties_t const &frame_properties)
{
    out << common::indention_t::indent << "length = " << frame_properties.length << ";\n";
    if (frame_properties.min_period)
    {
        out << common::indention_t::indent << "min_period = " << frame_properties.min_period.value()
            << " ms;\n";
    }

    if (frame_properties.max_period)
    {
        out << common::indention_t::indent << "max_period = " << frame_properties.max_period.value()
            << " ms;\n";
    }

    if (frame_properties.event_triggered_frame)
    {
        out << common::indention_t::indent
            << "event_triggered_frame = " << frame_properties.event_triggered_frame.value()
            << ";\n";
    }
    return out;
}

/* 8.2.5 Frame definition */

namespace frame {

std::ostream &operator<<(std::ostream &out, frame_kind_t const &frame_kind)
{
    switch (frame_kind)
    {
        case frame_kind_t::publish:
        {
            out << "publish";
            break;
        }
        case frame_kind_t::subscribe:
        {
            out << "subscribe";
            break;
        }
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, single_frame_t const &single_frame)
{
    out << common::indention_t::indent << common::indention_t::push << single_frame.frame_kind
        << " " << single_frame.frame_name << " {\n";
    out << single_frame.frame_properties;
    out << single_frame.signal_definition;
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

}    // namespace frame

std::ostream &operator<<(std::ostream &out, frames_t const &frames)
{
    out << common::indention_t::indent << common::indention_t::push << "frames {\n";
    for (auto const &frame : frames)
    {
        out << frame;
    }
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

}    // namespace lin::ncf
