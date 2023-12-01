#pragma once

#include <boost/program_options.hpp>

#include <lin/common/command/type.hpp>
#include <lin/ncf/node_capability_file.hpp>

namespace lin::ncf::command::command_line {

class command_t
{
  public:
    // NOLINTBEGIN(bugprone-easily-swappable-parameters)
    command_t(lin::common::command::type_t command, std::string name, const std::string &caption):
        _command{ command },
        _name{ std::move(name) },
        _options{ caption }
    {
    }
    // NOLINTEND(bugprone-easily-swappable-parameters)
    virtual ~command_t() = default;

    boost::program_options::options_description &options() { return _options; }
    virtual bool run(
        boost::program_options::variables_map &variables_map,
        lin::ncf::node_capability_file_t &node_capability_file,
        bool verbose) = 0;

    friend std::ostream &operator<<(std::ostream &out, const command_t &command)
    {
        out << command._name;
        return out;
    }

  protected:
    // NOLINTBEGIN(cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)
    lin::common::command::type_t _command{};
    std::string _name{};
    boost::program_options::options_description _options{};
    // NOLINTEND(cppcoreguidelines-non-private-member-variables-in-classes,misc-non-private-member-variables-in-classes)
};

class export_t: public command_t
{
  public:
    export_t();

    bool run(
        boost::program_options::variables_map &variables_map,
        lin::ncf::node_capability_file_t &node_capability_file,
        bool verbose) final;
};

class prettify_t: public command_t
{
  public:
    prettify_t();

    bool run(
        boost::program_options::variables_map &variables_map,
        lin::ncf::node_capability_file_t &node_capability_file,
        bool verbose) final;
};

class validate_t: public command_t
{
  public:
    validate_t();

    bool run(
        boost::program_options::variables_map &variables_map,
        lin::ncf::node_capability_file_t &node_capability_file,
        bool verbose) final;
};

bool parse(int argc, const char **argv);

}    // namespace lin::ncf::command::command_line
