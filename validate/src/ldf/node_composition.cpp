#include <map>
#include <vector>

#include <lin/ldf/node_composition.hpp>
#include <lin/ldf/nodes.hpp>
#include <lin/ldf/validate/node_composition.hpp>

namespace lin::ldf::validate::node::composition::configuration {

void composite_nodes_t::run(
    const ldf::nodes_t &nodes,
    const ldf::node::composition::configuration::composite_t &composite) const
{
    if (composite.nodes.empty())
    {
        _log_warning("Empty");
        return;
    }

    std::map< std::string, unsigned int > present{};

    for (auto const &slave : nodes.slaves)
    {
        present[slave] = 0;
    }

    std::vector< std::string > missing{};

    for (auto const &name : composite.nodes)
    {
        if (present.contains(name))
        {
            present[name]++;
        }
        else
        {
            missing.emplace_back(name);
        }
    }

    if (!missing.empty())
    {
        _log_error("Not defined", _to_string(missing));
        return;
    }

    std::vector< std::string > duplicate{};

    for (auto const &entry : present)
    {
        if (entry.second > 1)
        {
            duplicate.push_back(entry.first);
        }
    }

    if (!duplicate.empty())
    {
        _log_error("Duplicate entry", _to_string(duplicate));
        return;
    }

    _log_ok();
}

}    // namespace lin::ldf::validate::node::composition::configuration
