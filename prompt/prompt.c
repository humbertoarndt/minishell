/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 21:56:49 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/15 20:23:59 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_prompt(t_ms *ms)
{
	ms->exit_code = SUCCESS_CODE;
	while (TRUE)
	{
		ft_init_ms(ms);
		//set_signals();
		ms->buffer = readline(BASH_START);
		// if (ms->buffer == NULL) 
		// 	return (SUCCESS_CODE);
		if (ms->buffer == NULL) //isso aqui resolve o Cntrl+D???
		{
			ft_putstr("hey\n");
			exit(0);
		}
		ms->buffer_start = ms->buffer;
		add_history(ms->buffer);
		if (ft_strncmp(ms->buffer, "quit", strlen("quit")) == 0)
		{
			ft_free_all_ms(ms);
			exit(SUCCESS_CODE);
		}
		ft_tokenizer(ms);
		//ft_print_tokens_list(ms->tokens);
		ms->executor = ft_parser(ms);
		//ft_print_tree_recursive(ms->executor, "root", 0, TRUE);
		ms->exit_code = ft_execute(ms);
		//printf("%s\n", ms->buffer_start);
		ft_free_ms(ms);
	}
	return (ms->exit_code);
}