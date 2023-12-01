# NAME

ldf_tool - LIN description file parser, generator and validator

# SYNOPSIS

`ldf_tool` [`--help`] [`--verbose`] [`--version`] *command* [*options*]... *ldf_file*

# DESCRIPTION

**LDF tool** parses the given *ldf_file* according to LIN Specification 2.2A.

The tool provides multiple *command*s to run different functions on the parsed data.

# Global options

`-h, --help`

: Shows the help message.

`-v`, `--verbose`

: Give a more verbose output.

`--version`

: Print version line and exit.

# The command **prettify**

`ldf_tool` `prettify` generates a well-formed and readable LIN description file.

## Options

`-i`, `--indent`
: Number of spaces sections are indented. Default value is 4 spaces.

`o`, `--output`
: Output file the prettified content is saved to.

# The command **validate**

`ldf_tool` `validate` runs multiple logical tests over the parsed LIN description data. The output provides warnings, errors and some help, to fix possible problems.

As default, the lines printed are prefixed with a unicode symbol.

## Options

`-S`, `--no-symbols`
: Don't show unicode symbols on output.

`-w`, `--warnings-as-errors`
: Handle warnings as erros. Otherwise exit status 0 will be returned if no errors are found and only warnings present.

# EXIT STATUS

0
: Parsing and command execution went right.

1
: Wrong command-line arguments, parsing or runtime error.

# AUTHOR

Written by Benjamin Fueldner

# BUGS

<https://code.fueldner.net/opensource/lin_tools/issues>

# COPYRIGHT

Copyright (c) 2023 Benjamin Fueldner <https://fueldner.net>

# SEE ALSO

ncf_tool(1)
