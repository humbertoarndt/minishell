/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:46:45 by harndt            #+#    #+#             */
/*   Updated: 2023/01/08 20:10:45 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_sigint(int sig)
{
	(void)sig;
	ft_putstr_fd("\n", STDOUT_FILENO);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

static void	handle_sigint2(int sig)
{
	if (sig == SIGINT)
	{
		g_status.paused = TRUE;
		ft_putstr_fd("\n", STDOUT_FILENO);
		rl_replace_line("", 0);
		rl_on_new_line();
	}
}

void	set_execute_signals(int child_pid)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (child_pid == 0)
		sa.sa_handler = SIG_DFL;
	else
		sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_heredoc_signals(void)
{
	struct sigaction	sa_sigint;
	// struct sigaction	sa_sigquit;a
	sa_sigint.sa_flags = 0;
	sa_sigint.sa_handler = &handle_sigint2;
	sigemptyset(&sa_sigint.sa_mask);
	sigaction(SIGINT, &sa_sigint, NULL);
	// sa_sigquit.sa_flags = 0;
	// sigemptyset(&sa_sigquit.sa_mask);
	// sa_sigquit.sa_handler = SIG_IGN;
	// sigaction(SIGQUIT, &sa_sigquit, NULL);
}

void	set_signals(void)
{
	struct sigaction	sa_sigint; // ctrl + c
	struct sigaction	sa_sigquit; // ctrl + /

	sa_sigint.sa_handler = &handle_sigint;
	sa_sigint.sa_flags = 0;
	sigemptyset(&sa_sigint.sa_mask);
	sigaction(SIGINT, &sa_sigint, NULL);
	sa_sigquit.sa_handler = SIG_IGN;
	sa_sigquit.sa_flags = 0;
	sigemptyset(&sa_sigquit.sa_mask);
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}
