/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 21:58:02 by harndt            #+#    #+#             */
/*   Updated: 2023/01/22 16:09:06 by bbonaldi         ###   ########.fr       */
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
			ft_printf("exit\n");
			ft_print_custom_error_and_exit2(ms, (char *[2]){"exit: ", argv[1]},
				NUMERIC_ARGUMENT_REQUIRED, 2);
		}
		else if (argv[2])
		{
			ft_printf("exit\n");
			print_custom_arg_error(argv[0], EXIT_TOO_MANY_ARGUMENTS);
			ft_set_syntax_error_and_exit_code(ms, SYNTAX_ERR, 1);
			return ;
		}
		else
			exit_code = ft_atoll(argv[1]);
	}
	ft_free_all_ms(ms, TRUE);
	ft_printf("exit\n");
	exit(exit_code);
}
