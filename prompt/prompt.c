/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 21:56:49 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/28 19:27:45 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_prompt(t_ms *ms)
{
	while (TRUE)
	{
		ft_init_ms(ms);
		// set_signals();
		ms->buffer = readline(BASH_START);
		if (ms->buffer == NULL) 
			return (SUCCESS_CODE);
		ms->buffer_start = ms->buffer;
		add_history(ms->buffer);
		if (ft_strncmp(ms->buffer,"z", strlen("z")) == 0)
		{
			rl_clear_history();
			ft_free_ms(ms);
			exit(SUCCESS_CODE);
		}
		ft_tokenizer(ms);
		ft_print_tokens_list(ms->tokens);
		printf( "%s\n", ms->buffer_start);
	}
	return (SUCCESS_CODE);
}