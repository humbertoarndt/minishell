/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_tree.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/07 22:05:39 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/08 22:44:50 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_cmds(t_cmd *cmds)
{
	ft_lstclear(&cmds->argv_list, free);
	ft_free_ptr((void **)&(cmds->cmd));
}

void	ft_free_tree(t_executor **exec)
{
	if (*exec)
	{
		if ((*exec)->left)
			ft_free_tree(&(*exec)->left);
		if ((*exec)->right)
			ft_free_tree(&(*exec)->right);
		if ((*exec)->operator)
			free((*exec)->operator);
		ft_lstclear(&(*exec)->files, free);
		ft_free_cmds(&(*exec)->cmds);
		free(*exec);
		*exec = NULL;
	}
}
