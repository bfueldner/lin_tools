# LIN 2.2 tools

![License](https://build.fueldner.net/badges/opensource_lin_tools.svg?type=license&branch=main)
[![Build state](https://build.fueldner.net/badges/opensource_lin_tools.svg?branch=main)](https://build.fueldner.net/#/builders/opensource_lin_tools)
![Warnings](https://build.fueldner.net/badges/opensource_lin_tools.svg?type=warnings&branch=main)
![Tests](https://build.fueldner.net/badges/opensource_lin_tools.svg?type=tests&branch=main)
![Coverage](https://build.fueldner.net/badges/opensource_lin_tools.svg?type=coverage&branch=main)

LIN 2.2 node capability file (NCF) and LIN description file (LDF) parser written in `boost::spirit:x3` and generator using std::stream. NCF and LDF validation by command-line tool supported.

## Command-line

Usage of the parsing, generating and validation libraries is given by command-line tools.

### LDF-Tool

LIN description file parser, generator and validator command-line tool.

    Usage:
      ldf_tool \<command\> [options] \<input-file\>
    
    Commands:
      prettify              Prettify file
      validate              Validate file
    
    Generic options:
      -h [ --help ]         Show help text
      -v [ --verbose ]      Verbose output
      --version             Show program version 
    
    To get help for a specific command:
      ldf_tool <command> --help

For more information see [ldf_tool manual](command/doc/ldf_tool.md).

### NCF-Tool

Node capability file parser, generator and validator command-line tool.
    
    Usage:
      ncf_tool <command> [options] <input-file>
    
    Commands:
      prettify              Prettify file
      validate              Validate file
    
    Generic options:
      -h [ --help ]         Show help text
      -v [ --verbose ]      Verbose output
      --version             Show program version
    
    To get help for a specific command:
      ncf_tool <command> --help

For more information see [ncf_tool manual](command/doc/ncf_tool.md).

## Installation

    $ meson setup --buildtype release build
    $ meson install -C build --strip
    
To update shared library and manpage cache run:

    $ sudo ldconfig
    $ sudo mandb

---

> NON NOBIS DOMINE, NON NOBIS, SED NOMINI TUO DA GLORIAM
