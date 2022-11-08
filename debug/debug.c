/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:09:40 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/31 22:28:32 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_tokens_list(t_token *token_head)
{
	t_token		*head;
	static char	*types[] = {"NOT_FOUND", "WORD", "IO_FILE_TRUNCATE",
		"IO_FILE_APPEND", "IO_FILE_INFILE", "IO_HEREDOC", "OR_IF", "AND_IF",
		"VAR_EXPRESSION", "WILDCARD", "PIPELINE", "OPEN_PARENTHESIS",
		"CLOSE_PARENTHESIS", "SINGLE_QUOTE", "DOUBLE_QUOTE"};

	head = token_head;
	while (head)
	{
		ft_printf(GREEN"----------------------------\n"RESET);
		ft_printf(YELLOW"token: %s\n"RESET, head->token);
		ft_printf(BLUE"type: %s\n"RESET, types[head->type]);
		ft_printf(GREEN"----------------------------\n"RESET);
		head = head->next;
	}
}
