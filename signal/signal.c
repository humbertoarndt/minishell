/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:46:45 by harndt            #+#    #+#             */
/*   Updated: 2022/12/15 15:45:51 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// https://discord.com/channels/706206701598277681/805218563194355732/1033103735880159352

void	sigint_handler(int sig)
{
	if (sig != SIGINT)
		return ;
	g_status.paused = TRUE;
	if (g_status.pid)
	{
		ft_putstr("^C\n");
		rl_replace_line("", 0);
		rl_on_new_line();
		g_status.e_code = 130;
	}
	else
	{
		ft_putchar('\n');
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_status.e_code = 1;
	}
}

void	sigquit_handler(int sig)
{
	if (sig != SIGQUIT)
		return;
	g_status.paused = TRUE;
	if (g_status.pid)
	{
		ft_putstr("\\^Quit:\n");
		rl_redisplay();
		g_status.e_code = 131;
	}
	else
		ft_putstr(rl_line_buffer);
}

void	set_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
	signal(SIGSEGV, SIG_IGN);
}
