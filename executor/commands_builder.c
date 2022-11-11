/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands_builder.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 21:11:05 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/10 22:33:11 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_access_bin(char **cmd)
{
	if (access(*cmd, R_OK) == SUCCESS_CODE)
		return (TRUE);
	ft_free_ptr((void **)cmd);
	return (FALSE);
}

char	*ft_build_cmd(char *command, char **path)
{
	size_t	index;
	char	*path_with_slash;
	int		is_valid_bin;
	char	*command_found;

	is_valid_bin = FALSE;
	command_found = NULL;
	index = 0;
	while (*path[index])
	{
		path_with_slash = ft_strjoin(path[index], SLASH_STRING);
		if (is_valid_bin == FALSE)
		{
			command_found = ft_strjoin(path_with_slash, command);
			is_valid_bin = ft_check_access_bin(&command_found);
		}
		ft_free_ptr((void **)&(path_with_slash));
		if (is_valid_bin)
			return (command_found);
		index++;
	}
	if (!command_found)
	{
		is_valid_bin = ft_check_access_bin(&command);
		if (is_valid_bin)
			return (ft_strdup(command));
		return (NULL);
	}
	return (command_found);
}

void	ft_build_cmds(t_cmd *cmd, char **path)
{
	size_t	index_args;
	int		list_size;
	char	*argv_string;
	t_list	*arg_list;

	index_args = 0;
	arg_list = cmd->argv_list;
	list_size = ft_lstsize(cmd->argv_list);
	cmd->argv = (char **)ft_calloc(sizeof(char *), (list_size + 1));
	while (arg_list)
	{
		argv_string = (char *)arg_list->content;
		if (index_args == 0)
		{
			cmd->cmd = ft_build_cmd(argv_string, path);
			index_args++;
			continue;
		}
		cmd->argv[index_args - 1] = ft_strdup(argv_string);
		arg_list = arg_list->next;
		index_args++;
	}
}
