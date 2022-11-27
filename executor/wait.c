/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:28:38 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/27 19:12:08 by bbonaldi         ###   ########.fr       */
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

int	ft_wait_childs(t_list *pids)
{
	int	exit_code;

	exit_code = SUCCESS_CODE;
	while (pids)
	{
		exit_code = ft_wait_child((*(pid_t *)pids->content));
		pids = pids->next;
	}
	return (exit_code);
}

int	ft_set_should_run_next_cmd(t_conditional_op op, int exit_code)
{
	if (op == AND_OP && exit_code != SUCCESS_CODE)
		return (FALSE);
	if (op == OR_OP && exit_code == SUCCESS_CODE)
		return (FALSE);
	return (TRUE);
}

void	ft_parent_wait(t_ms *ms, pid_t *pid)
{
	t_list *pid_list;

	if (ms->conditional_operator)
	{
		ms->exit_code = ft_wait_child(*pid);
		ft_free_ptr((void **)&pid);
		ms->should_exec_next = ft_set_should_run_next_cmd(
			ms->conditional_operator, ms->exit_code);
		ms->conditional_operator = FALSE;
	}
	else
	{
		pid_list = ft_lstnew(pid);
		ft_lstadd_back(&ms->pids, pid_list);
	}
}