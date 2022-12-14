/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 21:52:41 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/12/07 22:01:35 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_buffer(t_ms *ms)
{
	ft_free_ptr((void **)&(ms->buffer_start));
	ms->buffer = NULL;
}

void	ft_free_ms(t_ms *ms)
{
	ft_clear_tokens(&ms->tokens);
	ft_free_tree(&ms->executor);
	ft_free_buffer(ms);
	if (ft_lstsize(ms->pids) > 0)
		ft_lstclear(&ms->pids, free);
	ft_free_ptr((void **)&ms->prompt_str);
}

void	ft_free_path(t_ms *ms)
{
	size_t	index;

	index = 0;
	while (ms->env.path[index])
		ft_free_ptr((void **)&(ms->env.path[index++]));
	ft_free_ptr((void **)(ms->env.path));
	ft_free_ptr((void **)&(ms->env.path));
}

void	ft_free_all_ms(t_ms *ms)
{
	ft_clear_tokens(&ms->tokens);
	ft_clear_hash_table(ms->env.var);
	ft_free_path(ms);
	ft_free_tree(&ms->executor);
	ft_free_buffer(ms);
	if (ft_lstsize(ms->pids) > 0)
		ft_lstclear(&ms->pids, free);
	ft_free_ptr((void **)&ms->prompt_str);
	rl_clear_history();
}
