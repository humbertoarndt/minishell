/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:27:30 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/16 21:59:54 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file	*ft_init_file(t_redir_type type, char *name)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	file->fd = -2;
	file->type = type;
	if (file->type == HEREDOC)
	{
		file->delimeter = name;
		file->file = HEREDOC_FILE;
	}
	else
	{
		file->delimeter = NULL;
		file->file = name;
	}
	return (file);
}

t_cmd	*ft_init_cmds(void)
{
	t_cmd	*cmds;

	cmds = (t_cmd *)malloc(sizeof(t_cmd));
	cmds->cmd = NULL;
	cmds->argv_list = NULL;
	cmds->argv = NULL;
	cmds->cmd_index = -2;
	return (cmds);
}

t_executor	*ft_init_tree(void)
{
	t_executor	*executor;

	executor = (t_executor *)malloc(sizeof(t_executor));
	if (!executor)
		return (NULL);
	executor->operator = NULL;
	executor->files = NULL;
	executor->left = NULL;
	executor->right = NULL;
	executor->cmds = ft_init_cmds();
	return (executor);
}
