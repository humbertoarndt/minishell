/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_delete.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:42:37 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/31 22:45:03 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_hash_item_more_than_one(t_hash_item **hash_table_items,
			t_hash_item	**found_hash_item)
{
	t_hash_item	*hash_item_tmp;

	hash_item_tmp = (*found_hash_item)->prev;
	if (hash_item_tmp)
		hash_item_tmp->next = (*found_hash_item)->next;
	hash_item_tmp = (*found_hash_item)->next;
	if ((*hash_table_items) == (*found_hash_item))
		(*hash_table_items) = (*found_hash_item)->next;
	if (hash_item_tmp)
		hash_item_tmp->prev = (*found_hash_item)->prev;
	ft_clear_hash_item2(found_hash_item);
}

int	ft_delete_hash_item_by_key(t_hash_table *hash_table, char *key)
{
	t_hash_item	*found_hash_item;
	size_t		count_items;
	t_uint		hash;

	hash = ft_hash(key, hash_table->size);
	found_hash_item = hash_table->hash_items[hash];
	count_items = ft_count_items_in_bucket(found_hash_item);
	while (found_hash_item)
	{
		if (found_hash_item 
			&& ft_strncmp(found_hash_item->key, key, ft_strlen(key)) == 0)
			break ;
		found_hash_item = found_hash_item->next;
	}
	if (!found_hash_item)
		return (FALSE);
	if (count_items == 1)
		ft_clear_hash_item2(&hash_table->hash_items[hash]);
	else
		ft_delete_hash_item_more_than_one(&hash_table->hash_items[hash],
			&found_hash_item);
	hash_table->count--;
	return (TRUE);
}