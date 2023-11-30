#include <ios>
#include <istream>
#include <ostream>
#include <string>

#include <lin/common/command/type.hpp>
#include <lin/common/command/type_io.hpp>

namespace lin::common::command {

std::istream &operator>>(std::istream &in, type_t &type)
{
    std::string token;

    in >> token;
    if (token == "validate")
    {
        type = type_t::validate;
    }
    else if (token == "prettify")
    {
        type = type_t::prettify;
    }
    else if (token == "export")
    {
        type = type_t::export_;
    }
    else
    {
        in.setstate(std::ios_base::failbit);
    }
    return in;
}

std::istream &operator>>(std::istream &in, export_type_t &type)
{
    std::string token;

    in >> token;
    if (token == "signal")
    {
        type = export_type_t::signal;
    }
    else if (token == "frame")
    {
        type = export_type_t::frame;
    }
    else
    {
        in.setstate(std::ios_base::failbit);
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, const type_t &type)
{
    switch (type)
    {
        case type_t::validate:
        {
            out << "validate";
            break;
        }

        case type_t::prettify:
        {
            out << "prettify";
            break;
        }

        case type_t::export_:
        {
            out << "export";
            break;
        }

        default:
        {
            out << "<unknown>";
            break;
        }
    }
    return out;
}

std::ostream &operator<<(std::ostream &out, const export_type_t &type)
{
    switch (type)
    {
        case export_type_t::signal:
        {
            out << "signal";
            break;
        }

        case export_type_t::frame:
        {
            out << "frame";
            break;
        }

        default:
        {
            out << "<unknown>";
            break;
        }
    }
    return out;
}

}    // namespace lin::common::command
