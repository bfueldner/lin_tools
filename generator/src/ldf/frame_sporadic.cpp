#include <ostream>

#include <lin/common/generator/indention.hpp>
#include <lin/ldf/frame_sporadic.hpp>
#include <lin/ldf/generator/frame_sporadic.hpp>

/* 9.2.4.2 Sporadic frames */

namespace lin::ldf::frame {

std::ostream &operator<<(std::ostream &out, sporadic_t const &sporadic)
{
    out << common::indention_t::indent << sporadic.name << ": ";
    for (auto iter = sporadic.frames.cbegin(); iter != sporadic.frames.cend(); ++iter)
    {
        out << *iter;
        if (iter != sporadic.frames.cend() - 1)
        {
            out << ", ";
        }
    }
    out << ";\n";
    return out;
}

std::ostream &operator<<(std::ostream &out, sporadics_t const &sporadics)
{
    out << common::indention_t::push << "Sporadic_frames {\n";
    for (auto const &sporadic : sporadics)
    {
        out << sporadic;
    }
    out << common::indention_t::pop << "}\n";
    return out;
}

}    // namespace lin::ldf::frame
