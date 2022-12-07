/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <humberto.arndt@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:58:42 by harndt            #+#    #+#             */
/*   Updated: 2022/12/05 22:46:10 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_pwd(t_ms *ms, t_bool is_child)
{
	char	*pwd;

	pwd = getcwd(NULL, 0);
	ft_insert_or_update_hash_item(ms->env.var, "PWD", pwd);
	ft_putendl_fd(pwd, STDOUT);
	kill_child(ms, is_child, 0); // TODO Definir valor de exit_code
	return (TRUE);
}