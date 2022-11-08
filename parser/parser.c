/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 19:29:45 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/07 23:19:40 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_has_operator(t_token_type type)
{
	return (type == PIPELINE || type == AND_IF || type == OR_IF);
}

int	ft_has_redirect(t_token_type type)
{
	return (type == IO_FILE_TRUNCATE || type == IO_FILE_INFILE || type == IO_FILE_APPEND || type == IO_HEREDOC);
}

t_redir_type ft_convert_token_type_redir_type(t_token_type token_type)
{
	if (token_type == IO_FILE_APPEND)
		return (APPEND);
	if (token_type == IO_FILE_INFILE)
		return (INFILE);
	if (token_type == IO_FILE_TRUNCATE)
		return (TRUNCATE);
	if (token_type == IO_HEREDOC)
		return (HEREDOC);
	return (NOT_FOUND_REDIR);
}

void	ft_add_file(t_executor *current_tree, t_token *token_head)
{
	t_file			*file;
	t_redir_type	redir_type;
	t_list			*list_file;

	redir_type = ft_convert_token_type_redir_type(token_head->type);
	file = ft_init_file(redir_type, token_head->token);
	list_file = ft_lstnew(file);
	ft_lstadd_back(&current_tree->files, list_file);
}

void	ft_add_command(t_executor *current_tree, t_token *token_head)
{
	t_list			*list_argv;

	if (!current_tree->cmds.cmd)
		current_tree->cmds.cmd = token_head->token;
	else
	{
		list_argv = ft_lstnew(ft_strdup(token_head->token));
		ft_lstadd_back(&current_tree->cmds.argv_list, list_argv);
	}
}

t_executor *ft_parser(t_ms *ms)
{
	t_executor	*current_tree;
	t_executor	*final_tree;
	t_token		*head_token;
	t_executor	*parent_tree;

	current_tree = ft_init_tree();
	final_tree = current_tree;
	head_token = ms->tokens;
	while (head_token)
	{
		if (ft_has_operator(head_token->type))
		{
			parent_tree = ft_init_tree();
			parent_tree->left = current_tree;
			parent_tree->operator = ft_strdup(head_token->token);
			parent_tree->right = ft_init_tree();
			current_tree = parent_tree->right;
			final_tree = parent_tree;
		}
		else
		{
			if (ft_has_redirect(head_token->type))
				ft_add_file(current_tree, head_token);
			else
				ft_add_command(current_tree, head_token);
		}
		head_token = head_token->next;
	}
	return (final_tree);
}
