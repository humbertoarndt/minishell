/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <humberto.arndt@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:46:45 by harndt            #+#    #+#             */
/*   Updated: 2022/11/01 14:34:36 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigint_handler(int signal)
{
	if (signal != SIGINT)
		return ;
	g_status.paused = TRUE;
	//Se for um processo filho
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
	ft_printf("SIGINT |%d| capturado\n", signal);
}

// void	sigquit_handler(int signal)
// {
// 	if (signal != SIGQUIT)
// 		return;
// 	g_status.paused = TRUE;
// 	if (g_status.pid)
// 	{
// 		ft_putstr("\\^Quit:\n");
// 		rl_redisplay();
// 		g_status.e_code = 131;
// 	}
// 	else
// 	{
// 		ft_putstr("$ ");
// 		ft_putstr(rl_line_buffer);
// 	}
// 	ft_printf("SIGQUIT |%d| capturado\n", signal);
// }

void	set_signals(void)
{
	sigset_t	mask;
	t_sigaction	sigint;
	// t_sigaction	sigquit;

	sigemptyset(&mask);
	sigint.sa_flags = SA_RESTART;
	sigint.sa_mask = mask;
	sigint.sa_handler = &sigint_handler;
	sigaction(SIGINT, &sigint, NULL);
	// sigquit.sa_flags = SA_RESTART;
	// sigquit.sa_mask = mask;
	// sigquit.sa_handler = &sigquit_handler;
	// sigaction(SIGQUIT, &sigquit, NULL);
	signal(SIGQUIT, SIG_IGN);
}