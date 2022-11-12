/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_tree.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 21:27:30 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/11 23:45:45 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_file	*ft_init_file(t_redir_type type, char *name)
{
	t_file	*file;

	file = (t_file *)malloc(sizeof(t_file));
	file->fd = -2;
	file->delimeter = NULL;
	file->type = type;
	file->file = name;
	return (file);
}

void	ft_init_cmds(t_cmd *cmds)
{
	cmds->cmd = NULL;
	cmds->argv_list = NULL;
	cmds->argv = NULL;
}

t_executor	*ft_init_tree(int depth)
{
	t_executor	*executor;

	executor = (t_executor *)malloc(sizeof(t_executor));
	if (!executor)
		return (NULL);
	executor->operator = NULL;
	executor->files = NULL;
	executor->left = NULL;
	executor->right = NULL;
	executor->depth = depth;
	ft_init_cmds(&executor->cmds);
	return (executor);
}
