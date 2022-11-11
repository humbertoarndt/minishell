/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_matrix.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 18:08:15 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/10 21:00:34 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_matrix(void ***matrix)
{
	size_t	index_matrix;

	index_matrix = 0;
	if (*matrix[index_matrix])
	{
		while (*matrix[index_matrix])
			ft_free_ptr(*matrix[index_matrix++]);
		ft_free_ptr(*matrix);
	}
}
