/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:22:26 by harndt            #+#    #+#             */
/*   Updated: 2023/01/16 21:49:59 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	is_builtin(t_ms *ms, t_executor *exec_tree, t_bool is_child)
{
	if (!exec_tree->cmds->argv[0])
		return (FALSE);
	else if (ft_strcmp(exec_tree->cmds->argv[0], "cd") == 0)
		return (ms_cd(ms, exec_tree->cmds->argv, is_child));
	else if (ft_strcmp(exec_tree->cmds->argv[0], "echo") == 0)
		return (ms_echo(ms, exec_tree->cmds->argv, is_child));
	else if (ft_strcmp(exec_tree->cmds->argv[0], "env") == 0)
		return (ms_env(ms, is_child));
	else if (ft_strcmp(exec_tree->cmds->argv[0], "exit") == 0)
		ms_exit(ms, exec_tree->cmds->argv);
	else if (ft_strcmp(exec_tree->cmds->argv[0], "export") == 0)
		return (ms_export(ms, exec_tree->cmds, is_child));
	else if (ft_strcmp(exec_tree->cmds->argv[0], "pwd") == 0)
		return (ms_pwd(ms, is_child));
	else if (ft_strcmp(exec_tree->cmds->argv[0], "unset") == 0)
		return (ms_unset(ms, exec_tree->cmds->argv, is_child));
	return (FALSE);
}

void	kill_child(t_ms *ms, t_bool is_child, int exit_code)
{
	if (is_child)
	{
		ms->exit_code = exit_code;
		ft_free_all_ms(ms, TRUE);
		exit (exit_code);
	}
}

t_bool	check_llong(char *str)
{
	t_bool	sign;

	sign = FALSE;
	if (*str == '-' || *str == '+')
		sign = TRUE;
	if ((int)ft_strlen(str) > (20 + sign))
		return (FALSE);
	else if (!sign && (ft_strcmp(MAX_LLONG, str) < 0))
		return (FALSE);
	else if (*str == '+' && (ft_strcmp(MAX_LLONG_S, str) < 0))
		return (FALSE);
	else if (*str == '-' && (ft_strcmp(MIN_LLONG, str) < 0))
		return (FALSE);
	return (TRUE);
}
