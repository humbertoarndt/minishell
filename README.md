# minishell

This is project ask us to code our own shell. A program capable of parsing a prompt and launching executables with arguments, along with a few built-in function.

## How to use it

By using `make` the `minishell` executable is created.

```sh
git clone https://github.com/humbertoarndt/minishell.git
cd minishell
make
./minishell
```

## Available options

 * Run of executables from absolute, relative or environment PATH (`/bin/ls` or `ls`);
 * Redirects with `> >> << < |`;
 * Enviroment variables are handled, like `$HOME` and `$?`;
 * The following signals are implemented as `Ctrl-C` to interrupt, `Ctrl-\`to do nothing and `Ctrl-D`to throw an EOF;
 * The above built-ins were coded:
    * `echo` with the `-n` option;
    * `pwd`;
    * `cd`;
    * `env`;
    * `export`;
    * `unset`;
    * `exit`;

This ptoject was done as a team, so many thanks to my partner [bbonaldi](https://github.com/brunobonaldi94), responsible for doing parsing, argument chcking, redirection, piping and enviroment variables.