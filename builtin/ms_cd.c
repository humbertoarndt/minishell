/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:58:25 by harndt            #+#    #+#             */
/*   Updated: 2023/01/22 12:44:30 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*get_value_from_hash_item(t_hash_table *var, char *key)
{
	t_hash_item	*hash_item;

	hash_item = ft_search_item_by_key(var, key);
	if (!hash_item)
		return (NULL);
	return (hash_item->value);
}

static void	set_env_pwd_and_oldpwd(t_ms *ms, char *oldpwd)
{
	char	*pwd;
	char	*pwd_env;
	char	*oldpwd_env;

	pwd = getcwd(NULL, 0);
	oldpwd_env = get_value_from_hash_item(ms->env.var, "OLDPWD");
	pwd_env = get_value_from_hash_item(ms->env.var, "PWD");
	if (oldpwd_env)
		ft_update_hash_item(ms->env.var, "OLDPWD", oldpwd);
	if (pwd_env)
		ft_update_hash_item(ms->env.var, "PWD", pwd);
	free(pwd);
	free(oldpwd);
}

char	*cd_home(t_hash_table *var, char *dir)
{
	if (!dir)
	{
		dir = get_value_from_hash_item(var, "HOME");
		return (dir);
	}
	return (dir);
}

t_bool	deal_cd(t_ms *ms, char **argv, char *dir, t_bool is_child)
{
	char	*oldpwd;

	if (!dir)
	{
		dir = get_value_from_hash_item(ms->env.var, "HOME");
		if (!dir && is_child)
			ft_print_custom_error_and_exit(ms, argv[0], HOME_NOT_SET, 1);
		if (!dir)
		{
			print_custom_arg_error(argv[0], HOME_NOT_SET);
			ms->exit_code = 1;
			return (TRUE);
		}
	}
	oldpwd = getcwd(NULL, 0);
	if (chdir(dir) == -1)
	{
		free(oldpwd);
		print_custom_arg_error2((char *[2]){"cd: ", argv[1]},
			FILE_NOT_FOUND_ERROR_MSG);
		ms->exit_code = 1;
		return (TRUE);
	}
	set_env_pwd_and_oldpwd(ms, oldpwd);
	return (TRUE);
}

t_bool	ms_cd(t_ms *ms, char **argv, t_bool is_child)
{
	char	*dir;
	t_bool	result_cd;

	dir = argv[1];
	ms->exit_code = SUCCESS_CODE;
	if (dir && argv[2])
	{
		print_custom_arg_error(argv[0], EXIT_TOO_MANY_ARGUMENTS);
		ms->exit_code = 1;
		return (TRUE);
	}
	result_cd = deal_cd(ms, argv, dir, is_child);
	kill_child(ms, is_child, 1);
	return (result_cd);
}
