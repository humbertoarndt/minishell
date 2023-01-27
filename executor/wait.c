/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 19:41:57 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/20 23:41:43 by bbonaldi         ###   ########.fr       */
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

void	ft_wait_childs(t_ms *ms, t_list *pids)
{
	while (pids)
	{
		ms->exit_code = ft_wait_child((*(pid_t *)pids->content));
		pids = pids->next;
	}
}
