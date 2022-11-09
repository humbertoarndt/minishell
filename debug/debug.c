/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:09:40 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/08 23:29:46 by bbonaldi         ###   ########.fr       */
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

void	ft_print_tabs(int tabs)
{
	while (tabs)
	{
		ft_printf("\t");
		tabs--;
	}
}

void	ft_print_file(t_list *file)
{
	t_file	*f;

	static char *file_types[] = {"NOT_FOUND_REDIR", "TRUNCATE", "APPEND",
		"INFILE", "HEREDOC"};
	while (file)
	{
		f = (t_file *)file->content;
		ft_printf("fd:%d--name:%s--type:%s--delimeter%s\n", f->fd, f->file,
			file_types[f->type],f->delimeter);
		file = file->next;
	}
	ft_printf("\n");
}

void	ft_print_cmds(t_cmd cmds)
{
	ft_printf("cmd:%s ", cmds.cmd);
	while (cmds.argv_list)
	{
		ft_printf("argvs:%s ", (char *)cmds.argv_list->content);
		cmds.argv_list = cmds.argv_list->next;
	}
	ft_printf("\n");
}

void	ft_print_tree_elements(t_executor *exec, char *leaf, int level)
{
	ft_print_tabs(level);
	ft_printf("----------start_level:%d--------------\n", level);
	ft_print_tabs(level);
	ft_printf("%s-lvl: %d \n", leaf, level);
	ft_print_tabs(level);
	ft_printf("op:%s\n", exec->operator);
	ft_print_tabs(level);
	ft_print_cmds(exec->cmds);
	ft_print_tabs(level);
	ft_print_file(exec->files);
	
}

void	ft_print_tree_recursive(t_executor *exec, char *leaf,int level)
{
	if (exec == NULL)
	{
		ft_print_tabs(level);
		ft_printf("leaf:%s|level:%d-->NULL\n", leaf, level);
		return ;
	}
	ft_print_tree_elements(exec, leaf, level);
	ft_print_tree_recursive(exec->left, YELLOW"left"RESET, level + 1);
	ft_print_tree_recursive(exec->right, BLUE"right"RESET, level + 1);
}