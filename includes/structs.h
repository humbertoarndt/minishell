/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 21:28:32 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/10 23:49:45 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

typedef unsigned int t_uint;

typedef struct s_status
{
	pid_t	pid;
	t_bool	paused;
	int		e_code;
}			t_status;

typedef enum e_error_type
{
	QUOTING_ERR = TRUE,
	MISSING_FILE_ERR,
	SYNTAX_ERR
}			t_error_type;

typedef enum e_token_type
{
	NOT_FOUND,
	WORD,
	IO_FILE_TRUNCATE,
	IO_FILE_APPEND,
	IO_FILE_INFILE,
	IO_HEREDOC,
	OR_IF,
	AND_IF,
	VAR_EXPRESSION,
	WILDCARD,
	PIPELINE,
	OPEN_PARENTHESIS,
	CLOSE_PARENTHESIS,
	SINGLE_QUOTE,
	DOUBLE_QUOTE,
}	t_token_type;


typedef enum e_redir_type
{
	NOT_FOUND_REDIR,
	TRUNCATE = 1,
	APPEND,
	INFILE,
	HEREDOC,
} t_redir_type;

typedef struct s_token
{
	char			*token;
	t_token_type	type;
	int				should_expand;
	struct s_token	*prev;
	struct s_token	*next;
}				t_token;

typedef	struct s_hash_item
{
	char				*key;
	char				*value;
	struct s_hash_item	*next;
	struct s_hash_item	*prev;
} t_hash_item;

typedef struct s_hash_table
{
	t_hash_item	**hash_items;
	size_t		count;
	size_t		size;
} t_hash_table;

typedef struct s_env
{
	char			**envp;
	t_hash_table	*var;
	char			**path;
} t_env;

typedef struct t_file
{
	int				fd;
	char			*file;
	t_redir_type	type;
	char			*delimeter;
	
}	t_file;
typedef struct s_cmd
{
	char	*cmd;
	t_list	*argv_list;
	char	**argv;
}	t_cmd;

typedef struct s_executor
{
	char				*operator;
	t_list				*files;
	t_cmd				cmds;
	struct s_executor	*left;
	struct s_executor	*right;
}	t_executor;

typedef struct s_stdin_out
{
	int	stdin;
	int	stdout;
}	t_stdin_out;

typedef struct s_ms
{
	char				*buffer;
	char				*buffer_start;
	t_env				env;
	t_error_type		invalid_program;
	int					exit_code;
	int					fd_pipe[2];
	int					should_write;
	t_stdin_out			stdin_out;
	t_executor			*executor;
	t_list				*pids;
	t_token				*tokens;
}				t_ms;

extern t_status				g_status;
typedef struct sigaction	t_sigaction;

#endif