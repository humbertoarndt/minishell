/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/11 22:52:46 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/12/07 21:57:09 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_close_fd(int fd)
{
	if (fd < 0)
		return ;
	close(fd);
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
