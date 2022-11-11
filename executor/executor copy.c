/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 20:20:01 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/10 19:17:09 by bbonaldi         ###   ########.fr       */
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

t_bin    *get_builtin(char *cmd_path)
{
	static t_bin_def	builtins[7] = {
	{"echo", builtin_echo},
	{"cd", builtin_cd},
	{"pwd", builtin_pwd},
	{"export", builtin_export},
	{"unset", builtin_unset},
	{"env", builtin_env},
	{"exit", builtin_exit},
	};
	int	i;

	i = 0;
	while (i < 7)
	{
		if (ft_streq(cmd_path, builtins[i].name))
			return (builtins[i].builtin);
		i++;
	}
	return (NULL);
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
	{
		//checar se comando builtin ou não
		if (exec_tree->cmds == builts[8])
		{
			//Se builtint -> executar
		}
		else
		{
			exec_path() // fork()
			//Se não -> fork() -> executar conforme o path
		}
	}
}


void exec_path(int i)
{
	pid_t	pid;

	pid = fork();
	if (pid = 0)
}