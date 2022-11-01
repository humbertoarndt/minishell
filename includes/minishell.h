/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:26:03 by harndt            #+#    #+#             */
/*   Updated: 2022/10/31 23:33:39 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

// =============================================================================
// LOCAL LIBRARIES
// =============================================================================

# include "../libft/libft.h"
# include "defines.h"
# include "structs.h"

// =============================================================================
// EXTERNAL LIBRARIES
// =============================================================================

/* access, chdir, close, dup2, dup, execve, exit, fork, pipe, read, unlink */
# include <unistd.h>
# include <fcntl.h>				/* open */
# include <errno.h>				/* errno, strerror */
# include <stdio.h>				/* printf, perror */
# include <dirent.h>			/* readdir */
# include <signal.h>			/* sigaction, sigemptyset */
# include <sys/types.h>			/* opendir, closedir */
# include <sys/wait.h>			/* wait, waitpid */
# include <sys/stat.h>			/* stat */
# include <readline/readline.h>	/* readline, rl_* */
# include <readline/history.h>	/* readline, add_history, rl_* */

typedef struct sigaction	t_sigaction;

// =============================================================================
// FUNCTIONS
// =============================================================================
// =============================================================================
// prompt
// =============================================================================
int				ft_prompt(t_ms *ms);
// =============================================================================
// INITIALIZERS
// =============================================================================
void			ft_init_ms(t_ms *ms);
void			ft_init_env(t_ms *ms, char *env[]);
// =============================================================================
// TOKENS
// =============================================================================
int				ft_tokenizer(t_ms *ms);
//token list
void			ft_addback_token(t_token **head, t_token *new_token);
t_token			*ft_create_token_node(char *token, t_token_type type);
void			ft_clear_tokens(t_token **token_head);
// quoting tokenizer
t_token			*ft_quoting_tokenizer(t_ms *ms);
t_token_type	ft_found_quoting(char *buffer);
// io file tokenizer
t_token_type	ft_found_redirection(char	*buffer);
t_token			*ft_io_file_tokenizer(t_ms *ms);
// pipe tokenizer
t_token_type	ft_found_pipe(char *buffer);
t_token			*ft_pipe_tokenizer(t_ms *ms);
// heredoc tokenizer
t_token_type	ft_found_heredoc(char *buffer);
t_token			*ft_heredoc_tokenizer(t_ms *ms);
//command tokenizer
t_token			*ft_command_tokenizer(t_ms *ms);
t_token_type	ft_found_command(char *buffer);
// token utils
int				has_closing_char(t_ms *ms, char quote);
char			*ft_create_token_string(t_ms *ms, size_t len);
t_token			*ft_return_simple_token(t_ms *ms, char *token_string,
					t_token_type token_type);
int				ft_advance_ptr_after_white_space(char **buffer);
// =============================================================================
// errors handlers
// =============================================================================
void			ft_perror_formmated(char *message);
int				ft_check_argc_argc(int argc, char *argv[]);
void			print_custom_arg_error(char *arg, char *message);
// =============================================================================
// debug
// =============================================================================
void			ft_print_tokens_list(t_token *token_head);
// =============================================================================
// hash_table
// =============================================================================
void			ft_print_hash_table(t_hash_table *hash_table);
int				ft_delete_hash_item_by_key(t_hash_table *hash_table,
					char *key);
int				ft_update_hash_item(t_hash_table *hash_table, char *key,
					char *value);
void			ft_insert_or_update_hash_item(t_hash_table *hash_table,
					char *key, char *value);
void			ft_print_hash_table(t_hash_table *hash_table);
t_hash_item		*ft_search_item_by_key(t_hash_table *hash_table,char *key);
void			ft_insert_hash_item(t_hash_table *hash_table, char *key,
					char *value);
size_t			ft_count_items_in_bucket(t_hash_item *hash_head);
void			ft_addback_item(t_hash_item **hash_item,
					t_hash_item *new_hash_item);
t_hash_item		*ft_find_last_item(t_hash_item *hash_head);
t_uint			ft_hash(char *key, size_t size);
void			ft_clear_hash_table(t_hash_table *hash_table);
void			ft_clear_hash_item2(t_hash_item **hash_item);
int				ft_delete_hash_item_by_key(t_hash_table *hash_table,
					char *key);
t_hash_table	*ft_create_hash_table(size_t size);
t_hash_item		*ft_create_hash_item(char *key, char *value);
void			ft_create_env(t_ms *ms);
void			ft_print_hash_item(t_hash_item *hash_item);
// =============================================================================
// free
// =============================================================================
void			ft_free_ms(t_ms *ms);
// void			set_signals(void);
#endif