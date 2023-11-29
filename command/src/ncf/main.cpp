#include <cstdlib>
#include <exception>
#include <iostream>

#include <lin/ncf/command/command_line.hpp>

int main(const int argc, const char **argv)
{
    try
    {
        return lin::ncf::command::command_line::parse(argc, argv) ? EXIT_SUCCESS : EXIT_FAILURE;
    }
    catch (boost::program_options::invalid_option_value &error)
    {
        if (error.get_option_name() == "--command")
        {
            error.set_prefix(0);
        }
        std::cerr << error.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (boost::program_options::error &error)
    {
        std::cerr << error.what() << '\n';
        return EXIT_FAILURE;
    }
    catch (std::exception &error)
    {
        std::cerr << error.what() << '\n';
        return EXIT_FAILURE;
    }
}
