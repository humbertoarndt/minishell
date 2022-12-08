/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   defines.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <humberto.arndt@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:18:19 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/12/07 21:27:13 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEFINES_H
# define DEFINES_H

# define TRUE 1
# define FALSE 0

# define ERROR_CODE 1
# define SUCCESS_CODE 0
# define ERROR_CODE_FUNCTION -1

# define READ_FD 0
# define WRITE_FD 1
# define INFILE 0
# define OUTFILE 1
# define HEREDOC_FILE "/tmp/heredoc_tmp"

# define STDIN 0
# define STDOUT 1
# define STDERROR 2

# define RED "\033[0;31m"
# define BLUE "\033[0;34m"
# define RESET "\033[0m"
# define BLACK "\033[0;30m"
# define GREEN "\033[0;32m"
# define YELLOW "\033[0;33m"

# define DEFAULT_PERMISSION 0000644

# define MINISHELL "minishell: "
# define BASH_START "$ "
# define UNCLOSED_QUOTE "> "
# define HEREDOC_START "> "

# define CHILD_PROCESS 0

# define SPACE_CHAR ' '
# define SINGLE_QUOTE_CHAR '\''
# define DOUBLE_QUOTE_CHAR '"'
# define COMMA_CHAR ':' 
# define EQUAL_CHAR '='
# define EQUAL_STRING "="
# define SLASH_STRING "/"
# define BACKSLASH_CHAR '\\'
# define SENTINEL_CHAR -28
# define PATH "PATH"
# define QUESTION_VAR_EXPRESSION_STRING "$?"

# define PWD "PWD"

# define SYNTAX_ERROR "syntax error near unexpected token `"

# define TO_MANY_ARGUMENTS_ARG "argv"
# define TO_MANY_ARGUMENTS_ERROR_MSG "you cannot run minishell with arguments"
# define COMMAND_NOT_FOUND_ERROR_CODE 127
# define COMMAND_NOT_FOUND_ERROR_MSG "command not found"
# define FILE_NOT_FOUND_ERROR_MSG "no such file or directory!"
# define NUMERIC_ARGUMENT_REQUIRED "numeric argument required"
# define EXIT_TOO_MANY_ARGUMENTS "too many arguments"

# define PIPE_CREATION_ERROR_MSG "Error on creating pipe!"
# define FORK_CREATION_ERROR_MSG "Error on initing fork!"
# define PERMISSION_DENIED_ERROR_CODE 126
# define PERMISSION_DENIED_ERROR_MSG "Permission denied"


# define FILE_DOES_NOT_EXIST -1
# define PERMISSION_NOT_ALLOWED 1
# define PERMISSION_OK 0

# define NOT_FOUND_FD -2

//IO FILE
# define GREAT ">"
# define LESS "<"
# define DGREAT ">>"

// IO HERE DOC
# define DLESS "<<"

// OPERATORS
# define AND_IF_OP "&&"
# define PIPE "|"
# define AND_OR_OP "||"

//VARIABLE EXPRESSION
# define VARIABLE_EXPRESSION "$"
# define QUOTATION_MARKS '?'
//
# define WHITE_SPACE " \t\r\n\v"
# define QUOTING	"\"'"
# define OPERATORS "<>&|"
# define SYMBOLS "<>&|()"

//HASH_TABLE
# define HASH_TABLE_SIZE 907
# define USER_KEY "USER"
# define PWD_KEY "PWD"
# define HOSTNAME_KEY "HOSTNAME"
# define AT "@"
# define COMMA ":"
# define PROMPT_START "$ "

# define MAX_LLONG "9223372036854775807"
# define MAX_LLONG_S "+9223372036854775807"
# define MIN_LLONG "-9223372036854775807"

#endif