/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler_redirection.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:52:46 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/16 22:48:05 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_init_redirection_fds(t_ms *ms, t_file *file)
{
	int		flags;

	flags = ft_set_file_flags(file->type);
	file->fd = open(file->file, flags, DEFAULT_PERMISSION);
	if (file->fd < 0)
	{
		ms->exit_code = 1;
		ft_print_error_and_exit(ms, file->file, errno);
	}
	return (file->fd);
}

void	ft_close_unused_fds(t_list	*file_list, int fds[2])
{
	t_file	*file;

	while (file_list)
	{
		file = (t_file *)file_list->content;
		if (file->fd == fds[INFILE] || file->fd == fds[OUTFILE])
		{
			file_list = file_list->next;
			continue ;
		}
		ft_close_fd(file->fd);
		file_list = file_list->next;
	}
}

void	ft_handle_redirections(int fds[2])
{
	if (fds[INFILE] == NOT_FOUND_FD && fds[OUTFILE] == NOT_FOUND_FD)
		return ;
	if (fds[INFILE] != NOT_FOUND_FD)
		ft_dup2_and_close(fds[INFILE], STDIN_FILENO);
	if (fds[OUTFILE] != NOT_FOUND_FD)
		ft_dup2_and_close(fds[OUTFILE], STDOUT_FILENO);
}

void	ft_set_redirection_fds(t_ms *ms, t_executor *exec_tree)
{
	int		fds[2];
	t_file	*file;
	t_list	*file_list;

	file_list = exec_tree->files;
	fds[INFILE] = NOT_FOUND_FD;
	fds[OUTFILE] = NOT_FOUND_FD;
	while (file_list)
	{
		file = (t_file *)file_list->content;
		if (file->type == INFILE || file->type == HEREDOC)
			fds[INFILE] = ft_init_redirection_fds(ms, file);
		else if (file->type == TRUNCATE || file->type == APPEND)
			fds[OUTFILE] = ft_init_redirection_fds(ms, file);
		file_list = file_list->next;
	}
	ft_close_unused_fds(exec_tree->files, fds);
	ft_handle_redirections(fds);
}
