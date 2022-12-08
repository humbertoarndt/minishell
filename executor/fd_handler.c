/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:52:46 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/27 19:46:24 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_pipes(t_ms *ms)
{
	if (ms->ctr.pipe_count == 0 || ms->ctr.pipe_start < 0)
		return ;
	if (ms->ctr.pipe_start == 0)
	{
		ft_close_fd(ms->fd_pipe[READ_FD]);
		ft_dup2_and_close(ms->fd_pipe[WRITE_FD], STDOUT_FILENO);
	}
	else if (ms->ctr.pipe_start != ms->ctr.pipe_count)
	{
		ft_close_fd(ms->prev_fd_pipe[WRITE_FD]);
		ft_close_fd(ms->fd_pipe[READ_FD]);
		ft_dup2_and_close(ms->prev_fd_pipe[READ_FD], STDIN_FILENO);
		ft_dup2_and_close(ms->fd_pipe[WRITE_FD], STDOUT_FILENO);
	}
	else if (ms->ctr.pipe_start == ms->ctr.pipe_count)
	{
		ft_close_fd(ms->fd_pipe[WRITE_FD]);
		ft_dup2_and_close(ms->fd_pipe[READ_FD], STDIN_FILENO);
	}
}

void	ft_init_pipes(t_ms *ms)
{
	if (ms->should_pipe)
	{
		ms->ctr.pipe_start++;
		ft_close_pipe_fds(ms->prev_fd_pipe);
		if (ms->ctr.pipe_start == ms->ctr.pipe_count)
			return ;
		ft_copy_fds_pipe_to_previous(ms->fd_pipe, ms->prev_fd_pipe);
		if (pipe(ms->fd_pipe) == ERROR_CODE_FUNCTION)
			exit(1);//implementar error handler
	}
}

int	ft_set_file_flags(t_redir_type redir_type)
{
	int	flags;

	flags = O_RDONLY;
	if (redir_type == INFILE || redir_type == HEREDOC)
		flags = O_RDONLY;
	else if (redir_type == TRUNCATE)
		flags = O_TRUNC | O_CREAT | O_RDWR;
	else if (redir_type == APPEND)
		flags = O_RDWR | O_APPEND | O_CREAT;
	return (flags);
}

int	ft_check_access_file(char *file_name, t_redir_type redir_type)
{
	int	file_permission;
	int	access_permissions;

	if (redir_type == INFILE)
		access_permissions = R_OK;
	else
		access_permissions = W_OK | R_OK;
	file_permission = PERMISSION_OK;
	if (access(file_name, F_OK) != SUCCESS_CODE)
		file_permission = FILE_DOES_NOT_EXIST;
	else if (access(file_name, access_permissions) != SUCCESS_CODE)
		file_permission = PERMISSION_NOT_ALLOWED;
	return (file_permission);
}

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
			continue;
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