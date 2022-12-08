/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wait.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/27 17:28:38 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/12/06 22:05:56 by bbonaldi         ###   ########.fr       */
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

int	ft_should_conditional_operator(t_executor *exec_tree)
{
	int	root_is_conditional_and;
	int	root_is_conditional_or;
	
	root_is_conditional_and = (exec_tree->root 
		&& ft_strcmp(exec_tree->root->operator, AND_IF_OP) == 0)
		|| (exec_tree->root && exec_tree->root->root && ft_strcmp(exec_tree->root->operator, PIPE)
		&& ft_strcmp(exec_tree->root->root->operator, AND_IF_OP) == 0) ;
	if (root_is_conditional_and)
		return (AND_OP);
	root_is_conditional_or = (exec_tree->root 
		&& ft_strcmp(exec_tree->root->operator, AND_OR_OP) == 0)
		|| (exec_tree->root && exec_tree->root->root && ft_strcmp(exec_tree->root->operator, PIPE)
		&& ft_strcmp(exec_tree->root->root->operator, AND_OR_OP) == 0);
	if (root_is_conditional_or)
		return (OR_OP);
	return (FALSE);
}

void	ft_parent_wait(t_ms *ms, pid_t *pid, t_executor *exec_tree)
{
	t_list *pid_list;

	ms->conditional_operator = ft_should_conditional_operator(exec_tree);
	ft_printf("",exec_tree->cmds->argv);
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