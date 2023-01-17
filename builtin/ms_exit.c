/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:58:02 by harndt            #+#    #+#             */
/*   Updated: 2023/01/16 21:35:36 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_exit(t_ms *ms, char **argv)
{
	t_llong	exit_code;

	exit_code = SUCCESS_CODE;
	if (argv && argv[1])
	{
		if (!check_llong(argv[1]) || !ft_isnum(argv[1]))
		{
			ft_print_custom_error_and_exit2(ms, (char *[2]){"exit: ", argv[1]},
				NUMERIC_ARGUMENT_REQUIRED, 2);
		}
		else if (argv[2])
		{
			ft_print_custom_error_and_exit(ms, argv[0],
				EXIT_TOO_MANY_ARGUMENTS, 1);
		}
		else
			exit_code = ft_atoll(argv[1]);
	}
	ft_free_all_ms(ms, TRUE);
	ft_printf("exit\n");
	exit(exit_code);
}
