/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <humberto.arndt@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:22:07 by harndt            #+#    #+#             */
/*   Updated: 2022/10/31 22:19:38 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_sigint(int sig)
{
	ft_putnbr_fd(sig, 1);
	if (sig != SIGINT)
		return ;
	g_status.paused = TRUE;
	if (g_status.pid)
	{
		ft_putstr("^Ç\n");
		rl_replace_line("", 0);
		rl_on_new_line();
	}
	else
	{
		ft_putchar('\n');
		rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
	}
}

void	handle_siquit(int sig)
{
	ft_putnbr_fd(sig, 1);
	if (sig != SIGQUIT)
		return ;
	printf("\tCaptured signal: |%d|\n", sig);
}

void	set_signals(void)
{
	signal(SIGINT, handle_sigint);
	signal(SIGQUIT, handle_siquit);
	signal(SIGSEGV, SIG_IGN);
}
