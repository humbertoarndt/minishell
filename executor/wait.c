/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <harndt@student.42sp.org.br>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:41:57 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/07 15:41:39 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_wait_child(pid_t pid)
{
	int	exit_code;

	exit_code = SUCCESS_CODE;
	waitpid(pid, &exit_code, 0);
	if (WIFEXITED(exit_code))
		exit_code = WEXITSTATUS(exit_code);
	return (exit_code);
}

int	ft_wait_child2(pid_t pid, int *sig)
{
	int	exit_code;

	exit_code = SUCCESS_CODE;
	waitpid(pid, &exit_code, 0);
	if (WIFEXITED(exit_code))
	{
		exit_code = WEXITSTATUS(exit_code);
		*sig = 0;
	}
	else if (WIFSIGNALED(exit_code))
	{
		exit_code = WTERMSIG(exit_code);
		*sig = exit_code;
	}
	return (exit_code);
}

int	ft_wait_childs(t_list *pids)
{
	int	exit_code;

	while (pids)
	{
		exit_code = ft_wait_child((*(pid_t *)pids->content));
		pids = pids->next;
	}
	return (exit_code);
}