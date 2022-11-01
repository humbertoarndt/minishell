/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handlers_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 18:32:05 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/28 19:05:47 by bbonaldi         ###   ########.fr       */
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

void	print_custom_arg_error(char *arg, char *message)
{
	int		fd_std_out;
	char	*concat_minishell_with_arg;

	concat_minishell_with_arg = ft_strjoin(MINISHELL, arg);
	fd_std_out = dup(STDOUT_FILENO);
	dup2(STDERR_FILENO, STDOUT_FILENO);
	ft_printf(RED"%s: %s\n"RESET, concat_minishell_with_arg, message);
	dup2(fd_std_out, STDOUT_FILENO);
	close(fd_std_out);
}
