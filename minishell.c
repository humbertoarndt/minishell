/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/20 18:29:22 by harndt            #+#    #+#             */
/*   Updated: 2022/11/15 20:18:05 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main(int argc, char *argv[], char *envp[])
{
	t_ms	ms;


	if (ft_check_argc_argc(argc, argv))
		return (ERROR_CODE);
	ft_create_env(&ms, envp);
	return (ft_prompt(&ms));
}