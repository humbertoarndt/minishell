/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_handler_redirection_utils.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 21:55:14 by bbonaldi          #+#    #+#             */
/*   Updated: 2023/01/16 22:23:29 by bbonaldi         ###   ########.fr       */
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
