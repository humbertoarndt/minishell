/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:58:42 by harndt            #+#    #+#             */
/*   Updated: 2023/01/20 23:29:12 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_pwd(t_ms *ms, t_bool is_child)
{
	char	*pwd;

	ms->exit_code = SUCCESS_CODE;
	pwd = getcwd(NULL, 0);
	ft_insert_or_update_hash_item(ms->env.var, "PWD", pwd);
	ft_putendl_fd(pwd, STDOUT);
	kill_child(ms, is_child, 0);
	return (TRUE);
}
