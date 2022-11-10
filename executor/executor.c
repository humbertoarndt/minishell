/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:20:01 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/09 21:12:37 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
#include "minishell.h"

void	ft_build_cmds(t_cmd *cmd)
{
	size_t	index_args;

	index_args = 0;

	while (cmd->argv_list)
	{
		if (index_args == 0)
		{
			cmd->cmd = ft_strdup((char *)cmd->argv_list->content);
			continue;
		}
		cmd->argv_list = cmd->argv_list->next;
	}
}

void	ft_exec_cmds(t_executor *exec_tree)
{
	//t_list	*pid;

	if (!exec_tree)
		return ;
	
	
}

void	ft_execute_pipe(t_executor	*exec_tree)
{

}

void	ft_execute_tree(t_ms *ms)
{
	t_executor	*exec_tree;

	if (!ms->executor)
		return ;
	exec_tree = ms->executor;
	if (ft_strncmp(exec_tree->operator, PIPE, ft_strlen(PIPE)) == 0)
		ft_execute_pipe(exec_tree);
	else
		ft_exec_cmds(exec_tree);
}
*/