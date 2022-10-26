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
| `readline()` | <stdio.h> <readline/readline.h> <readline/history.h> | `char *readline (const char *prompt);` | This function reads a line from the terminal and returns it, while waiting for input allows the user to edit the line. This is the function to be used in order to show the `prompt` in the program terminal. [man](https://www.man7.org/linux/man-pages/man3/readline.3.html) |
| `rl_clear_history()` | <stdio.h> <readline/readline.h> <readline/history.h> | `void rl_clear_history(void)` | Clears the history deleting all of the entries readed by `readline()`. [man](https://tiswww.case.edu/php/chet/readline/readline.html#index-rl_005fclear_005fhistory) |
| `rl_on_new_line()` | <stdio.h> <readline/readline.h> <readline/history.h> | `int rl_on_new_line(void) | Tell the update functions that we have moved ont a new (empty) line, usually after outputting a newline. [man](https://tiswww.case.edu/php/chet/readline/readline.html#index-rl_005fon_005fnew_005fline) |
| `rl_replace_line()` | <stdio.h> <readline/readline.h> <readline/history.h> | `void rl_replace_line (const char *text, int clear_undo)` | Replace the contents of the `buffer` with it's `text`. [man](https://tiswww.case.edu/php/chet/readline/readline.html#index-rl_005freplace_005fline) |
| `rl_redisplay()` | <stdio.h> <readline/readline.h> <readline/history.h> | `void rl_display(void)` | Change what's displayed on the screen to reflect the current contents of `buffer` [man](https://tiswww.case.edu/php/chet/readline/readline.html#index-rl_005fredisplay) |
| `add_history()` | <history.h> | `void add_history (const char *string)` | Adds a new <i>string</i> at the end of the history list readed by `readline()` [man](https://linux.die.net/man/3/history) |
| `printf()` | <stdio.h> | `int printf(const char *restrict format, ...)` | The function produces an output according to it's format and writes it to <b>stdout</b>. [man](https://www.man7.org/linux/man-pages/man3/printf.3.html) |
| `malloc()` | <stdlib.h> | `void *malloc(size_t size)` | Allocates size bytes and returns a pointer to the allocated memory. [man](https://www.man7.org/linux/man-pages/man3/malloc.3.html) |
| `free()` | <stdlib.h> | `void free(void *ptr)` | Frees the memory allocated by `malloc()`, `calloc()` or `realloc()`. [man](https://www.man7.org/linux/man-pages/man3/malloc.3.html) |
| `write()` | <unistd.h> | `ssize_t write(int fd, const void *buf, size_t count)` | Writes up to count bytes from the buffer starting at buf to referred fd. [man](https://man7.org/linux/man-pages/man2/write.2.html) |
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