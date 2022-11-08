/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hash_table_init.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbonaldi <bbonaldi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/31 22:09:28 by bbonaldi          #+#    #+#             */
/*   Updated: 2022/10/31 22:09:59 by bbonaldi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include "minishell.h"

void	ft_initialize_hash_items(t_hash_table *hash_table)
{
	size_t	index;

	index = 0;
	while (index < hash_table->size)
	{
		hash_table->hash_items[index] = NULL;
		index++;
	}
}

t_hash_item	*ft_create_hash_item(char *key, char *value)
{
	t_hash_item	*hash_item;

	hash_item = (t_hash_item *)malloc(sizeof(t_hash_item));
	hash_item->key = ft_strdup(key);
	hash_item->value = ft_strdup(value);
	hash_item->next = NULL;
	hash_item->prev = NULL;
	return (hash_item);
}

t_hash_table	*ft_create_hash_table(size_t size)
{
	t_hash_table	*hash_table;

	hash_table = (t_hash_table *)malloc(sizeof(t_hash_table));
	hash_table->hash_items = (t_hash_item **)malloc(sizeof(t_hash_item *) * size);
	hash_table->size = size;
	hash_table->count = 0;
	ft_initialize_hash_items(hash_table);
	return (hash_table);
}
