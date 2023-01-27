/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/14 13:43:34 by harndt            #+#    #+#             */
/*   Updated: 2023/01/21 02:40:01 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	should_stop_on_signals_quoting(t_ms *ms, char *line, char quote)
{
	int	fd_std_out;

	if (g_status.paused || !line)
	{
		if (!line && g_status.paused == FALSE)
		{
			fd_std_out = dup(STDOUT_FILENO);
			dup2(STDERR_FILENO, STDOUT_FILENO);
			ft_printf("\nminishell: unexpected EOF while " \
				" looking for matching `%s'\n", (char [2]){quote, '\0'});
			ft_printf("minishell: syntax error: unexpected end of file\n");
			dup2(fd_std_out, STDOUT_FILENO);
			close(fd_std_out);
			ft_set_syntax_error_and_exit_code(ms, SYNTAX_ERR, 2);
		}
		else
			ft_set_syntax_error_and_exit_code(ms, SYNTAX_ERR, 130);
		g_status.paused = FALSE;
		return (TRUE);
	}
	return (FALSE);
}

void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_replace_line("", 1);
	rl_on_new_line();
	rl_redisplay();
}

void	handle_sigint2(int sig)
{
	if (sig == SIGINT)
	{
		g_status.paused = TRUE;
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 1);
		rl_on_new_line();
	}
}

void	handle_sigint3(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDERR_FILENO);
	rl_replace_line("", 1);
	rl_on_new_line();
}
