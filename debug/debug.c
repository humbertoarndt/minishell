/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:09:40 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/09 19:59:16 by bbonaldi         ###   ########.fr       */
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

void	ft_print_tree_recursive(t_executor *exec, char *leaf, int level,
			int should_reset)
{
	static int	counter;

	if (should_reset == TRUE)
		counter = 0;
	if (exec == NULL)
	{
		ft_print_tabs(level);
		ft_printf("leaf:%s|level:%d|exec_order:%d-->NULL\n", leaf, level,
			counter++);
		return ;
	}
	ft_print_tree_elements(exec, leaf, level, &counter);
	ft_print_tree_recursive(exec->left, YELLOW"left"RESET, level + 1, FALSE);
	ft_print_tree_recursive(exec->right, BLUE"right"RESET, level + 1, FALSE);
}
