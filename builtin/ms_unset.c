/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:58:12 by harndt            #+#    #+#             */
/*   Updated: 2023/01/20 23:28:55 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_unset(t_ms *ms, char **argv, t_bool is_child)
{
	size_t	i;

	i = 0;
	ms->exit_code = SUCCESS_CODE;
	while (argv[i])
	{
		if (ft_strcmp(argv[i], PATH) == 0)
			ft_free_path(ms);
		ft_delete_hash_item_by_key(ms->env.var, argv[i++]);
	}
	kill_child(ms, is_child, 0);
	return (TRUE);
}
