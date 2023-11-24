#include <ios>
#include <istream>
#include <ostream>
#include <string>

#include <lin/ncf/command/type.hpp>
#include <lin/ncf/command/type_io.hpp>

namespace lin::ncf::command {

std::istream &operator>>(std::istream &in, command_t &command)
{
    std::string token;

    in >> token;
    if (token == "validate")
    {
        command = command_t::validate;
    }
    else if (token == "prettify")
    {
        command = command_t::prettify;
    }
    else if (token == "export")
    {
        command = command_t::export_;
    }
    else
    {
        in.setstate(std::ios_base::failbit);
    }
    return in;
}

std::istream &operator>>(std::istream &in, type_t &type)
{
    std::string token;

    in >> token;
    if (token == "signal")
    {
        type = type_t::signal;
    }
    else if (token == "frame")
    {
        type = type_t::frame;
    }
    else
    {
        in.setstate(std::ios_base::failbit);
    }
    return in;
}

std::ostream &operator<<(std::ostream &out, const command_t &command)
{
    switch (command)
    {
        case command_t::validate:
        {
            out << "validate";
            break;
        }

        case command_t::prettify:
        {
            out << "prettify";
            break;
        }

        case command_t::export_:
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

std::ostream &operator<<(std::ostream &out, const type_t &type)
{
    switch (type)
    {
        case type_t::signal:
        {
            out << "signal";
            break;
        }

        case type_t::frame:
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

}    // namespace lin::ncf::command
