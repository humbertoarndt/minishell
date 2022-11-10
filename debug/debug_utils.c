/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/09 19:15:09 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/09 19:15:30 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	t_file		*f;
	static char	*file_types[] = {"NOT_FOUND_REDIR", "TRUNCATE", "APPEND",
		"INFILE", "HEREDOC"};

	while (file)
	{
		f = (t_file *)file->content;
		ft_printf(GREEN"fd:%d--name:%s--type:%s--delimeter%s\n"RESET, f->fd,
			f->file, file_types[f->type], f->delimeter);
		file = file->next;
	}
	ft_printf("\n");
}

void	ft_print_cmds(t_cmd cmds)
{
	ft_printf(RED"cmd:%s "RESET, cmds.cmd);
	while (cmds.argv_list)
	{
		ft_printf(RED"argvs:%s "RESET, (char *)cmds.argv_list->content);
		cmds.argv_list = cmds.argv_list->next;
	}
	ft_printf("\n");
}

void	ft_print_tree_elements(t_executor *exec, char *leaf, int level,
			int *ctr)
{
	ft_print_tabs(level);
	ft_printf("----------start_level:%d--------------\n", level);
	ft_print_tabs(level);
	ft_printf("%s-lvl: %d \n", leaf, level);
	ft_print_tabs(level);
	ft_printf(YELLOW"op:%s\n"RESET, exec->operator);
	ft_print_tabs(level);
	ft_print_cmds(exec->cmds);
	ft_print_tabs(level);
	ft_print_file(exec->files);
	ft_print_tabs(level);
	ft_printf("exec_order:%d\n", *ctr++);
}
