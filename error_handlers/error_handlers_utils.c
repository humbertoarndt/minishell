/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:32:05 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/17 23:41:53 by bbonaldi         ###   ########.fr       */
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

	if (!*tok)
		token = "newline";
	else
		token = tok;
	syntax_error = ft_strjoin(SYNTAX_ERROR, token);
	return (syntax_error);
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
