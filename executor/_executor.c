/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <humberto.arndt@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:20:01 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/22 21:46:51 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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

// t_bool	ft_handle_builtins(t_ms *ms, t_executor *exec_tree)
// {
// 	if (ft_strcmp(exec_tree->cmds, "echo") == 0)
// 		return (ms_echo(ms, exec_tree->cmds));
// 	else if (ft_strcmp(exec_tree->cmds, "cd") == 0)
// 		return (ms_cd(ms, exec_tree->cmds));
// 	else if (ft_strcmp(exec_tree->cmds, "pwd") == 0)
// 		return (ms_pwd(ms, exec_tree->cmds));
// 	else if (ft_strcmp(exec_tree->cmds, "unset") == 0)
// 		return (ms_unset(ms, exec_tree->cmds));
// 	else if (ft_strcmp(exec_tree->cmds, "env") == 0)
// 		return (ms_env(ms, exec_tree->cmds));
// 	else if (ft_strcmp(exec_tree->cmds, "exit") == 0)
// 		return (ms_exit(ms, exec_tree->cmds));
// 	else
// 		return (FALSE);
// }

void	ft_execute_tree(t_ms *ms)
{
	t_bool		status;
	t_executor	*exec_tree;

	if (!ms->executor)
		return ;
	exec_tree = ms->executor;
	if (ft_strncmp(exec_tree->operator, PIPE, ft_strlen(PIPE)) == 0)
		ft_execute_pipe(exec_tree);
	else
	{
		//checar se comando builtin ou não
			//Se builtint -> executar
		status = 0;//ft_handle_builtins(ms, exec_tree);
		if (!status)
		{
			//Se não -> fork() -> executar conforme o path
			// exec_path() // fork()
			ft_printf("Encontrar caminho\n");	
		}
	}
}


// void exec_path(int i)
// {
// 	pid_t	pid;

// 	pid = fork();
// 	if (pid = 0)
// }