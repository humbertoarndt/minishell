/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <humberto.arndt@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:57:49 by harndt            #+#    #+#             */
/*   Updated: 2022/12/05 22:37:43 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_bool	ms_echo(t_ms *ms, char **argv, t_bool is_child)
{
	size_t	i;
	t_bool	nl;

	i = 1;
	nl = TRUE;
	if (argv[i] && !ft_strcmp(argv[i], "-n"))
	{
		nl = FALSE;
		i++;
	}
	while (argv[i])
		ft_putstr_fd(argv[i++], STDOUT);
	if (nl)
		ft_putendl_fd("",STDOUT );
	kill_child(ms, is_child, 0); // TODO Definir valor de exit_code
	return (TRUE);
}
