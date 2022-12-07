/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <humberto.arndt@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:57:34 by harndt            #+#    #+#             */
/*   Updated: 2022/12/05 22:37:45 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_env(t_ms *ms, t_bool is_child)
{
	ft_print_hash_table(ms->env.var);
	kill_child(ms, is_child, 0); // TODO Definir valor de exit_code
	return (TRUE);
}