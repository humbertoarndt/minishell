/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_ms.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 21:52:41 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/27 22:11:17 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_buffer(t_ms *ms)
{
	free(ms->buffer_start);
	ms->buffer_start = NULL;
	ms->buffer = NULL;
}

void	ft_free_ms(t_ms *ms)
{
	ft_clear_tokens(&ms->tokens);
	ft_free_buffer(ms);
}