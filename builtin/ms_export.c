/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <humberto.arndt@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 22:00:23 by harndt            #+#    #+#             */
/*   Updated: 2022/12/05 22:37:51 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_export(t_ms *ms, t_bool is_child)
{	
	t_hash_item	*hash_tmp;
	size_t		index;

	index = 0;
	while (index < ms->env.var->size)
	{
		hash_tmp = ms->env.var->hash_items[index];
		while (hash_tmp)
		{
			ft_printf("declare -x ");
			ft_print_hash_item(hash_tmp);
			hash_tmp = hash_tmp->next;
		}
		index++;
	}
	kill_child(ms, is_child, 1); // TODO Definir valor de exit_code
	return (TRUE);
}
