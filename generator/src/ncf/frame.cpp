#include <ostream>

#include <lin/common/generator/indention.hpp>
#include <lin/ncf/frame.hpp>
#include <lin/ncf/generator/frame.hpp>
#include <lin/ncf/generator/signal.hpp>

/* 8.2.5 Frame definition */

namespace lin::ncf {

/* 8.2.5.1 Frame properties */

namespace frame {

std::ostream &operator<<(std::ostream &out, kind_t const &frame_kind)
{
    switch (frame_kind)
    {
        case kind_t::publish:
        {
            out << "publish";
            break;
        }
        case kind_t::subscribe:
        {
            out << "subscribe";
            break;
        }
    }
    return out;
}

}    // namespace frame

std::ostream &operator<<(std::ostream &out, frame_t const &frame)
{
    out << common::indention_t::indent << common::indention_t::push << frame.kind << " "
        << frame.name << " {\n";
    out << common::indention_t::indent << "length = " << frame.size << ";\n";
    if (frame.min_period)
    {
        out << common::indention_t::indent << "min_period = " << frame.min_period.value()
            << " ms;\n";
    }

    if (frame.max_period)
    {
        out << common::indention_t::indent << "max_period = " << frame.max_period.value()
            << " ms;\n";
    }

    if (frame.event_triggered_frame)
    {
        out << common::indention_t::indent
            << "event_triggered_frame = " << frame.event_triggered_frame.value() << ";\n";
    }
    out << frame.signals;
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}


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
