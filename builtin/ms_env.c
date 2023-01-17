/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:57:34 by harndt            #+#    #+#             */
/*   Updated: 2023/01/16 21:36:12 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_env(t_ms *ms, t_bool is_child)
{
	ft_print_hash_table(ms->env.var);
	kill_child(ms, is_child, 0);
	return (TRUE);
}
