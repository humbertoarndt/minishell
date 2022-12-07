/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: harndt <humberto.arndt@gmail.com>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:58:02 by harndt            #+#    #+#             */
/*   Updated: 2022/12/05 22:37:49 by harndt           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit(t_ms *ms, char **argv)
{
	t_llong	exit_code;

	if (argv && argv[1])
	{
		if (!check_llong(argv[1]) || !ft_isnum(argv[1]))
		{
			ft_print_custom_error_and_exit2(ms, (char *[2]){"exit: ", argv[1]}, NUMERIC_ARGUMENT_REQUIRED, 2);
		}
		else if (argv[2])
		{
			ft_print_custom_error_and_exit(ms, argv[0], EXIT_TOO_MANY_ARGUMENTS, 1);
		}
		else
			exit_code = ft_atoll(argv[1]);
	}
	ft_free_all_ms(ms);
	exit(exit_code);
}