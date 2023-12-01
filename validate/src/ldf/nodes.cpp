#include <map>
#include <string>
#include <vector>

#include <lin/ldf/nodes.hpp>
#include <lin/ldf/validate/nodes.hpp>

namespace lin::ldf::validate::nodes {

void node_names_t::run(const ldf::nodes_t &nodes) const
{
    std::map< std::string, unsigned int > names{};

    names[nodes.master.name]++;
    for (auto const &slave : nodes.slaves)
    {
        names[slave]++;
    }

    std::vector< std::string > error_names{};
    for (auto const &entry : names)
    {
        if (entry.second > 1)
        {
            error_names.push_back(entry.first);
        }
    }

    if (!error_names.empty())
    {
        _log_error("Names not unique", _to_string(error_names));
        return;
    }

    _log_ok();
}

}    // namespace lin::ldf::validate::nodes
