/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/21 19:22:26 by harndt            #+#    #+#             */
/*   Updated: 2023/01/22 16:26:20 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	set_redirection_builtin(t_ms *ms, t_executor *exec_tree,
			t_bool is_child)
{
	t_bool	should_stop_builtin;

	should_stop_builtin = FALSE;
	if (!is_child)
	{
		ft_set_redirection_fds(ms, exec_tree, FALSE);
		if (ms->invalid_program)
			should_stop_builtin = TRUE;
	}
	return (should_stop_builtin);
}

t_bool	is_builtin(t_ms *ms, t_executor *exec_tree, t_bool is_child)
{
	if (set_redirection_builtin(ms, exec_tree, is_child))
		return (TRUE);
	if (!exec_tree->cmds->argv[0])
		return (FALSE);
	else if (ft_strcmp(exec_tree->cmds->argv[0], "cd") == 0)
		return (ms_cd(ms, exec_tree->cmds->argv, is_child));
	else if (ft_strcmp(exec_tree->cmds->argv[0], "echo") == 0)
		return (ms_echo(ms, exec_tree->cmds->argv, is_child));
	else if (ft_strcmp(exec_tree->cmds->argv[0], "env") == 0)
		return (ms_env(ms, is_child));
	else if (ft_strcmp(exec_tree->cmds->argv[0], "exit") == 0)
	{
		ms_exit(ms, exec_tree->cmds->argv);
		return (TRUE);
	}
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
