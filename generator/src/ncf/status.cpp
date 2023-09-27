#include <ostream>

#include <lin/ncf/status.hpp>

#include <lin/common/generator/indention.hpp>
#include <lin/ncf/generator/status.hpp>

namespace lin::ncf {

/* 8.2.6 Status management */

std::ostream &operator<<(std::ostream &out, status_t const &status)
{
    out << common::indention_t::indent << common::indention_t::push << "status_management {\n";
    out << common::indention_t::indent << "response_error = " << status.response_error << ";\n";
    if (!status.fault_state_signals.empty())
    {
        out << common::indention_t::indent << "fault_state_signals = ";
        for (auto iter = status.fault_state_signals.begin();
             iter != status.fault_state_signals.end();
             ++iter)
        {
            out << *iter;
            if (iter != status.fault_state_signals.end() - 1)
            {
                out << ", ";
            }
        }
        out << ";\n";
    }
    out << common::indention_t::pop << common::indention_t::indent << "}\n";
    return out;
}

}    // namespace lin::ncf
