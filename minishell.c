/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:29:22 by harndt            #+#    #+#             */
/*   Updated: 2022/10/31 23:16:15 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	t_ms	ms;


	if (ft_check_argc_argc(argc, argv))
		return (ERROR_CODE);
	ft_init_env(&ms, envp);
	ft_create_env(&ms);
	ft_prompt(&ms);
	return (SUCCESS_CODE);
}