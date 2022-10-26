# Minishell | 42 São Paulo

## Table of Contents
* [1 - Introduction](#introduction)
	* [1.1 - What the Shell](#what-the-shell)
	* [1.2 - How the Shell Works](#)
* [Allowed Functions](#allowed-function)


## 1 - Introduction

This project is about recreating your very own (mini)shell, using bash as a reference. This is my first group project at [42 São Paulo](https://www.42sp.org.br/), and my partner in crime is the great [@bbonaldi](https://github.com/brunobonaldi94).

### 1.1 - What the Shell

Following the Oxford English's dictionary, `shell` (/SHel/) is <b><i>"The hard protective outer case of a mollusk or crustacean"</i></b>. When you aplly this logic into computer science it makes total sense. In that case computer shells are a protective way to guard your operational system, and allow the user to interact with it trough an interface without direct access to its kernel.
Besides being a communication tool the shell does not need to do much, it's only need to know where to find and how the execute what the user requests, and then send it to the OS.

### Allowed Functions

| Function | Lib | Prototype | Description |
| --- | --- | --- | --- |
| `readline()` | <stdio.h> <readline/readline.h> <readline/history.h> | `char *readline (const char *prompt);` | This function reads a line from the terminal and returns it, while waiting for input allows the user to edit the line. This is the function to be used in order to show the `prompt` in the program terminal. |
| `rl_clear_history()` |
| `rl_on_new_line()` |
| `rl_replace_line()` |
| `rl_redisplay()` |
| `add_history()` |
| `printf()` |
| `malloc()` |
| `free()` |
| `write()` |
| `access()` |
| `open()` |
| `read()` |
| `close()` |
| `fork()` |
| `wait()` |
| `waitpid()` |
| `wait3()` |
| `wait4()` |
| `signal()` |
| `sigaction()` |
| `sigemptyset()` |
| `sigaddset()` |
| `kill()` |
| `exit()` |
| `getcwd()` |
| `chdir()` |
| `stat()` |
| `lstat()` |
| `fstat()` |
| `unlink()` |
| `execve()` |
| `dup()` |
| `dup2()` |
| `pipe()` |
| `opendir()` |
| `readdir()` |
| `closedir()` |
| `strerror()` |
| `perror()` |
| `isatty()` |
| `ttyname()` |
| `ttyslot()` |
| `ioctl()` |
| `etenv()` |
| `tcsetattr()` |
| `tcgetattr()` |
| `tgetent()` |
| `tgetflag()` |
| `tgetnum()` |
| `tgetstr()` |
| `tgoto()` |
| `tputs()` |