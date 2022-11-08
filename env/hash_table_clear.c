/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_clear.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:10:43 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/11/01 21:22:47 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_clear_hash_item(t_hash_item *hash_item)
{
	ft_free_ptr((void **)&(hash_item->key));
	ft_free_ptr((void **)&(hash_item->value));
	ft_free_ptr((void **)&(hash_item));
}

void	ft_clear_hash_item2(t_hash_item **hash_item)
{
	ft_free_ptr((void **)&((*hash_item)->key));
	ft_free_ptr((void **)&((*hash_item)->value));
	(*hash_item)->next = NULL;
	(*hash_item)->prev = NULL;
	ft_free_ptr((void **)&(*hash_item));
	*hash_item = NULL;
}

void	ft_clear_hash_items(t_hash_item **hash_head)
{
	t_hash_item	*hash_tmp;

	while (*hash_head)
	{
		if (!(*hash_head)->next)
		{
			ft_clear_hash_item(*hash_head);
			break ;
		}
		hash_tmp = (*hash_head)->next;
		hash_tmp->prev = NULL;
		ft_clear_hash_item(*hash_head);
		(*hash_head) = hash_tmp;
	}
	hash_head = NULL;
}

void	ft_clear_hash_table(t_hash_table *hash_table)
{
	size_t	index;

	index = 0;
	while (index < hash_table->size)
	{
		ft_clear_hash_items(&hash_table->hash_items[index]);
		index++;
	}
	ft_free_ptr((void **)&(hash_table->hash_items));
	ft_free_ptr((void **)&(hash_table));
}
