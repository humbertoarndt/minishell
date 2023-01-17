/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:32:05 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/16 21:51:14 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_perror_formmated(char *message)
{
	char	*message_concat_minishell;

	message_concat_minishell = ft_strjoin(MINISHELL, message);
	perror(message_concat_minishell);
	free(message_concat_minishell);
}

char	*ft_syntax_error_message(char *tok)
{
	char	*token;
	char	*syntax_error;
	char	*syntax_error_quoted;

	if (!*tok)
		token = "newline";
	else
		token = tok;
	syntax_error = ft_strjoin(SYNTAX_ERROR, token);
	syntax_error_quoted = ft_strjoin(syntax_error, "'");
	ft_free_ptr((void **)&syntax_error);
	return (syntax_error_quoted);
}

void	print_custom_arg_error(char *arg, char *message)
{
	int		fd_std_out;
	char	*concat_minishell_with_arg;

	if (arg != NULL)
		concat_minishell_with_arg = ft_strjoin(MINISHELL, arg);
	else
		concat_minishell_with_arg = ft_strdup("minishell");
	fd_std_out = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf(RED"%s: %s\n"RESET, concat_minishell_with_arg, message);
	dup2(fd_std_out, STDOUT_FILENO);
	ft_free_ptr((void **)&(concat_minishell_with_arg));
	close(fd_std_out);
}

void	print_custom_arg_error2(char *argv[2], char *message)
{
	int		fd_std_out;
	char	*concat_minishell_with_arg;
	char	*concat_argv;

	concat_argv = ft_strjoin(argv[0], argv[1]);
	if (concat_argv != NULL)
		concat_minishell_with_arg = ft_strjoin(MINISHELL, concat_argv);
	else
		concat_minishell_with_arg = ft_strdup("minishell");
	fd_std_out = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf(RED"%s: %s\n"RESET, concat_minishell_with_arg, message);
	dup2(fd_std_out, STDOUT_FILENO);
	ft_free_ptr((void **)&(concat_minishell_with_arg));
	close(fd_std_out);
}

void	ft_set_syntax_error_and_exit_code(t_ms *ms, t_error_type error_type,
			int exit_code)
{
	ms->invalid_program = error_type;
	ms->exit_code = exit_code;
}
