/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:46:45 by harndt            #+#    #+#             */
/*   Updated: 2023/01/21 02:39:31 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_execute_signals(int child_pid)
{
	struct sigaction	sa;

	sa.sa_flags = 0;
	sigemptyset(&sa.sa_mask);
	if (child_pid == 0)
		sa.sa_handler = &handle_sigint3;
	else
		sa.sa_handler = SIG_IGN;
	sigaction(SIGINT, &sa, NULL);
	sigaction(SIGQUIT, &sa, NULL);
}

void	set_heredoc_signals(void)
{
	struct sigaction	sa_sigint;

	sa_sigint.sa_flags = 0;
	sa_sigint.sa_handler = &handle_sigint2;
	sigemptyset(&sa_sigint.sa_mask);
	sigaction(SIGINT, &sa_sigint, NULL);
}

void	set_signals(void)
{
	struct sigaction	sa_sigint;
	struct sigaction	sa_sigquit;

	sa_sigint.sa_handler = &handle_sigint;
	sa_sigint.sa_flags = SA_RESTART;
	sigemptyset(&sa_sigint.sa_mask);
	sigaction(SIGINT, &sa_sigint, NULL);
	sa_sigquit.sa_handler = SIG_IGN;
	sa_sigquit.sa_flags = 0;
	sigemptyset(&sa_sigquit.sa_mask);
	sigaction(SIGQUIT, &sa_sigquit, NULL);
}
