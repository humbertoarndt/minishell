/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 21:52:41 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/18 23:46:18 by bbonaldi         ###   ########.fr       */
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
	if (!ms->env.path)
		return ;
	while (ms->env.path[index])
		ft_free_ptr((void **)&(ms->env.path[index++]));
	ft_free_ptr((void **)(ms->env.path));
	ft_free_ptr((void **)&(ms->env.path));
}

void	ft_free_all_ms(t_ms *ms, t_bool free_env)
{
	if (free_env == TRUE)
	{
		ft_clear_hash_table(ms->env.var);
		ft_free_path(ms);
	}
	ft_clear_tokens(&ms->tokens);
	ft_free_tree(&ms->executor);
	ft_free_buffer(ms);
	if (ft_lstsize(ms->pids) > 0)
		ft_lstclear(&ms->pids, free);
	ft_free_ptr((void **)&ms->prompt_str);
	rl_clear_history();
}
