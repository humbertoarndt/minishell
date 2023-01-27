/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnum.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 20:30:51 by harndt            #+#    #+#             */
/*   Updated: 2023/01/22 13:07:37 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_bool	ft_isnum(char *str)
{
	if (!*str)
		return (FALSE);
	if (*str == '-' || *str == '+')
		str++;
	while (*str)
		if (!ft_isdigit(*str++))
			return (FALSE);
	return (TRUE);
}
