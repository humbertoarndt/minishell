/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <humberto.arndt@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:58:25 by harndt            #+#    #+#             */
/*   Updated: 2022/12/07 15:12:34 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_cd(t_ms *ms, char **argv, t_bool is_child)
{
	int	dir;

	if (argv[2])
	{
		ft_print_custom_error_and_exit(ms, argv[0], EXIT_TOO_MANY_ARGUMENTS, 1);
	}
	dir = chdir((const char *)argv[1]);
	if (dir == -1)
	{
		print_custom_arg_error2((char *[2]){"cd: ", argv[1]}, FILE_NOT_FOUND_ERROR_MSG);
		return (FALSE);
	}
	kill_child(ms, is_child, 1); // TODO Definir valor de exit_code
	return (TRUE);
}
