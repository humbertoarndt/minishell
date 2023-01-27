/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:57:49 by harndt            #+#    #+#             */
/*   Updated: 2023/01/20 23:16:20 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_echo(t_ms *ms, char **argv, t_bool is_child)
{
	size_t	i;
	t_bool	nl;

	i = 1;
	nl = TRUE;
	ms->exit_code = SUCCESS_CODE;
	if (argv[i] && !ft_strcmp(argv[i], "-n"))
	{
		nl = FALSE;
		i++;
	}
	while (argv[i])
	{
		ft_putstr_fd(argv[i++], STDOUT);
		if (argv[i])
			ft_putchar_fd(' ', STDOUT);
	}
	if (nl)
		ft_putendl_fd("", STDOUT);
	kill_child(ms, is_child, 0);
	return (TRUE);
}
