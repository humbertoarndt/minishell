/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/25 22:22:07 by harndt            #+#    #+#             */
/*   Updated: 2022/10/28 23:46:22 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// #include "minishell.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <signal.h>

void	handle_sigint(int sig)
{
	if (sig != SIGINT)
		return ;
	printf("\tCaptured signal: |%d|\n", sig);
	printf("^C\n");
}

void	handle_siquit(int sig)
{
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

int	main(void)
{
	set_signals();
	while (1)
	{
		printf("...\n");
		sleep(5);
	}
	return (0);
}
