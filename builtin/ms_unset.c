/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <humberto.arndt@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:58:12 by harndt            #+#    #+#             */
/*   Updated: 2022/12/05 22:37:57 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_unset(t_ms *ms, char **argv, t_bool is_child)
{
	size_t	i;

	i = -1;
	while (argv[++i])
		ft_delete_hash_item_by_key(ms->env.var, argv[i]);
	kill_child(ms, is_child, 0); // TODO Definir valor de exit_code
	return (TRUE);
}