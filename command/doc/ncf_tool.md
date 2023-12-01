# NAME

ncf_tool - Node capability file parser, generator and validator

# SYNOPSIS

`ncf_tool` [`--help`] [`--verbose`] [`--version`] *command* [*options*]... *ncf_file*

# DESCRIPTION

**NCF tool** parses the given *ncf_file* according to LIN Specification 2.2A.

The tool provides multiple *command*s to run different functions on the parsed data.

# Global options

`-h, --help`

: Shows the help message.

`-v`, `--verbose`

: Give a more verbose output.

`--version`

: Print version line and exit.

# The command **prettify**

`ncf_tool` `prettify` generates a well-formed and readable node capability file.

## Options

`-i`, `--indent`
: Number of spaces sections are indented. Default value is 4 spaces.

`o`, `--output`
: Output file the prettified content is saved to.

# The command **validate**

`ncf_tool` `validate` runs multiple logical tests over the parsed node capability data. The output provides warnings, errors and some help, to fix possible problems.

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

ldf_tool(1)
