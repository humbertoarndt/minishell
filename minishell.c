/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:29:22 by harndt            #+#    #+#             */
/*   Updated: 2023/01/16 22:39:24 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_status	g_status;

int	main(int argc, char *argv[], char *envp[])
{
	t_ms	ms;

	g_status.e_code = 0;
	if (ft_check_argc_argc(argc, argv))
		return (ERROR_CODE);
	ft_create_env(&ms, envp);
	return (ft_prompt(&ms));
}
