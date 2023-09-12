#include <lin/type_io/common/signal_encoding_type.hpp>
#include <lin/type_io/ldf/signal.hpp>

/* 9.2.3 Signal definition */

namespace lin::type::ldf::signal {

/* 9.2.3.1 Standard signals */

namespace standard_signal {

//std::ostream &operator<<(std::ostream &out, const init_value_scalar_t &init_value_scalar)
//{
//    out << std::hex << init_value_scalar;
//    return out;
//}

std::ostream &operator<<(std::ostream &out, init_value_array_t const &init_value_array)
{
    out << "{ " << std::hex;
    for (auto iter = init_value_array.cbegin(); iter != init_value_array.cend(); ++iter)
    {
        out << "0x" << *iter;
        if (iter != init_value_array.end() - 1)
        {
            out << ", ";
        }
    }
    out << " }" << std::dec;
    return out;
}

std::ostream &operator<<(std::ostream &out, init_value_t const &init_value)
{
    std::visit([&out](auto &&arg) { out << arg; }, init_value);
    return out;
}

}    // namespace standard_signal

std::ostream &operator<<(std::ostream &out, standard_signal_t const &standard_signal)
{
    using namespace standard_signal;

    out << standard_signal.signal_name << ": " << (long int)standard_signal.signal_size << ", "
        << standard_signal.init_value << ", " << standard_signal.published_by;
    for (auto const &subscriber : standard_signal.subscribed_by)
    {
        out << ", " << subscriber;
    }
    out << ";" << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, standard_signals_t const &standard_signals)
{
    out << "Signals {" << std::endl;
    for (auto const &standard_signal : standard_signals)
    {
        out << "    " << standard_signal;
    }
    out << "}" << std::endl;
    return out;
}

/* 9.2.3.2 Diagnostic signals */

std::ostream &operator<<(std::ostream &out, diagnostic_signal_t const &diagnostic_signal)
{
    using namespace standard_signal;

    out << diagnostic_signal.signal_name << ": " << diagnostic_signal.signal_size << ", "
        << diagnostic_signal.init_value << ";" << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, diagnostic_signals_t const &diagnostic_signals)
{
    out << "Diagnostic_signals {" << std::endl;
    for (auto const &diagnostic_signal : diagnostic_signals)
    {
        out << "    " << diagnostic_signal;
    }
    out << "}" << std::endl;
    return out;
}

/* 9.2.3.3 Signal groups */

namespace signal_group {

std::ostream &operator<<(std::ostream &out, group_entry_t const &group_entry)
{
    out << group_entry.signal_name << ", " << group_entry.group_offset << ";" << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, group_entries_t const &group_entries)
{
    for (auto const &group_entry : group_entries)
    {
        out << "        " << group_entry;
    }
    return out;
}

}    // namespace signal_group

std::ostream &operator<<(std::ostream &out, signal_group_t const &signal_group)
{
    out << "    " << signal_group.signal_group_name << ": " << signal_group.group_size << " {"
        << std::endl;
    out << signal_group.group_entries;
    out << "    }" << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, signal_groups_t const &signal_groups)
{
    out << "Signal_groups {" << std::endl;
    for (auto const &signal_group : signal_groups)
    {
        out << signal_group;
    }
    out << "}" << std::endl;
    return out;
}

/* 9.2.6.1 Signal encoding type definition */

std::ostream &operator<<(std::ostream &out, signal_encoding_type_t const &signal_encoding_type)
{
    using namespace common::signal_encoding_type;

    out << "    " << signal_encoding_type.signal_encoding_type_name << " {" << std::endl;
    for (auto const &value : signal_encoding_type.values)
    {
        out << "        " << value;
    }
    out << "    }" << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, signal_encoding_types_t const &signal_encoding_types)
{
    out << "Signal_encoding_types {" << std::endl;
    for (auto const &signal_encoding_type : signal_encoding_types)
    {
        out << signal_encoding_type;
    }
    out << "}" << std::endl;
    return out;
}

/* 9.2.6.2 Signal representation definition */

std::ostream &operator<<(std::ostream &out, signal_representation_t const &signal_representation)
{
    out << signal_representation.signal_encoding_type_name << ": ";
    for (auto iter = signal_representation.signal_names.begin();
         iter != signal_representation.signal_names.end();
         ++iter)
    {
        out << *iter;
        if (iter != signal_representation.signal_names.end() - 1)
        {
            out << ", ";
        }
    }
    out << ";" << std::endl;
    return out;
}

std::ostream &operator<<(std::ostream &out, signal_representations_t const &signal_representations)
{
    out << "Signal_representation {" << std::endl;
    for (auto const &signal_representation : signal_representations)
    {
        out << "    " << signal_representation;
    }
    out << "}" << std::endl;
    return out;
}

}    // namespace lin::type::ldf::signal
